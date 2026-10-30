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
		printf("%s,%d,%s:hword(16bit) sequential write+CRC fail!\r\n", __FILE__, __LINE__, __func__);
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
		printf("%s,%d,%s:dword(32bit) sequential write+CRC fail!\r\n", __FILE__, __LINE__, __func__);
		res = false;
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
	return res;
}
