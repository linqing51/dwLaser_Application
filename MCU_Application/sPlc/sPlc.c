/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/

#include "sPlc.h"
#include "elog_ext.h"
extern void restoreDefault(void);//预设方案恢复默认设置(MainAppLib层, DM区CRC校验失败时使用)
//避免指针和动态RAM分配 移植大部分8BIT和16BIT单片机效率低存在问题
#pragma pack(push, 4)
int16_t NVRAM0[CONFIG_NVRAM_SIZE];//掉电保持寄存器 当前 包含存档寄存器
int16_t NVRAM1[CONFIG_NVRAM_SIZE];//掉电保持寄存器 上一次
int16_t FDRAM0[CONFIG_FDRAM_SIZE], FDRAM1[CONFIG_FDRAM_SIZE];//存档寄存器
int16_t BKRAM0[CONFIG_BKRAM_SIZE / 2] __attribute__((at(CONFIG_BKSRAM_BASE_ADDR)));//BKRAM0: BKSRAM起始(2K字节)
int16_t BKRAM1[CONFIG_BKRAM_SIZE / 2] __attribute__((at(CONFIG_BKSRAM_BASE_ADDR + (CONFIG_BKRAM_SIZE * 2L / 2L))));//BKRAM1: BKSRAM中间(2K字节) 真掉电存储寄存器
uint32_t BootloadCrc, ApplicationCrc;//当前固件校验码
#pragma pack(pop)
/*****************************************************************************/
uint16_t TimerCounter_10mS = 0;//10毫秒
uint16_t TimerCounter_100mS = 0;//100毫秒
uint16_t TimerCounter_200mS = 0;//200毫秒
uint16_t TimerCounter_500mS = 0;//500毫秒
uint16_t TimerCounter_1000mS = 0;//1秒
uint16_t TimerCounter_60000mS = 0;//1分钟
/*****************************************************************************/
uint8_t TD_10MS_SP = 0;
uint8_t TD_100MS_SP = 0;
uint8_t TD_200MS_SP = 0;
uint8_t TD_500MS_SP = 0;
uint8_t TD_1000MS_SP = 0;
uint8_t TD_60000MS_SP = 0;
/******************************************************************************/
deviceConfig_t deviceConfig;
deviceLogInfo_t deviceLogInfo;
/*****************************************************************************/
void sPlcErrorHandler(uint16_t errCode){
	while(1);
}

void sPlcAssertCoilAddress(uint16_t adr){//检查线圈地址
#if CONFIG_SPLC_ASSERT == 1
	uint32_t maxCoilAdr = CONFIG_NVRAM_SIZE * 16 - 1;
	if(adr > (maxCoilAdr)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
void sPlcAssertRegisterAddress(uint16_t adr){//检查寄存器地址
#if CONFIG_SPLC_ASSERT == 1
	if(adr > (CONFIG_NVRAM_SIZE - 1)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
uint32_t sPlcCrc32Calc(CRC_HandleTypeDef *hcrc, uint32_t *pBuffer, uint32_t BufferLength){//EPROM CRC32: 计算前RCC强制复位CRC外设(同步复位确保DR=0xFFFFFFFF/CR=0), 消除任何状态残留
	__HAL_RCC_CRC_CLK_ENABLE();
	__HAL_RCC_CRC_FORCE_RESET();
	__HAL_RCC_CRC_RELEASE_RESET();
	CRC->CR = 0x00000000U;//复位后CR应为0(REV_IN=WORDS, REV_OUT=0)
	return HAL_CRC_Calculate(hcrc, pBuffer, BufferLength);
}
uint32_t sPlcCrc32Soft(uint32_t *pBuffer, uint32_t BufferLength){//标准CRC-32软件计算(与HAL硬件WORDS语义一致: poly 0x04C11DB7/初值0xFFFFFFFF/无输出异或), 用于对照验证硬件外设
	uint32_t crc = 0xFFFFFFFFu;
	uint32_t i;
	for(i = 0; i < BufferLength; i++){
		uint32_t v = pBuffer[i];
		int32_t b;
		for(b = 31; b >= 0; b--){
			uint32_t bit = (crc >> 31) & 1u;
			crc <<= 1;
			if(((v >> b) & 1u) != bit){
				crc ^= 0x04C11DB7u;
			}
		}
	}
	return crc;//与HAL DR一致(不做0xFFFFFFFF异或)
}
void sPlcNvramLoad(void){//从EPROM中载入NVRAM MR和DM
	volatile uint32_t crc32_mr, crc32_dm;//volatile: 防止-O1优化寄存器复用覆盖局部变量(此前被踩成0x93FFFFFF导致误判)
	uint32_t crc32_eprom_mr, crc32_eprom_dm;
	volatile uint8_t crcFailMr = 0, crcFailDm = 0;//CRC校验失败标志(volatile: 防止-O1寄存器复用覆盖导致if误判)
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));
	//从EPROM中恢复MR NVRAM
	epromRead(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MR_SIZE * 2));//从EPROM中恢复MR
	epromReadDword(CONFIG_EPROM_MR_CRC, &crc32_eprom_mr);
	crc32_mr = sPlcCrc32Calc(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MR_SIZE / 2));
	//从EPROM中恢复DM NVRAM
	epromRead(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DM_SIZE * 2));//从EPROM中恢复DM
	epromReadDword(CONFIG_EPROM_DM_CRC, &crc32_eprom_dm);
	crc32_dm = sPlcCrc32Calc(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DM_SIZE / 2));

	memcpy((uint8_t*)NVRAM1, (uint8_t*)NVRAM0, (CONFIG_NVRAM_SIZE * 2));
	if(crc32_eprom_mr != crc32_mr){
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:[DIAG]MR CRC FAIL epromAddr=0x%08X len=%d calc=0x%08X soft=0x%08X eprom=0x%08X\n",__FILE__, __LINE__, __func__, (unsigned)CONFIG_EPROM_MR_START, (CONFIG_MR_SIZE * 2), crc32_mr,
			sPlcCrc32Soft((uint32_t *)(NVRAM0 + MR_START), (CONFIG_MR_SIZE / 2)), crc32_eprom_mr);
