/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "sPlc.h"
//閬垮厤鎸囬拡鍜屽姩鎬丷AM鍒嗛厤 绉绘澶ч儴鍒?BIT鍜?6BIT鍗曠墖鏈烘晥鐜囦綆瀛樺湪闂
/*****************************************************************************/
#pragma pack(push, 4)
int16_t NVRAM0[CONFIG_NVRAM_SIZE];//鎺夌數淇濇寔瀵勫瓨鍣?褰撳墠 鍖呭惈瀛樻。瀵勫瓨鍣?
int16_t NVRAM1[CONFIG_NVRAM_SIZE];//鎺夌數淇濇寔瀵勫瓨鍣?涓婁竴娆?
int16_t FDRAM0[CONFIG_FDRAM_SIZE], FDRAM1[CONFIG_FDRAM_SIZE];//瀛樻。瀵勫瓨鍣?
uint32_t BootloadCrc, ApplicationCrc;//褰撳墠鍥轰欢鏍￠獙鐮?
#pragma pack(pop)
/*****************************************************************************/
uint16_t TimerCounter_10mS = 0;//10姣
uint16_t TimerCounter_100mS = 0;//100姣
uint16_t TimerCounter_200mS = 0;//200姣
uint16_t TimerCounter_500mS = 0;//500姣
uint16_t TimerCounter_1000mS = 0;//1绉?
uint16_t TimerCounter_60000mS = 0;//1鍒嗛挓
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

