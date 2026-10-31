/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "sPlc.h"
#include "sPlcEprom.h"
/*****************************************************************************/
static uint8_t cmpByte(uint8_t *psrc, uint8_t *pdist, uint16_t len){
	uint16_t i;
	for(i = 0;i < len;i ++){
		if(*(psrc + i) != *(pdist + i)){
			return false;
		}
	}
	return true;
}

uint8_t sPlcEpromTest(void){//EPROM 读写自测试(含长批量/边界/CRC回读校验)
	uint32_t i, crcRead = 0, crcWrite = 0;
	uint32_t bk, remain;
	uint8_t rblock[256], wblock[256];
	static uint8_t bigbuf[2048];//长批量测试缓冲(静态,不占栈)
	uint32_t tempRead, tempWrite;
	uint8_t res = 0;
	uint32_t longLen;
	uint16_t j;
	uint32_t bndAdr[8] = {0};//边界地址表
	uint32_t bndNum = 0;
	uint32_t bndCnt;

	//1.字节填充写入0x55(全区)
	printf("%s,%d,%s:byte(8bit) start write 0x55\r\n", __FILE__, __LINE__, __func__);
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		tempWrite = 0x55;
		tempRead = 0;
		epromWriteByte(i, (uint8_t*)&tempWrite);
	}
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		epromReadByte(i, (uint8_t*)&tempRead);
		if(tempRead != 0x55){
			printf("%s,%d,%s:byte(8bit) write 0x55 fail at:0x%08X!\r\n", __FILE__, __LINE__, __func__, i);
			res = false;
			break;
		}
	}
	//2.字节填充写入0xAA(全区,验证覆盖写)
	printf("%s,%d,%s:byte(8bit) start write 0xAA\r\n", __FILE__, __LINE__, __func__);
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		tempWrite = 0xAA;
		epromWriteByte(i, (uint8_t*)&tempWrite);
	}
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		epromReadByte(i, (uint8_t*)&tempRead);
		if(tempRead != 0xAA){
			printf("%s,%d,%s:byte(8bit) write 0xAA fail at:0x%08X!\r\n", __FILE__, __LINE__, __func__, i);
			res = false;
			break;
		}
	}
	//3.随机字节顺序写入+CRC比对(写/读各自累计CRC)
	__HAL_CRC_DR_RESET(&hcrc);//清空之前CRC32结果
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);
		epromWriteByte((i + 0), ((uint8_t*)&tempWrite + 0));
		epromWriteByte((i + 1), ((uint8_t*)&tempWrite + 1));
		epromWriteByte((i + 2), ((uint8_t*)&tempWrite + 2));
		epromWriteByte((i + 3), ((uint8_t*)&tempWrite + 3));
		crcWrite = HAL_CRC_Accumulate(&hcrc, &tempWrite, 1);
	}
	__HAL_CRC_DR_RESET(&hcrc);
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		epromReadByte((i + 0), ((uint8_t*)&tempRead + 0));
		epromReadByte((i + 1), ((uint8_t*)&tempRead + 1));
		epromReadByte((i + 2), ((uint8_t*)&tempRead + 2));
		epromReadByte((i + 3), ((uint8_t*)&tempRead + 3));
		crcRead = HAL_CRC_Accumulate(&hcrc, &tempRead, 1);
	}
	if(crcRead == crcWrite){
		printf("%s,%d,%s:byte(8bit) sequential write+CRC pass!\r\n", __FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:byte(8bit) sequential write+CRC fail!\r\n", __FILE__, __LINE__, __func__);
		res = false;
	}
	//4.字(16bit)顺序写入+CRC比对
	__HAL_CRC_DR_RESET(&hcrc);
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);
		epromWriteHword((i + 0), ((uint16_t*)&tempWrite + 0));
		epromWriteHword((i + 2), ((uint16_t*)&tempWrite + 1));
		crcWrite = HAL_CRC_Accumulate(&hcrc, &tempWrite, 1);
	}
	__HAL_CRC_DR_RESET(&hcrc);
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		epromReadHword((i + 0), ((uint16_t*)&tempRead + 0));
		epromReadHword((i + 2), ((uint16_t*)&tempRead + 1));
		crcRead = HAL_CRC_Accumulate(&hcrc, (uint32_t*)&tempRead, 1);
	}
	if(crcRead == crcWrite){
		printf("%s,%d,%s:hword(16bit) sequential write+CRC pass!\r\n", __FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:hword(16bit) sequential write+CRC fail! crcWrite=0x%08X crcRead=0x%08X\r\n", __FILE__, __LINE__, __func__, crcWrite, crcRead);
		//诊断: 确定性数据逐组写读比对, 定位首个失败地址与读回值
		bndCnt = 0;
		for(i = 0;i < CONFIG_EPROM_SIZE && bndCnt < 16;i += 4){
			tempWrite = (0x12345678u ^ i);//确定性期望值(每4字节唯一,可复现)
			epromWriteHword((i + 0), ((uint16_t*)&tempWrite + 0));
			epromWriteHword((i + 2), ((uint16_t*)&tempWrite + 1));
			epromReadHword((i + 0), ((uint16_t*)&tempRead + 0));
			epromReadHword((i + 2), ((uint16_t*)&tempRead + 1));
			if(tempRead != tempWrite){
				printf("%s,%d,%s:hword diag fail at:0x%04X wr=0x%08X rd=0x%08X\r\n", __FILE__, __LINE__, __func__, i, tempWrite, tempRead);
				bndCnt ++;
			}
		}
		if(bndCnt == 0) printf("%s,%d,%s:hword diag: 逐组比对全过(读回与期望一致), 疑CRC累计/端序问题\r\n", __FILE__, __LINE__, __func__);
		res = false;
	}
	//5.双字(32bit)顺序写入+CRC比对
	__HAL_CRC_DR_RESET(&hcrc);
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);
		epromWriteDword(i, &tempWrite);
		crcWrite = HAL_CRC_Accumulate(&hcrc, &tempWrite, 1);
	}
	__HAL_CRC_DR_RESET(&hcrc);
	for(i = 0;i < CONFIG_EPROM_SIZE;i += 4){
		epromReadDword(i, &tempRead);
		crcRead = HAL_CRC_Accumulate(&hcrc, &tempRead, 1);
	}
	if(crcRead == crcWrite){
		printf("%s,%d,%s:dword(32bit) sequential write+CRC pass!\r\n", __FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:dword(32bit) sequential write+CRC fail! crcWrite=0x%08X crcRead=0x%08X\r\n", __FILE__, __LINE__, __func__, crcWrite, crcRead);
		//诊断: 确定性数据逐组写读比对, 定位首个失败地址与读回值
		bndCnt = 0;
		for(i = 0;i < CONFIG_EPROM_SIZE && bndCnt < 16;i += 4){
			tempWrite = (0x12345678u ^ i);//确定性期望值(每4字节唯一,可复现)
			epromWriteDword(i, &tempWrite);
			epromReadDword(i, &tempRead);
			if(tempRead != tempWrite){
				printf("%s,%d,%s:dword diag fail at:0x%04X wr=0x%08X rd=0x%08X\r\n", __FILE__, __LINE__, __func__, i, tempWrite, tempRead);
				bndCnt ++;
			}
		}
		if(bndCnt == 0) printf("%s,%d,%s:dword diag: 逐组比对全过(读回与期望一致), 疑CRC累计/端序问题\r\n", __FILE__, __LINE__, __func__);
		res = false;
	}
	//5.5 非4对齐地址 hword/dword 读写校验(0x0001/0x0003 起各8组,覆盖奇数/未对齐地址盲区)
	{
		uint32_t naAdr[2] = {0x0001, 0x0003};
		uint32_t naIdx, naK, naBase;
		uint16_t naWr16, naRd16;
		for(naIdx = 0;naIdx < 2;naIdx ++){
			for(naK = 0;naK < 8;naK ++){
				naBase = naAdr[naIdx] + (naK * 32);//每组间隔32字节,避免组间重叠
				//hword: 非对齐16位写读
				tempWrite = 0xA55A0000u ^ (naBase << 1);
				naWr16 = (uint16_t)(tempWrite & 0xFFFFu);
				epromWriteHword(naBase, &naWr16);
				epromReadHword(naBase, &naRd16);
				if(naRd16 != naWr16){
					printf("%s,%d,%s:unaligned hword fail at:0x%04X wr=0x%04X rd=0x%04X\r\n", __FILE__, __LINE__, __func__, naBase, naWr16, naRd16);
					res = false;
				}
				//dword: 非对齐32位写读(覆盖hword写入的2字节并扩展2字节)
				tempWrite = 0xA55A0000u ^ naBase;
				epromWriteDword(naBase, &tempWrite);
				epromReadDword(naBase, &tempRead);
				if(tempRead != tempWrite){
					printf("%s,%d,%s:unaligned dword fail at:0x%04X wr=0x%08X rd=0x%08X\r\n", __FILE__, __LINE__, __func__, naBase, tempWrite, tempRead);
					res = false;
				}
			}
		}
		printf("%s,%d,%s:unaligned(0x0001/0x0003) hword/dword test done!\r\n", __FILE__, __LINE__, __func__);
	}
	//6.块顺序写入(64B块,修正:地址从0开始,读回与写入源比对)
	bk = CONFIG_EPROM_SIZE / sizeof(wblock);
	remain = CONFIG_EPROM_SIZE % sizeof(wblock);
	for(i = 0; i < bk;i ++){
		memset(wblock, (i & 0xFF), sizeof(wblock));
		memset(rblock, 0x00, sizeof(rblock));
		epromWrite((i * sizeof(wblock)), wblock, sizeof(wblock));
		epromRead((i * sizeof(wblock)), rblock, sizeof(wblock));
		if(cmpByte(wblock, rblock, sizeof(wblock)) == false){
			printf("%s,%d,%s:block sequential Write fail at blk:%d!\r\n", __FILE__, __LINE__, __func__, i);
			res = false;
		}
	}
	memset(wblock, (rand() % 0xFF), sizeof(wblock));
	memset(rblock, 0x00, sizeof(rblock));
	epromWrite((CONFIG_EPROM_SIZE - remain), wblock, remain);
	epromRead((CONFIG_EPROM_SIZE - remain), rblock, remain);
	if(cmpByte(wblock, rblock, remain) == false){
		printf("%s,%d,%s:block tail Write fail!\r\n", __FILE__, __LINE__, __func__);
		res = false;
	}
	printf("%s,%d,%s:block(64B) sequential Write pass!\r\n", __FILE__, __LINE__, __func__);
	//7.长批量写入回读(128B~2048B单次连续写,直击NVFSAVE全量保存场景)+CRC回读比对
	for(j = 0;j < 5;j ++){
		longLen = 128 << j;//128/256/512/1024/2048
		for(i = 0;i < longLen;i ++){
			bigbuf[i] = (uint8_t)((i * 7 + j) & 0xFF);//确定性模式
		}
		crcWrite = HAL_CRC_Calculate(&hcrc, (uint32_t*)bigbuf, (longLen / 4));//写前内存CRC
		epromWrite(0, bigbuf, longLen);//单次长连续写(从0地址)
		memset(bigbuf, 0x00, longLen);
		epromRead(0, bigbuf, longLen);
		crcRead = HAL_CRC_Calculate(&hcrc, (uint32_t*)bigbuf, (longLen / 4));//读回CRC
		for(i = 0;i < longLen;i ++){//逐字节回读比对
			if(bigbuf[i] != (uint8_t)((i * 7 + j) & 0xFF)){
				printf("%s,%d,%s:long write %uB fail at:0x%08X,exp:0x%02X,got:0x%02X!\r\n", __FILE__, __LINE__, __func__, (unsigned)longLen, (unsigned)i, (unsigned)(uint8_t)((i * 7 + j) & 0xFF), (unsigned)bigbuf[i]);
				res = false;
				break;
			}
		}
		if(crcRead != crcWrite){
			printf("%s,%d,%s:long write %uB CRC fail!(mem:0x%08X,rd:0x%08X)\r\n", __FILE__, __LINE__, __func__, (unsigned)longLen, (unsigned)crcWrite, (unsigned)crcRead);
			res = false;
		}
		else{
			printf("%s,%d,%s:long write %uB pass!\r\n", __FILE__, __LINE__, __func__, (unsigned)longLen);
		}
	}
	//8.边界地址测试(首/末/区域边界)
	bndAdr[bndNum++] = 0;//首地址
	if(CONFIG_EPROM_SIZE >= 4) bndAdr[bndNum++] = CONFIG_EPROM_SIZE - 4;//末4字节
	if(CONFIG_EPROM_SIZE >= 1) bndAdr[bndNum++] = CONFIG_EPROM_SIZE - 1;//末字节
#ifdef CONFIG_EPROM_MR_END
	bndAdr[bndNum++] = CONFIG_EPROM_MR_START;
	bndAdr[bndNum++] = CONFIG_EPROM_MR_END;
	bndAdr[bndNum++] = CONFIG_EPROM_DM_START;
	bndAdr[bndNum++] = CONFIG_EPROM_DM_END;
#endif
	for(bndCnt = 0;bndCnt < bndNum;bndCnt ++){
		if(bndAdr[bndCnt] >= CONFIG_EPROM_SIZE) continue;
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);
		tempRead = 0;
		//末字节地址写1字节,其余写4字节
		if(bndAdr[bndCnt] == (CONFIG_EPROM_SIZE - 1)){
			epromWriteByte(bndAdr[bndCnt], (uint8_t*)&tempWrite);
			epromReadByte(bndAdr[bndCnt], (uint8_t*)&tempRead);
			if((tempRead & 0xFF) != (tempWrite & 0xFF)){
				printf("%s,%d,%s:boundary addr 0x%08X byte fail!\r\n", __FILE__, __LINE__, __func__, (unsigned)bndAdr[bndCnt]);
				res = false;
			}
		}
		else{
			epromWrite(bndAdr[bndCnt], (uint8_t*)&tempWrite, 4);
			epromRead(bndAdr[bndCnt], (uint8_t*)&tempRead, 4);
			if(tempRead != tempWrite){
				printf("%s,%d,%s:boundary addr 0x%08X dword fail!\r\n", __FILE__, __LINE__, __func__, (unsigned)bndAdr[bndCnt]);
				res = false;
			}
		}
	}
	printf("%s,%d,%s:boundary addr test done!\r\n", __FILE__, __LINE__, __func__);
	//9.全0/全1模式测试(FRAM无需擦除,验证0x00/0xFF直接覆盖写)
	memset(bigbuf, 0xFF, 2048);
	epromWrite(0, bigbuf, 2048);
	memset(bigbuf, 0x00, 2048);
	epromRead(0, bigbuf, 2048);
	for(i = 0;i < 2048;i ++){
		if(bigbuf[i] != 0xFF){
			printf("%s,%d,%s:all-0xFF write fail at:0x%08X!\r\n", __FILE__, __LINE__, __func__, (unsigned)i);
			res = false;
			break;
		}
	}
	memset(bigbuf, 0x00, 2048);
	epromWrite(0, bigbuf, 2048);
	memset(bigbuf, 0xFF, 2048);
	epromRead(0, bigbuf, 2048);
	for(i = 0;i < 2048;i ++){
		if(bigbuf[i] != 0x00){
			printf("%s,%d,%s:all-0x00 write fail at:0x%08X!\r\n", __FILE__, __LINE__, __func__, (unsigned)i);
			res = false;
			break;
		}
	}
	printf("%s,%d,%s:all 0xFF/0x00 mode test done!\r\n", __FILE__, __LINE__, __func__);
	//10.随机地址写入(4字节,修正:防越界)
	for(i=0;i<10000;i++){
		HAL_RNG_GenerateRandomNumber(&hrng, &bk);
		bk = bk % CONFIG_EPROM_SIZE;//0 ~ SIZE-1
		if(bk > (CONFIG_EPROM_SIZE - 4)){
			bk = CONFIG_EPROM_SIZE - 4;//防越界(写4字节需留空间)
		}
		tempWrite = HAL_RNG_GetRandomNumber(&hrng);//获取随机数据
		epromWrite(bk, ((uint8_t*)&tempWrite), 4);//写入
		epromRead(bk, ((uint8_t*)&tempRead), 4);//读取
		if(tempWrite != tempRead){
			printf("%s,%d,%s:random write fail at:0x%08X!\r\n", __FILE__, __LINE__, __func__, (unsigned)bk);
			res = false;
		}
	}
	printf("%s,%d,%s:random write pass!\r\n", __FILE__, __LINE__, __func__);
	//11.读写性能基准测试(累计计时形成性能基准: 各类操作平均耗时+吞吐量)
	printf("%s,%d,%s:perf benchmark start!\r\n", __FILE__, __LINE__, __func__);
	{
		uint32_t t0, t1, loops, k, totalW, totalR, avgUs, thrKB;
		//11.1 单字节顺序读写吞吐
		loops = 1024;
		if(loops > CONFIG_EPROM_SIZE){ loops = CONFIG_EPROM_SIZE; }
		t0 = HAL_GetTick();
		for(k = 0;k < loops;k ++){
			tempWrite = (uint8_t)(k * 13 + 7);
			epromWriteByte(k, (uint8_t*)&tempWrite);
		}
		t1 = HAL_GetTick();
		totalW = (t1 >= t0) ? (t1 - t0) : 0;
		t0 = HAL_GetTick();
		for(k = 0;k < loops;k ++){
			tempRead = 0;
			epromReadByte(k, (uint8_t*)&tempRead);
		}
		t1 = HAL_GetTick();
		totalR = (t1 >= t0) ? (t1 - t0) : 0;
		avgUs = (totalW * 1000UL) / loops;
		thrKB = (loops * 1000UL) / ((totalW > 0) ? totalW : 1);
		printf("%s,%d,%s:perf byte write %uB: %ums avg=%uus/B thr=%uKB/s\r\n", __FILE__, __LINE__, __func__, (unsigned)loops, (unsigned)totalW, (unsigned)avgUs, (unsigned)thrKB);
		avgUs = (totalR * 1000UL) / loops;
		thrKB = (loops * 1000UL) / ((totalR > 0) ? totalR : 1);
		printf("%s,%d,%s:perf byte read %uB: %ums avg=%uus/B thr=%uKB/s\r\n", __FILE__, __LINE__, __func__, (unsigned)loops, (unsigned)totalR, (unsigned)avgUs, (unsigned)thrKB);
		//11.2 64B块顺序读写吞吐
		loops = 128;
		if((loops * sizeof(wblock)) > CONFIG_EPROM_SIZE){ loops = CONFIG_EPROM_SIZE / sizeof(wblock); }
		t0 = HAL_GetTick();
		for(k = 0;k < loops;k ++){
			memset(wblock, (uint8_t)(k & 0xFF), sizeof(wblock));
			epromWrite((k * sizeof(wblock)), wblock, sizeof(wblock));
		}
		t1 = HAL_GetTick();
		totalW = (t1 >= t0) ? (t1 - t0) : 0;
		t0 = HAL_GetTick();
		for(k = 0;k < loops;k ++){
			memset(rblock, 0x00, sizeof(rblock));
			epromRead((k * sizeof(wblock)), rblock, sizeof(wblock));
		}
		t1 = HAL_GetTick();
		totalR = (t1 >= t0) ? (t1 - t0) : 0;
		avgUs = (totalW * 1000UL) / (loops * sizeof(wblock));
		thrKB = ((loops * sizeof(wblock)) * 1000UL) / ((totalW > 0) ? totalW : 1);
		printf("%s,%d,%s:perf 64B-block write %uB(%u blk): %ums avg=%uus/B thr=%uKB/s\r\n", __FILE__, __LINE__, __func__, (unsigned)(loops * sizeof(wblock)), (unsigned)loops, (unsigned)totalW, (unsigned)avgUs, (unsigned)thrKB);
		avgUs = (totalR * 1000UL) / (loops * sizeof(wblock));
		thrKB = ((loops * sizeof(wblock)) * 1000UL) / ((totalR > 0) ? totalR : 1);
		printf("%s,%d,%s:perf 64B-block read %uB(%u blk): %ums avg=%uus/B thr=%uKB/s\r\n", __FILE__, __LINE__, __func__, (unsigned)(loops * sizeof(wblock)), (unsigned)loops, (unsigned)totalR, (unsigned)avgUs, (unsigned)thrKB);
		//11.3 2048B长批量读写吞吐(直击NVFSAVE全量保存场景)
		loops = 8;
		if((loops * 2048) > CONFIG_EPROM_SIZE){ loops = CONFIG_EPROM_SIZE / 2048; }
		if(loops > 0){
			t0 = HAL_GetTick();
			for(k = 0;k < loops;k ++){
				memset(bigbuf, (uint8_t)(k & 0xFF), 2048);
				epromWrite((k * 2048), bigbuf, 2048);
			}
			t1 = HAL_GetTick();
			totalW = (t1 >= t0) ? (t1 - t0) : 0;
			t0 = HAL_GetTick();
			for(k = 0;k < loops;k ++){
				memset(bigbuf, 0x00, 2048);
				epromRead((k * 2048), bigbuf, 2048);
			}
			t1 = HAL_GetTick();
			totalR = (t1 >= t0) ? (t1 - t0) : 0;
			avgUs = (totalW * 1000UL) / (loops * 2048);
			thrKB = ((loops * 2048) * 1000UL) / ((totalW > 0) ? totalW : 1);
			printf("%s,%d,%s:perf 2048B-bulk write %uB(%u blk): %ums avg=%uus/B thr=%uKB/s\r\n", __FILE__, __LINE__, __func__, (unsigned)(loops * 2048), (unsigned)loops, (unsigned)totalW, (unsigned)avgUs, (unsigned)thrKB);
			avgUs = (totalR * 1000UL) / (loops * 2048);
			thrKB = ((loops * 2048) * 1000UL) / ((totalR > 0) ? totalR : 1);
			printf("%s,%d,%s:perf 2048B-bulk read %uB(%u blk): %ums avg=%uus/B thr=%uKB/s\r\n", __FILE__, __LINE__, __func__, (unsigned)(loops * 2048), (unsigned)loops, (unsigned)totalR, (unsigned)avgUs, (unsigned)thrKB);
		}
		//11.4 随机4B读写吞吐(寻址开销+读写)
		loops = 1000;
		t0 = HAL_GetTick();
		for(k = 0;k < loops;k ++){
			HAL_RNG_GenerateRandomNumber(&hrng, &bk);
			bk = bk % (CONFIG_EPROM_SIZE - 4);
			tempWrite = HAL_RNG_GetRandomNumber(&hrng);
			epromWrite(bk, (uint8_t*)&tempWrite, 4);
		}
		t1 = HAL_GetTick();
		totalW = (t1 >= t0) ? (t1 - t0) : 0;
		t0 = HAL_GetTick();
		for(k = 0;k < loops;k ++){
			HAL_RNG_GenerateRandomNumber(&hrng, &bk);
			bk = bk % (CONFIG_EPROM_SIZE - 4);
			epromRead(bk, (uint8_t*)&tempRead, 4);
		}
		t1 = HAL_GetTick();
		totalR = (t1 >= t0) ? (t1 - t0) : 0;
		avgUs = (totalW * 1000UL) / (loops * 4);
		thrKB = ((loops * 4) * 1000UL) / ((totalW > 0) ? totalW : 1);
		printf("%s,%d,%s:perf random-4B write %u ops: %ums avg=%uus/B thr=%uKB/s\r\n", __FILE__, __LINE__, __func__, (unsigned)loops, (unsigned)totalW, (unsigned)avgUs, (unsigned)thrKB);
		avgUs = (totalR * 1000UL) / (loops * 4);
		thrKB = ((loops * 4) * 1000UL) / ((totalR > 0) ? totalR : 1);
		printf("%s,%d,%s:perf random-4B read %u ops: %ums avg=%uus/B thr=%uKB/s\r\n", __FILE__, __LINE__, __func__, (unsigned)loops, (unsigned)totalR, (unsigned)avgUs, (unsigned)thrKB);
	}
	printf("%s,%d,%s:perf benchmark done!\r\n", __FILE__, __LINE__, __func__);
	return res;
}