#endif
		crcFailMr = 1; //之后在业务流程恢复当前只做标记
    SSET(SPCOIL_MR_CRC_FAIL);
	}
	if(crc32_eprom_dm != crc32_dm){
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:[DIAG]DM CRC FAIL epromAddr=0x%08X len=%d calc=0x%08X soft=0x%08X eprom=0x%08X\n",__FILE__, __LINE__, __func__, (unsigned)CONFIG_EPROM_DM_START, (CONFIG_DM_SIZE * 2), crc32_dm,
			sPlcCrc32Soft((uint32_t *)(NVRAM0 + DM_START), (CONFIG_DM_SIZE / 2)), crc32_eprom_dm);
#endif
		crcFailDm = 1; //之后在业务流程恢复当前只做标记
    SSET(SPCOIL_DM_CRC_FAIL);
	}
  //之后在业务流程恢复当前只做标记
	memcpy((uint8_t*)NVRAM1, (uint8_t*)NVRAM0, (CONFIG_NVRAM_SIZE * 2));//恢复后同步NVRAM镜像
	if(crcFailMr || crcFailDm){
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:load NVRAM crc fail, re-init done...\n",__FILE__, __LINE__, __func__);
#endif
	}
	else{
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:load NVRAM done...\n",__FILE__, __LINE__, __func__);
#endif
	}
#if (CONFIG_DEBUG_NVRAM == 1)
	//判断完成后再打印对照值, 避免printf执行过程破坏crc32变量导致判断误判
	printf("%s,%d,%s:MR EPROM CRC:0x%08X,MR CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_mr, crc32_mr);
	printf("%s,%d,%s:DM EPROM CRC:0x%08X,DM CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_dm, crc32_dm);
#endif
}
void sPlcNvramSave(void){//强制将NVRAM存入EPROM
	volatile uint32_t crc32_mr, crc32_dm;//volatile: 防止-O1优化寄存器复用覆盖
	//MR NVRAM写入EPROM
	crc32_mr = sPlcCrc32Calc(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MR_SIZE / 2));
	epromWrite(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MR_SIZE * 2));//将NVRAM中MR储存入EPROM
	{
		uint32_t crcTmp = crc32_mr;//volatile->非volatile拷贝后传址
		epromWriteDword(CONFIG_EPROM_MR_CRC, &crcTmp);//在的指定地址开始写入32位数
	}
#if (CONFIG_DEBUG_NVRAM == 1)
	printf("%s,%d,%s:[DIAG]save MR hw=0x%08X soft=0x%08X\n",__FILE__, __LINE__, __func__, crc32_mr,
		sPlcCrc32Soft((uint32_t *)(NVRAM0 + MR_START), (CONFIG_MR_SIZE / 2)));