void sPlcAssertCoilAddress(uint16_t adr){//妫€鏌ョ嚎鍦堝湴鍧€
#if CONFIG_SPLC_ASSERT == 1
	uint32_t maxCoilAdr = CONFIG_NVRAM_SIZE * 16 - 1;
	if(adr > (maxCoilAdr)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
void sPlcAssertRegisterAddress(uint16_t adr){//妫€鏌ュ瘎瀛樺櫒鍦板潃
#if CONFIG_SPLC_ASSERT == 1
	if(adr > (CONFIG_NVRAM_SIZE - 1)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
void sPlcNvramLoad(void){//浠嶦PROM涓浇鍏VRAM MR鍜孌M
	uint32_t crc32_mr, crc32_dm;
	uint32_t crc32_eprom_mr, crc32_eprom_dm;
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));
	//浠嶦PROM涓仮澶峂R NVRAM
	epromRead(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MR_SIZE * 2));//浠嶦PROM涓仮澶峂R
	epromReadDword(CONFIG_EPROM_MR_CRC, &crc32_eprom_mr);
	crc32_mr = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MR_SIZE / 2));
	//浠嶦PROM涓仮澶岲M NVRAM
	epromRead(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DM_SIZE * 2));//浠嶦PROM涓仮澶岲M
	epromReadDword(CONFIG_EPROM_DM_CRC, &crc32_eprom_dm);
	crc32_dm = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DM_SIZE / 2));
	
	memcpy((uint8_t*)NVRAM1, (uint8_t*)NVRAM0, (CONFIG_NVRAM_SIZE * 2));
	printf("%s,%d,%s:MR EPROM CRC:0x%08X,MR CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_mr, crc32_mr);
	printf("%s,%d,%s:DM EPROM CRC:0x%08X,DM CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_dm, crc32_dm);
	if((crc32_eprom_mr != crc32_mr) && (crc32_eprom_dm != crc32_dm)){
		printf("%s,%d,%s:load NVRAM crc fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load NVRAM done...\n",__FILE__, __LINE__, __func__);
	}
}
void sPlcNvramSave(void){//寮哄埗灏哊VRAM瀛樺叆EPROM
	uint32_t crc32_mr, crc32_dm;
	//MR NVRAM鍐欏叆EPROM
	epromWrite(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MR_SIZE * 2));//灏哊VRAM涓璏R鍌ㄥ瓨鍏PROM																				
	crc32_mr = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MR_SIZE / 2));
	epromWriteDword(CONFIG_EPROM_MR_CRC, &crc32_mr);//鍦ㄧ殑鎸囧畾鍦板潃寮€濮嬪啓鍏?2浣嶆暟
	//DM NVRAM鍐欏叆EPROM
	epromWrite(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DM_SIZE * 2));//灏哊VRAM涓璂M鍌ㄥ瓨鍏PROM
	crc32_dm = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DM_SIZE / 2));
	epromWriteDword(CONFIG_EPROM_DM_CRC, &crc32_dm);//鍦ㄧ殑鎸囧畾鍦板潃寮€濮嬪啓鍏?2浣嶆暟
	printf("%s,%d,%s:save NVRAM done...(MR CRC:0x%08X,DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr, crc32_dm);
}
void sPlcNvramUpdate(void){//鏇存柊NVRAM->EPROM
	uint8_t *sp0, *sp1;
	uint8_t updateFlagMr, updateFlagDm;
	uint16_t i;
	uint32_t crc32_mr, crc32_dm;
	//鍌ㄥ瓨MR
	updateFlagMr = 0;
	sp0 = (uint8_t*)(NVRAM0 + MR_START);
	sp1 = (uint8_t*)(NVRAM1 + MR_START);
	for(i = 0;i < (CONFIG_MR_SIZE * 2);i ++){//鍌ㄥ瓨MR
		if(*sp0 != *sp1){
			epromWriteByte((i + CONFIG_EPROM_MR_START), sp0);
			updateFlagMr |= 0xFF;
		}
		sp0 ++;
		sp1 ++;
	}
	if(updateFlagMr){
		crc32_mr = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MR_SIZE / 2));
		epromWriteDword(CONFIG_EPROM_MR_CRC, &crc32_mr);//鍦ㄧ殑鎸囧畾鍦板潃寮€濮嬪啓鍏?2浣嶆暟
	}
	//鍌ㄥ瓨DM
	updateFlagDm = 0;
	sp0 = (uint8_t*)(NVRAM0 + DM_START);
	sp1 = (uint8_t*)(NVRAM1 + DM_START);
	for(i = 0;i < (CONFIG_DM_SIZE * 2);i ++){//鍌ㄥ瓨MR
		if(*sp0 != *sp1){
			epromWriteByte((i + CONFIG_EPROM_DM_START), sp0);
			updateFlagDm |= 0xFF;
		}
		sp0 ++;
		sp1 ++;
	}
	if(updateFlagDm){
		crc32_dm = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DM_SIZE / 2));
		epromWriteDword(CONFIG_EPROM_DM_CRC, &crc32_dm);//鍦ㄧ殑鎸囧畾鍦板潃寮€濮嬪啓鍏?2浣嶆暟
	}
	memcpy((uint8_t*)(NVRAM1), (uint8_t*)(NVRAM0), (CONFIG_NVRAM_SIZE * 2));//鏇存柊NVRAM1 闈炰繚鎸佸瘎瀛樺櫒