#endif
	//DM NVRAM写入EPROM
	epromWrite(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DM_SIZE * 2));//将NVRAM中DM储存入EPROM
	crc32_dm = sPlcCrc32Calc(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DM_SIZE / 2));
	{
		uint32_t crcTmp = crc32_dm;//volatile->非volatile拷贝后传址
		epromWriteDword(CONFIG_EPROM_DM_CRC, &crcTmp);//在的指定地址开始写入32位数
	}
#if (CONFIG_DEBUG_NVRAM == 1)
	printf("%s,%d,%s:[DIAG]save DM hw=0x%08X soft=0x%08X\n",__FILE__, __LINE__, __func__, crc32_dm,
		sPlcCrc32Soft((uint32_t *)(NVRAM0 + DM_START), (CONFIG_DM_SIZE / 2)));
#endif
#if (CONFIG_DEBUG_NVRAM == 1)
	//写后回读校验(诊断): 逐段读回与内存逐字节比对 + CRC值回读比对(确认写入正确)
	{
		uint32_t rdCrcMr, rdCrcDm;
		uint8_t rdBuf[256];
		uint16_t rdIdx;
		uint8_t bkFail = 0;
		epromReadDword(CONFIG_EPROM_MR_CRC, &rdCrcMr);
		epromReadDword(CONFIG_EPROM_DM_CRC, &rdCrcDm);
		if((rdCrcMr != crc32_mr) || (rdCrcDm != crc32_dm)){
			LOG_PRINT(ELOG_LVL_ERROR, "%s,%d,%s:save NVRAM CRC区FAIL!(MR:0x%08X exp:0x%08X, DM:0x%08X exp:0x%08X)\n",__FILE__, __LINE__, __func__, rdCrcMr, crc32_mr, rdCrcDm, crc32_dm);
			bkFail = 1;
		}
		for(rdIdx = 0;rdIdx < (CONFIG_MR_SIZE * 2);rdIdx += 64){//MR区逐段读回逐字节比对(128B=2段)
			memset(rdBuf, 0, sizeof(rdBuf));
			epromRead((CONFIG_EPROM_MR_START + rdIdx), rdBuf, 64);
			if(memcmp(rdBuf, ((uint8_t*)(NVRAM0 + MR_START) + rdIdx), 64) != 0){
				LOG_PRINT(ELOG_LVL_ERROR, "%s,%d,%s:save NVRAM MR数据FAIL at:0x%08X!\n",__FILE__, __LINE__, __func__, (unsigned)(CONFIG_EPROM_MR_START + rdIdx));
				bkFail = 1;
				break;
			}
		}
		for(rdIdx = 0;rdIdx < (CONFIG_DM_SIZE * 2);rdIdx += 256){//DM区逐段读回逐字节比对(2048B=8段)
			memset(rdBuf, 0, sizeof(rdBuf));
			epromRead((CONFIG_EPROM_DM_START + rdIdx), rdBuf, 256);
			if(memcmp(rdBuf, ((uint8_t*)(NVRAM0 + DM_START) + rdIdx), 256) != 0){
				LOG_PRINT(ELOG_LVL_ERROR, "%s,%d,%s:save NVRAM DM数据FAIL at:0x%08X!\n",__FILE__, __LINE__, __func__, (unsigned)(CONFIG_EPROM_DM_START + rdIdx));
				bkFail = 1;
				break;
			}
		}
		if(bkFail == 0){
			printf("%s,%d,%s:[DIAG]save NVRAM verify PASS!(MR:0x%08X,DM:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr, crc32_dm);
			LOG_PRINT(ELOG_LVL_INFO, "%s,%d,%s:save NVRAM verify pass!(MR:0x%08X,DM:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr, crc32_dm);
		}
		else{
			printf("%s,%d,%s:[DIAG]save NVRAM verify FAIL!\n",__FILE__, __LINE__, __func__);
		}
		{//诊断: 直接回读EPROM MR区原始内容与CRC区, 验证verify读到的是否真是EPROM
			uint8_t rdFull[64];
			uint32_t rdCrc2;
			uint16_t w;
			epromRead(CONFIG_EPROM_MR_START, rdFull, 64);
			epromReadDword(CONFIG_EPROM_MR_CRC, &rdCrc2);
			printf("%s,%d,%s:[DIAG]verify readback EPROM MR(16w):",__FILE__, __LINE__, __func__);
			for(w = 0;w < 16;w ++){ printf("%04X ", ((uint16_t*)rdFull)[w]); }
			printf(" epromCRC=0x%08X memCRC=0x%08X\n", rdCrc2, crc32_mr);
		}
	}
#endif
#if (CONFIG_DEBUG_NVRAM == 1)
	printf("%s,%d,%s:[DIAG]save NVRAM done...(MR CRC:0x%08X,DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr, crc32_dm);
#endif
	LOG_PRINT(ELOG_LVL_INFO, "%s,%d,%s:save NVRAM done...(MR CRC:0x%08X,DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr, crc32_dm);
}
void sPlcNvramUpdate(void){//更新NVRAM->EPROM(优化: 连续变化字节合并段批量写, 减少SPI传输次数与耗时)
	uint8_t *sp0, *sp1;
	uint8_t updateFlagMr, updateFlagDm;
	uint8_t inSeg;
	uint16_t i, segStart;
	volatile uint32_t crc32_mr, crc32_dm;//volatile: 防止-O1优化寄存器复用覆盖
	//储存MR(变化字节按连续区间合并, 每次epromWrite写一整段, 代替逐字节epromWriteByte)
	updateFlagMr = 0;
	sp0 = (uint8_t*)(NVRAM0 + MR_START);
	sp1 = (uint8_t*)(NVRAM1 + MR_START);
	segStart = 0;
	inSeg = 0;
	for(i = 0;i < (CONFIG_MR_SIZE * 2);i ++){//储存MR
		if(*sp0 != *sp1){
			if(inSeg == 0){
				segStart = i;
				inSeg = 1;
			}
			updateFlagMr = 0xFF;
		}
		else if(inSeg == 1){//连续变化段结束, 整段批量写
			epromWrite((CONFIG_EPROM_MR_START + segStart), ((uint8_t*)(NVRAM0 + MR_START) + segStart), (i - segStart));
			inSeg = 0;
		}
		sp0 ++;
		sp1 ++;
	}
	if(inSeg == 1){//尾部变化段
		epromWrite((CONFIG_EPROM_MR_START + segStart), ((uint8_t*)(NVRAM0 + MR_START) + segStart), (i - segStart));
	}
	if(updateFlagMr){
		crc32_mr = sPlcCrc32Calc(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MR_SIZE / 2));
		{
			uint32_t crcTmp = crc32_mr;//volatile->非volatile拷贝后传址
			epromWriteDword(CONFIG_EPROM_MR_CRC, &crcTmp);//在的指定地址开始写入32位数
		}
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:[DIAG]update MR NVRAM written (MR CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr);
#endif
	}
	//储存DM(同上)
	updateFlagDm = 0;
	sp0 = (uint8_t*)(NVRAM0 + DM_START);
	sp1 = (uint8_t*)(NVRAM1 + DM_START);
	segStart = 0;
	inSeg = 0;
	for(i = 0;i < (CONFIG_DM_SIZE * 2);i ++){//储存DM
		if(*sp0 != *sp1){
			if(inSeg == 0){
				segStart = i;
				inSeg = 1;
			}
			updateFlagDm = 0xFF;
		}
		else if(inSeg == 1){//连续变化段结束, 整段批量写
			epromWrite((CONFIG_EPROM_DM_START + segStart), ((uint8_t*)(NVRAM0 + DM_START) + segStart), (i - segStart));
			inSeg = 0;
		}
		sp0 ++;
		sp1 ++;
	}
	if(inSeg == 1){//尾部变化段
		epromWrite((CONFIG_EPROM_DM_START + segStart), ((uint8_t*)(NVRAM0 + DM_START) + segStart), (i - segStart));
	}
	if(updateFlagDm){
		crc32_dm = sPlcCrc32Calc(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DM_SIZE / 2));
		{
			uint32_t crcTmp = crc32_dm;//volatile->非volatile拷贝后传址
			epromWriteDword(CONFIG_EPROM_DM_CRC, &crcTmp);//在的指定地址开始写入32位数
		}
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:[DIAG]update DM NVRAM written (DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_dm);
#endif
	}
	memcpy((uint8_t*)(NVRAM1), (uint8_t*)(NVRAM0), (CONFIG_NVRAM_SIZE * 2));//更新NVRAM1 非保持寄存器
#if (CONFIG_DEBUG_NVRAM == 1)
	if(updateFlagMr){    
		LOG_PRINT(ELOG_LVL_DEBUG, "%s,%d,%s:update MR NVRAM done...(MR CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr);
	}
	if(updateFlagDm){
		LOG_PRINT(ELOG_LVL_DEBUG, "%s,%d,%s:update DM NVRAM done...(DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_dm);
	}
#endif
}
void sPlcNvramClear(void){//清除NVRAM数据	
	clearEprom(CLEAR_EPROM_NVRAM);//clear mr dm
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));//初始化NVRAM0
	memset((uint8_t*)NVRAM1, 0x0, (CONFIG_NVRAM_SIZE * 2));//初始化NVRAM1
#if (CONFIG_DEBUG_NVRAM == 1)
	printf("%s,%d,%s:clear NVRAM done...\n",__FILE__, __LINE__, __func__);
#endif
}
void sPlcFdramLoad(void){//从EPROM中载入FDRAM
	uint32_t crc32_fd;
	uint32_t crc32_eprom_fd;
	memset((uint8_t*)FDRAM0, 0x0, (CONFIG_FDRAM_SIZE * 2));//初始化FDRAM(已移除早期自测0x01填充)
  epromRead(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));//从EPROM中恢复MR
	epromReadDword(CONFIG_EPROM_FD_CRC, &crc32_eprom_fd);
  crc32_fd = sPlcCrc32Calc(&hcrc, (uint32_t *)(FDRAM0), (CONFIG_FDRAM_SIZE / 2));
  memcpy((uint8_t*)FDRAM1, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
  if(crc32_eprom_fd != crc32_fd){
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:[DIAG]FD CRC FAIL epromAddr=0x%08X len=%d calc=0x%08X eprom=0x%08X\n",__FILE__, __LINE__, __func__, (unsigned)CONFIG_EPROM_FD_START, (CONFIG_FDRAM_SIZE * 2), crc32_fd, crc32_eprom_fd);
#endif
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:load FDRAM crc fail...\n",__FILE__, __LINE__, __func__);
#endif
    SSET(SPCOIL_FD_CRC_FAIL); //之后在业务流程恢复当前只做标记(FD区失败)
	}
	else{
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:load FDRAM done...\n",__FILE__, __LINE__, __func__);
#endif
	}
#if (CONFIG_DEBUG_NVRAM == 1)
	//判断完成后再打印对照值, 避免printf执行过程破坏crc32变量导致判断误判
	printf("%s,%d,%s:FDRAM EPROM CRC:0x%08X,FDRAM CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_fd, crc32_fd);
#endif
}
void sPlcFdramSave(void){//强制将FDRAM存入EPROM
	uint32_t crc32_eprom_fd;
  HAL_StatusTypeDef ref;
  crc32_eprom_fd = sPlcCrc32Calc(&hcrc,(uint32_t *)(FDRAM0), (CONFIG_FDRAM_SIZE / 2));
	ref = epromWrite(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
	ref = epromWriteDword(CONFIG_EPROM_FD_CRC, &crc32_eprom_fd);//在的指定地址开始写入32位数
  if(ref != HAL_OK){
#if (CONFIG_DEBUG_NVRAM == 1)
		LOG_PRINT(ELOG_LVL_ERROR, "%s,%d,%s:save FD RAM fail...\n",__FILE__, __LINE__, __func__);
#endif
	}
	else{
#if (CONFIG_DEBUG_NVRAM == 1)
    LOG_PRINT(ELOG_LVL_INFO, "%s,%d,%s:save FD RAM done...(FDRAM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_eprom_fd);
#endif
	}
#if (CONFIG_DEBUG_NVRAM == 1)
	//写后回读校验(诊断): 逐段读回与内存逐字节比对 + CRC值回读比对(确认写入正确)
	{
		uint32_t rdCrcFd;
		uint8_t rdBuf[256];
		uint16_t rdIdx;
		uint8_t bkFail = 0;
		epromReadDword(CONFIG_EPROM_FD_CRC, &rdCrcFd);
		if(rdCrcFd != crc32_eprom_fd){
			LOG_PRINT(ELOG_LVL_ERROR, "%s,%d,%s:save FD RAM CRC区FAIL!(0x%08X exp:0x%08X)\n",__FILE__, __LINE__, __func__, rdCrcFd, crc32_eprom_fd);
			bkFail = 1;
		}
		for(rdIdx = 0;rdIdx < (CONFIG_FDRAM_SIZE * 2);rdIdx += 256){//FDRAM区逐段读回逐字节比对(4096B=16段)
			memset(rdBuf, 0, sizeof(rdBuf));
			epromRead((CONFIG_EPROM_FD_START + rdIdx), rdBuf, 256);
			if(memcmp(rdBuf, ((uint8_t*)FDRAM0 + rdIdx), 256) != 0){
				LOG_PRINT(ELOG_LVL_ERROR, "%s,%d,%s:save FD RAM 数据FAIL at:0x%08X!\n",__FILE__, __LINE__, __func__, (unsigned)(CONFIG_EPROM_FD_START + rdIdx));
				bkFail = 1;
				break;
			}
		}
		if(bkFail == 0){
			printf("%s,%d,%s:[DIAG]save FD RAM verify PASS!(CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_eprom_fd);
			LOG_PRINT(ELOG_LVL_INFO, "%s,%d,%s:save FD RAM verify pass!(CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_eprom_fd);
		}
		else{
			printf("%s,%d,%s:[DIAG]save FD RAM verify FAIL!\n",__FILE__, __LINE__, __func__);
		}
	}
#endif
}
void sPlcFdramClear(void){//清除FDRAM数据
	clearEprom(CLEAR_EPROM_FDRAM);//clear mr dm
	memset(FDRAM0, 0x0, (CONFIG_FDRAM_SIZE * 2));//初始化FDRAM
	memset(FDRAM1, 0x0, (CONFIG_FDRAM_SIZE * 2));//初始化FDRAM
#if (CONFIG_DEBUG_NVRAM == 1)  
  printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
#endif
}

void sPlcBkramLoad(void){//从EPROM中载入BK(映射BKSRAM)
	uint32_t crc32_bk;
	uint32_t crc32_eprom_bk;
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();//解除备份域写保护
	__HAL_RCC_BKPSRAM_CLK_ENABLE();//使能BKPSRAM接口时钟
	memset((uint8_t*)CONFIG_BKSRAM_BASE_ADDR, 0x0, (CONFIG_BKRAM_SIZE * 2));//清空BKSRAM
	epromRead(CONFIG_EPROM_BK_START, (uint8_t*)CONFIG_BKSRAM_BASE_ADDR, (CONFIG_BKRAM_SIZE * 2));//从EPROM中恢复BK
	epromReadDword(CONFIG_EPROM_BK_CRC, &crc32_eprom_bk);
	crc32_bk = sPlcCrc32Calc(&hcrc, (uint32_t *)CONFIG_BKSRAM_BASE_ADDR, (CONFIG_BKRAM_SIZE / 2));
	if(crc32_eprom_bk != crc32_bk){
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:[DIAG]BK CRC FAIL epromAddr=0x%08X len=%d calc=0x%08X eprom=0x%08X\n",__FILE__, __LINE__, __func__, (unsigned)CONFIG_EPROM_BK_START, (CONFIG_BKRAM_SIZE * 2), crc32_bk, crc32_eprom_bk);
		printf("%s,%d,%s:[DIAG]BK SRAM head(8w):%04X %04X %04X %04X %04X %04X %04X %04X\n",__FILE__, __LINE__, __func__,
			((uint16_t*)CONFIG_BKSRAM_BASE_ADDR)[0],((uint16_t*)CONFIG_BKSRAM_BASE_ADDR)[1],((uint16_t*)CONFIG_BKSRAM_BASE_ADDR)[2],((uint16_t*)CONFIG_BKSRAM_BASE_ADDR)[3],
			((uint16_t*)CONFIG_BKSRAM_BASE_ADDR)[4],((uint16_t*)CONFIG_BKSRAM_BASE_ADDR)[5],((uint16_t*)CONFIG_BKSRAM_BASE_ADDR)[6],((uint16_t*)CONFIG_BKSRAM_BASE_ADDR)[7]);
#endif
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:load BK crc fail...\n",__FILE__, __LINE__, __func__);
#endif
    SSET(SPCOIL_BK_CRC_FAIL); //之后在业务流程恢复当前只做标记(BK区失败)
	}
	else{
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:load BK done...\n",__FILE__, __LINE__, __func__);
#endif
		RRES(SPCOIL_BK_CRC_FAIL);//还原成功清除BK失败标记
	}
#if (CONFIG_DEBUG_NVRAM == 1)
	//判断完成后再打印对照值, 避免printf执行过程破坏crc32变量导致判断误判
	printf("%s,%d,%s:BK EPROM CRC:0x%08X,BK CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_bk, crc32_bk);
#endif
}

void sPlcBkramSave(void){//BKSRAM->EPROM 强制保存
	uint32_t crc32_bk;
	HAL_StatusTypeDef ref1, ref2;
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_BKPSRAM_CLK_ENABLE();
	crc32_bk = sPlcCrc32Calc(&hcrc, (uint32_t *)CONFIG_BKSRAM_BASE_ADDR, (CONFIG_BKRAM_SIZE / 2));
	ref1 = epromWrite(CONFIG_EPROM_BK_START, (uint8_t*)CONFIG_BKSRAM_BASE_ADDR, (CONFIG_BKRAM_SIZE * 2));
	ref2 = epromWriteDword(CONFIG_EPROM_BK_CRC, &crc32_bk);//在的指定地址开始写入32位数
	if((ref1 != HAL_OK) || (ref2 != HAL_OK)){
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:[DIAG]save BK NVRAM SPI FAIL! (ref1=%d ref2=%d)\n",__FILE__, __LINE__, __func__, ref1, ref2);
#endif
#if (CONFIG_DEBUG_NVRAM == 1)
		LOG_PRINT(ELOG_LVL_ERROR, "%s,%d,%s:save BK NVRAM fail...\n",__FILE__, __LINE__, __func__);
#endif
	}
	else{
#if (CONFIG_DEBUG_NVRAM == 1)
		printf("%s,%d,%s:[DIAG]save BK done (BK CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_bk);
#endif
#if (CONFIG_DEBUG_NVRAM == 1)
		LOG_PRINT(ELOG_LVL_INFO, "%s,%d,%s:save BK done...(BK CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_bk);
#endif
  }
}

void sPlcBkramClear(void){//清除BK数据(含EPROM BK区)
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_BKPSRAM_CLK_ENABLE();
	clearEprom(CLEAR_EPROM_BKRAM);//清除EPROM BK数据区与CRC
	memset((uint8_t*)CONFIG_BKSRAM_BASE_ADDR, 0x0, (CONFIG_BKRAM_SIZE * 2));//清空BKSRAM
#if (CONFIG_DEBUG_NVRAM == 1)
	printf("%s,%d,%s:clear BK done...\n",__FILE__, __LINE__, __func__);
#endif
}

void sPlcDeviceConfigClear(void){//清除设备配置参数
	clearEprom(CLEAR_EPROM_DEVICE_CONFIG);
#if (CONFIG_DEBUG_NVRAM == 1)
	printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
#endif
}
void sPlcDeviceLogClear(void){//清除设备记录
	clearEprom(CLEAR_EPROM_LOG_INFO);
#if (CONFIG_DEBUG_NVRAM == 1)
	printf("%s,%d,%s:clear device log done...\n",__FILE__, __LINE__, __func__);
#endif
}

void sPlcSpwmLoop(void){//SPWM轮询	
	if(LDP(SPCOIL_PS10MS)){//每10mS执行一次
		//SPWM0
		if(LD(SPCOIL_SPWM_RESET_0)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_0] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = 0;
			RRES(SPCOIL_SPWM_RESET_0);
			RRES(SPCOIL_SPWM_OUT_0);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_0] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_0] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_0] = NVRAM0[SPREG_SPWM_POS_0];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = NVRAM0[SPREG_SPWM_CYCLE_0];
			SSET(SPCOIL_SPWM_OUT_0);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_0] == NVRAM0[SPREG_SPWM_POS_SHADOW_0]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
			RRES(SPCOIL_SPWM_OUT_0);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
		}
		//SPWM1
		if(LD(SPCOIL_SPWM_RESET_1)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_1] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = 0; 
			RRES(SPCOIL_SPWM_RESET_1);
			RRES(SPCOIL_SPWM_OUT_1);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_1] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_1] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_1] = NVRAM0[SPREG_SPWM_POS_1];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = NVRAM0[SPREG_SPWM_CYCLE_1];
			SSET(SPCOIL_SPWM_OUT_1);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_1] == NVRAM0[SPREG_SPWM_POS_SHADOW_1]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
			RRES(SPCOIL_SPWM_OUT_1);
		}
		
		else{
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
		}
		//SPWM2
		if(LD(SPCOIL_SPWM_RESET_2)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_2] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = 0;
			RRES(SPCOIL_SPWM_RESET_2);
			RRES(SPCOIL_SPWM_OUT_2);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_2] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_2] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_2] = NVRAM0[SPREG_SPWM_POS_2];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2] = NVRAM0[SPREG_SPWM_CYCLE_2];
			SSET(SPCOIL_SPWM_OUT_2);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_2] == NVRAM0[SPREG_SPWM_POS_SHADOW_2]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
			RRES(SPCOIL_SPWM_OUT_2);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
		}
		//SPWM3
		if(LD(SPCOIL_SPWM_RESET_3)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_3] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = 0;
			RRES(SPCOIL_SPWM_RESET_3);
			RRES(SPCOIL_SPWM_OUT_3);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_3] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_3] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_3] = NVRAM0[SPREG_SPWM_POS_3];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = NVRAM0[SPREG_SPWM_CYCLE_3];
			SSET(SPCOIL_SPWM_OUT_3);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_3] == NVRAM0[SPREG_SPWM_POS_SHADOW_3]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
			RRES(SPCOIL_SPWM_OUT_3);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
		}
	}
}

void sPlcRtcProcess(void){//RTC轮询(万年历同步到NVRAM EM_RTC_*,NVRAM中year沿用后两位约定,HMI显示时+2000)
	uint16_t year;
	uint8_t mon, day, hour, min, sec;
	RtcGetDateTime(&year, &mon, &day, &hour, &min, &sec);
	NVRAM0[EM_RTC_YEAR] = (int16_t)(year - 2000);
	NVRAM0[EM_RTC_MONTH] = mon;
	NVRAM0[EM_RTC_DAY] = day;
	NVRAM0[EM_RTC_HOURS] = hour;
	NVRAM0[EM_RTC_MINUTES] = min;
	NVRAM0[EM_RTC_SECONDS] = sec;
}
/*****************************************************************************/
void sPlcInit(void){//软逻辑初始化	
	elog_init();//日志分级库初始化(默认过滤级别 ELOG_OUTPUT_LVL)
	LOG_PRINT(ELOG_LVL_INFO, "%s,%d,%s:start App......\n",__FILE__, __LINE__, __func__);
	epromInit();
	readStm32UniqueID();
#if CONFIG_SPLC_USING_EPROM_TEST == 1
  while(1){
    sPlcEpromTest();
  }
#endif
	sPlcNvramLoad();//上电恢复NVRAM
	sPlcFdramLoad();//上电恢复FDRAM
#ifdef CONFIG_BKRAM_SIZE
	sPlcBkramLoad();//上电恢复BK(映射BKSRAM)
#endif
	RtcCheckAndInit();//RTC掉电检测与防锁死初始化(含BKSRAM使能)
	BootloadCrc = getOriginBootloadCrc();
	ApplicationCrc = getOriginAppCrc();
#if (CONFIG_DEBUG_NVRAM == 1)
	printf("%s,%d,%s:bootload crc:0x%08X\n",__FILE__, __LINE__, __func__, BootloadCrc);
	printf("%s,%d,%s:app crc:0x%08X\n",__FILE__, __LINE__, __func__, ApplicationCrc);
#endif
	SSET(SPCOIL_ON);
	SSET(SPCOIL_START_UP);
	
	
	sPlcTimerInit();//初始化硬件计时器模块 启动计时器
	sPlcSpeakerInit();
	
	sPlcPortInit();
	
	
	SET_RED_LED_OFF;
	SET_GREEN_LED_OFF;	
	SET_BLUE_LED_OFF;
	RRES(Y_TICK_LED);
}
void sPlcProcessStart(void){//sPLC轮询起始
	if(TD_10MS_SP >= 1){
		FLIP(SPCOIL_PS10MS);
		TD_10MS_SP = 0;
		if(NVRAM0[SPREG_BEEM_COUNTER] < INT16_MAX){
			NVRAM0[SPREG_BEEM_COUNTER] ++;
		}
	}
	if(TD_100MS_SP >= 1){
		FLIP(SPCOIL_PS100MS);
		TD_100MS_SP = 0;
	}
	if(TD_200MS_SP >= 1){
		FLIP(SPCOIL_PS200MS);
		TD_200MS_SP = 0;
	}
	if(TD_500MS_SP >= 1){
		FLIP(SPCOIL_PS500MS);
		TD_500MS_SP = 0;
	}
	if(TD_1000MS_SP >= 1){
		FLIP(SPCOIL_PS1000MS);
		TD_1000MS_SP = 0;
	}
	if(TD_60000MS_SP >= 1){
		FLIP(SPCOIL_PS1MINS);
		TD_60000MS_SP = 0;
	}
	sPlcInputRefresh();//读取X口输入
	if(LDP(SPCOIL_PS100MS)){
#if (CONFIG_SPLC_USING_RTC == 1)
		sPlcRtcProcess();//RTC万年历同步到NVRAM
#endif
	}
	sPlcSpwmLoop();
	sPlcAdcProcessBuffer();//ADC 更新NVRAM
}

void sPlcProcessEnd(void){//sPLC轮询结束
	if(LDP(SPCOIL_PS500MS)){
		FLIP(Y_TICK_LED);
	}
	sPlcOutputRefresh();//更新Y口输出
	sPlcNvramUpdate();//更新NVRAM
	RRES(SPCOIL_START_UP);
}