#if (CONFIG_DEBUG_EPROM == 1)
	if(updateFlagMr){    
		printf("%s,%d,%s:update MR NVRAM done...(MR CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr);
	}
	if(updateFlagDm){
		printf("%s,%d,%s:update DM NVRAM done...(DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_dm);
	}
#endif
}
void sPlcNvramClear(void){//娓呴櫎NVRAM鏁版嵁	
	clearEprom(CLEAR_EPROM_NVRAM);//clear mr dm
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));//鍒濆鍖朜VRAM0
	memset((uint8_t*)NVRAM1, 0x0, (CONFIG_NVRAM_SIZE * 2));//鍒濆鍖朜VRAM1
	printf("%s,%d,%s:clear NVRAM done...\n",__FILE__, __LINE__, __func__);
}
void sPlcFdramLoad(void){//浠嶦PROM涓浇鍏DRAM
	uint32_t crc32_fd;
	uint32_t crc32_eprom_fd;
	memset((uint8_t*)FDRAM0, 0x0, (CONFIG_FDRAM_SIZE * 2));
  memset((uint8_t*)FDRAM0, 0x1, (CONFIG_FDRAM_SIZE * 2));
  epromRead(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));//浠嶦PROM涓仮澶峂R
	epromReadDword(CONFIG_EPROM_FD_CRC, &crc32_eprom_fd);
  crc32_fd = HAL_CRC_Calculate(&hcrc, (uint32_t *)(FDRAM0), (CONFIG_FDRAM_SIZE / 2));
  memcpy((uint8_t*)FDRAM1, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
  printf("%s,%d,%s:FDRAM EPROM CRC:0x%08X,FDRAM CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_fd, crc32_fd);
  if(crc32_eprom_fd != crc32_fd){
		printf("%s,%d,%s:load FDRAM crc fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load FDRAM done...\n",__FILE__, __LINE__, __func__);
	}  
}
void sPlcFdramSave(void){//寮哄埗灏咶DRAM瀛樺叆EPROM
	uint32_t crc32_eprom_fd;
  HAL_StatusTypeDef ref;
  crc32_eprom_fd = HAL_CRC_Calculate(&hcrc,(uint32_t *)(FDRAM0), (CONFIG_FDRAM_SIZE / 2));
	ref = epromWrite(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
	ref = epromWriteDword(CONFIG_EPROM_FD_CRC, &crc32_eprom_fd);//鍦ㄧ殑鎸囧畾鍦板潃寮€濮嬪啓鍏?2浣嶆暟
  if(ref != HAL_OK){
		printf("%s,%d,%s:save FD NVRAM fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
    printf("%s,%d,%s:save FDRAM done...(FDRAM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_eprom_fd);
	}
}
void sPlcFdramClear(void){//娓呴櫎FDRAM鏁版嵁
	clearEprom(CLEAR_EPROM_FDRAM);//clear mr dm
	memset(FDRAM0, 0x0, (CONFIG_FDRAM_SIZE * 2));//鍒濆鍖朏DRAM
	memset(FDRAM1, 0x0, (CONFIG_FDRAM_SIZE * 2));//鍒濆鍖朏DRAM
  printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
}
#ifdef CONFIG_BKRAM_SIZE
void sPlcBkramLoad(void){//浠嶦PROM涓浇鍏K(鏄犲皠BKSRAM)
	uint32_t crc32_bk;
	uint32_t crc32_eprom_bk;
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();//瑙ｉ櫎澶囦唤鍩熷啓淇濇姢
	__HAL_RCC_BKPSRAM_CLK_ENABLE();//浣胯兘BKPSRAM鎺ュ彛鏃堕挓
	memset((uint8_t*)BKRAM, 0x0, (CONFIG_BKRAM_SIZE * 2));//娓呯┖BKSRAM
	epromRead(CONFIG_EPROM_BK_START, (uint8_t*)BKRAM, (CONFIG_BKRAM_SIZE * 2));//浠嶦PROM涓仮澶岯K
	epromReadDword(CONFIG_EPROM_BK_CRC, &crc32_eprom_bk);
	crc32_bk = HAL_CRC_Calculate(&hcrc, (uint32_t *)BKRAM, (CONFIG_BKRAM_SIZE / 2));
	printf("%s,%d,%s:BK EPROM CRC:0x%08X,BK CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_bk, crc32_bk);
	if(crc32_eprom_bk != crc32_bk){
		printf("%s,%d,%s:load BK crc fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load BK done...\n",__FILE__, __LINE__, __func__);
	}
}
void sPlcBkramSave(void){//BKSRAM->EPROM 寮哄埗淇濆瓨
	uint32_t crc32_bk;
	HAL_StatusTypeDef ref1, ref2;
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_BKPSRAM_CLK_ENABLE();
	crc32_bk = HAL_CRC_Calculate(&hcrc, (uint32_t *)BKRAM, (CONFIG_BKRAM_SIZE / 2));
	ref1 = epromWrite(CONFIG_EPROM_BK_START, (uint8_t*)BKRAM, (CONFIG_BKRAM_SIZE * 2));
	ref2 = epromWriteDword(CONFIG_EPROM_BK_CRC, &crc32_bk);//鍦ㄧ殑鎸囧畾鍦板潃寮€濮嬪啓鍏?2浣嶆暟
	if((ref1 != HAL_OK) || (ref2 != HAL_OK)){
		printf("%s,%d,%s:save BK NVRAM fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:save BK done...(BK CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_bk);
	}
}
void sPlcBkramClear(void){//娓呴櫎BK鏁版嵁(鍚獷PROM BK鍖?
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_BKPSRAM_CLK_ENABLE();
	clearEprom(CLEAR_EPROM_BKRAM);//娓呴櫎EPROM BK鏁版嵁鍖轰笌CRC
	memset(BKRAM, 0x0, (CONFIG_BKRAM_SIZE * 2));//娓呯┖BKSRAM
	printf("%s,%d,%s:clear BK done...\n",__FILE__, __LINE__, __func__);
}
#endif
void sPlcDeviceConfigClear(void){//娓呴櫎璁惧閰嶇疆鍙傛暟
	clearEprom(CLEAR_EPROM_DEVICE_CONFIG);
	printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
}
void sPlcDeviceLogClear(void){//娓呴櫎璁惧璁板綍
	clearEprom(CLEAR_EPROM_LOG_INFO);
	printf("%s,%d,%s:clear device log done...\n",__FILE__, __LINE__, __func__);
}

void sPlcSpwmLoop(void){//SPWM杞	
	if(LDP(SPCOIL_PS10MS)){//姣?0mS鎵ц涓€娆?
		//SPWM0
		if(LD(SPCOIL_SPWM_RESET_0)){//澶嶄綅
			NVRAM0[SPREG_SPWM_COUNTER_0] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = 0;
			RRES(SPCOIL_SPWM_RESET_0);
			RRES(SPCOIL_SPWM_OUT_0);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_0] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0]){//鍙戠敓婧㈠嚭
			NVRAM0[SPREG_SPWM_COUNTER_0] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_0] = NVRAM0[SPREG_SPWM_POS_0];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = NVRAM0[SPREG_SPWM_CYCLE_0];
			SSET(SPCOIL_SPWM_OUT_0);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_0] == NVRAM0[SPREG_SPWM_POS_SHADOW_0]){//鍙戠敓鍖归厤缈昏浆杈撳嚭
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
			RRES(SPCOIL_SPWM_OUT_0);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
		}
		//SPWM1
		if(LD(SPCOIL_SPWM_RESET_1)){//澶嶄綅
			NVRAM0[SPREG_SPWM_COUNTER_1] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = 0; 
			RRES(SPCOIL_SPWM_RESET_1);
			RRES(SPCOIL_SPWM_OUT_1);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_1] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1]){//鍙戠敓婧㈠嚭
			NVRAM0[SPREG_SPWM_COUNTER_1] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_1] = NVRAM0[SPREG_SPWM_POS_1];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = NVRAM0[SPREG_SPWM_CYCLE_1];
			SSET(SPCOIL_SPWM_OUT_1);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_1] == NVRAM0[SPREG_SPWM_POS_SHADOW_1]){//鍙戠敓鍖归厤缈昏浆杈撳嚭
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
			RRES(SPCOIL_SPWM_OUT_1);
		}
		
		else{
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
		}
		//SPWM2
		if(LD(SPCOIL_SPWM_RESET_2)){//澶嶄綅
			NVRAM0[SPREG_SPWM_COUNTER_2] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = 0;
			RRES(SPCOIL_SPWM_RESET_2);
			RRES(SPCOIL_SPWM_OUT_2);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_2] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2]){//鍙戠敓婧㈠嚭
			NVRAM0[SPREG_SPWM_COUNTER_2] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_2] = NVRAM0[SPREG_SPWM_POS_2];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2] = NVRAM0[SPREG_SPWM_CYCLE_2];
			SSET(SPCOIL_SPWM_OUT_2);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_2] == NVRAM0[SPREG_SPWM_POS_SHADOW_2]){//鍙戠敓鍖归厤缈昏浆杈撳嚭
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
			RRES(SPCOIL_SPWM_OUT_2);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
		}
		//SPWM3
		if(LD(SPCOIL_SPWM_RESET_3)){//澶嶄綅
			NVRAM0[SPREG_SPWM_COUNTER_3] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = 0;
			RRES(SPCOIL_SPWM_RESET_3);
			RRES(SPCOIL_SPWM_OUT_3);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_3] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3]){//鍙戠敓婧㈠嚭
			NVRAM0[SPREG_SPWM_COUNTER_3] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_3] = NVRAM0[SPREG_SPWM_POS_3];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = NVRAM0[SPREG_SPWM_CYCLE_3];
			SSET(SPCOIL_SPWM_OUT_3);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_3] == NVRAM0[SPREG_SPWM_POS_SHADOW_3]){//鍙戠敓鍖归厤缈昏浆杈撳嚭
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
			RRES(SPCOIL_SPWM_OUT_3);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
		}
	}
}

void sPlcRtcProcess(void){//RTC杞(涓囧勾鍘嗗悓姝ュ埌NVRAM EM_RTC_*,NVRAM涓瓂ear娌跨敤鍚庝袱浣嶇害瀹?HMI鏄剧ず鏃?2000)
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
void sPlcInit(void){//杞€昏緫鍒濆鍖?
	printf("%s,%d,%s:start App......\n",__FILE__, __LINE__, __func__);
	epromInit();
  listEpromTable();
	readStm32UniqueID();
#if CONFIG_SPLC_USING_EPROM_TEST == 1
  while(1){
    sPlcEpromTest();
  }
#endif
	sPlcNvramLoad();//涓婄數鎭㈠NVRAM
	sPlcFdramLoad();//涓婄數鎭㈠FDRAM
#ifdef CONFIG_BKRAM_SIZE
	sPlcBkramLoad();//涓婄數鎭㈠BK(鏄犲皠BKSRAM)
#endif
	RtcCheckAndInit();//RTC鎺夌數妫€娴嬩笌闃查攣姝诲垵濮嬪寲(鍚獴KSRAM浣胯兘)
	BootloadCrc = getOriginBootloadCrc();
	ApplicationCrc = getOriginAppCrc();
	printf("%s,%d,%s:bootload crc:0x%08X\n",__FILE__, __LINE__, __func__, BootloadCrc);
	printf("%s,%d,%s:app crc:0x%08X\n",__FILE__, __LINE__, __func__, ApplicationCrc);
	SSET(SPCOIL_ON);
	SSET(SPCOIL_START_UP);
	
	
	sPlcTimerInit();//鍒濆鍖栫‖浠惰鏃跺櫒妯″潡 鍚姩璁℃椂鍣?
	sPlcSpeakerInit();
	
	sPlcPortInit();
	
	
	SET_RED_LED_OFF;
	SET_GREEN_LED_OFF;	
	SET_BLUE_LED_OFF;
	RRES(Y_TICK_LED);
}
void sPlcProcessStart(void){//sPLC杞璧峰
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
	sPlcInputRefresh();//璇诲彇X鍙ｈ緭鍏?
	if(LDP(SPCOIL_PS100MS)){
#if (CONFIG_SPLC_USING_RTC == 1)
		sPlcRtcProcess();//RTC涓囧勾鍘嗗悓姝ュ埌NVRAM
#endif
	}
	sPlcSpwmLoop();
	sPlcAdcProcessBuffer();//ADC 鏇存柊NVRAM
}

void sPlcProcessEnd(void){//sPLC杞缁撴潫
	if(LDP(SPCOIL_PS500MS)){
		FLIP(Y_TICK_LED);
	}
	sPlcOutputRefresh();//鏇存柊Y鍙ｈ緭鍑?
	sPlcNvramUpdate();//鏇存柊NVRAM
	RRES(SPCOIL_START_UP);
}





