#include "MainAppLib.h"
/*****************************************************************************/
void addAcousticTime(void){//增加提示时间 +STEP
	NVRAM0[EM_ACOUSTIC_TIME] += NVRAM0[EM_ACOUSTIC_TIME_STEP];
	LIMS16(EM_ACOUSTIC_TIME, EM_ACOUSTIC_TIME_MIN, EM_ACOUSTIC_TIME_MAX);
	NVRAM0[EM_ACOUSTIC_ENERGY] += NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
	LIMS16(EM_ACOUSTIC_ENERGY, EM_ACOUSTIC_ENERGY_MIN, EM_ACOUSTIC_ENERGY_MAX);
}
void decAcousticTime(void){//减小提示时间 -STEP
	NVRAM0[EM_ACOUSTIC_TIME] -= NVRAM0[EM_ACOUSTIC_TIME_STEP];
	LIMS16(EM_ACOUSTIC_TIME, EM_ACOUSTIC_TIME_MIN, EM_ACOUSTIC_TIME_MAX);
	NVRAM0[EM_ACOUSTIC_ENERGY] -= NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
	LIMS16(EM_ACOUSTIC_ENERGY, EM_ACOUSTIC_ENERGY_MIN, EM_ACOUSTIC_ENERGY_MAX);
}
void addAcousticEnergy(void){//增加提示能量 +STEP
	NVRAM0[EM_ACOUSTIC_TIME] += NVRAM0[EM_ACOUSTIC_TIME_STEP];
	LIMS16(EM_ACOUSTIC_TIME, EM_ACOUSTIC_TIME_MIN, EM_ACOUSTIC_TIME_MAX);
	NVRAM0[EM_ACOUSTIC_ENERGY] += NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
	LIMS16(EM_ACOUSTIC_ENERGY, EM_ACOUSTIC_ENERGY_MIN, EM_ACOUSTIC_ENERGY_MAX);
}
void decAcousticEnergy(void){//减小提示能量 -STEP
	NVRAM0[EM_ACOUSTIC_TIME] -= NVRAM0[EM_ACOUSTIC_TIME_STEP];
	LIMS16(EM_ACOUSTIC_TIME, EM_ACOUSTIC_TIME_MIN, EM_ACOUSTIC_TIME_MAX);
	NVRAM0[EM_ACOUSTIC_ENERGY] -= NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
	LIMS16(EM_ACOUSTIC_ENERGY, EM_ACOUSTIC_ENERGY_MIN, EM_ACOUSTIC_ENERGY_MAX);
}

int16_t keyRuleAdd(int16_t ps, int16_t max){//增加
	if(ps >= 1 && ps < 10){
		ps += 1;
	}
	else if(ps >= 10 && ps < 100){
		ps += 10;
	}
	else if(ps >= 100 && ps < 1000){
		ps += 50;
	}
	else if(ps >= 1000 && ps < 32000){
		ps += 1000;
	}
	if(ps >= max){
		ps = max;
	}
	return ps;
}
int16_t keyRuleDec(int16_t ps, int16_t min){//减少
	if(ps > 1 && ps <= 10){
		ps -= 1;
	}
	else if(ps > 10 && ps <= 100){
		ps -= 10;
	}
	else if(ps > 100 && ps <= 1000){
		ps -= 50;
	}
	else if(ps > 1000 && ps <= 32000){
		ps -= 1000;
	}
	if(ps <= min){
		ps = min;
	}
	return ps;
}

void restoreDefault(void){//恢复默认值
	RRES(MR_FOOSWITCH_HAND_SWITCH);
	RRES(MR_BEEP_TONE);			
	RRES(R_DISABLE_RFID);
	RRES(R_DISABLE_FIBER_PROBE);
	RRES(R_DISABLE_FAN_SPEED);
	NVRAM0[DM_BEEM_VOLUME] = CONFIG_BEEM_MAX_VOLUME / 2;
	NVRAM0[DM_AIM_BRG] = CONFIG_MAX_LASER_POWER_650;
	NVRAM0[DM_LCD_BRG] = CONFIG_LCD_MAX_DC;
	schemeInit(1);//初始化自定义方案
#if defined(MODEL_PVGLS_TRI) || defined(MODEL_PVGLS_TRI_COMBINE) //三波长
	NVRAM0[DM_SCHEME_CLASSIFY] = SCHEME_PHLEBOLOGY;
	NVRAM0[DM_SCHEME_INDEX] = 0;
#endif
#if defined(MODEL_PVGLS_7W_1940) || defined(MODEL_PVGLS_15W_1470)
	NVRAM0[DM_SCHEME_CLASSIFY] = SCHEME_CUSTIOM;
	NVRAM0[DM_SCHEME_INDEX] = 0;
#endif

	FDSAV();
	NVFSAVE();
}

uint8_t getLcdDuty(int16_t LcdBrg){//屏幕亮度值转换为占空比
	uint16_t temp;
	LcdBrg = 100 - LcdBrg; 
	if(LcdBrg <= 0)
		LcdBrg = 0;
	if(LcdBrg >= 80)
		LcdBrg = 80;
	temp = LcdBrg * 255;
	temp = temp / 100;
	return (uint8_t)(temp);
}

void updateCustomScheme(uint8_t index){//EM->FD
	uint8_t *psrc, *pdist;
	pdist = (uint8_t*)&FDRAM0[index * (FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1)];
	psrc = (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME];
	memcpy(pdist, psrc, ((FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1) * 2));
}

uint16_t fitLaserToCodeLine(uint8_t ch, int16_t power){//功率->DAC CODE 使用默认拟合校正表
	uint16_t tmp;
	switch(ch){
		case LASER_CHANNEL_1470:{
			tmp = (uint16_t)((int32_t)power * 4095 / CONFIG_MAX_LASER_POWER_1470);
			break;
		}
		case LASER_CHANNEL_980:{
			tmp = (uint16_t)((int32_t)power * 4095 / CONFIG_MAX_LASER_POWER_980);
			break;
		}
		default:{
			tmp = 0;
			break;
		}
	}
	return tmp;
}
uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg){//功率->DAC CODE 使用校正表
	double fpower, fout, fk, fb;
	int16_t pmax, pmin;
	uint16_t *pCal;
	uint16_t out;
	switch(ch){
		case LASER_CHANNEL_1470:{
			pmax = (int16_t)CONFIG_MAX_LASER_POWER_1470;
			pmin = (int16_t)CONFIG_MIN_LASER_POWER_1470;
			pCal = deviceConfig.calibrationPwr0;
			break;
		}
		case LASER_CHANNEL_980:{
			pmax = (int16_t)CONFIG_MAX_LASER_POWER_980;
			pmin = (int16_t)CONFIG_MIN_LASER_POWER_980;
			pCal = deviceConfig.calibrationPwr1;
			break;
		}
		case LASER_CHANNEL_1940:{
			pmax = (int16_t)CONFIG_MAX_LASER_POWER_1940;
			pmin = (int16_t)CONFIG_MIN_LASER_POWER_1940;
			pCal = deviceConfig.calibrationPwr2;//1940与1470相同通道
			break;
		}
		default:{
			break;
		}
	}
	if(power > pmax){
		power = pmax;
	}
	if(power < pmin){
		power = pmin;
	}
	fpower = (float)power;
	printf("%s,%d,%s:Calibration input power = %d\n", __FILE__, __LINE__, __func__, power);
	printf("%s,%d,%s:Calibration max power = %d\n", __FILE__, __LINE__, __func__, pmax);
	printf("%s,%d,%s:Calibration min power = %d\n", __FILE__, __LINE__, __func__, pmin);
	if(LDB(R_CALIBRATION_MODE)){//正模式
		//通过校正表计算DAC值
		if(power > 0 && (power <= pCal[0])){//0-10%
			fk = pCal[0] / 0.1F;
			fb = 0.0F;
			//fb = pCal[0] - fk * 0.1;
		}
		else if((power > pCal[0]) && (power <= pCal[1])){//10-20%
			fk = (pCal[1] - pCal[0]) / 0.1F;
			fb = pCal[0] - fk * 0.1;
		}
		else if((power > pCal[1]) && (power <= pCal[2])){//20-30%
			fk = (pCal[2] - pCal[1]) / 0.1F;
			fb = pCal[1] - fk * 0.2;
		}
		else if((power > pCal[2]) && (power <= pCal[3])){
			fk = (pCal[3] - pCal[2]) / 0.1F;
			fb = pCal[2] - fk * 0.3;
		}
		else if((power > pCal[3]) && (power <= pCal[4])){
			fk = (pCal[4] - pCal[3]) / 0.1F;
			fb = pCal[3] - fk * 0.4;
		}
		else if((power > pCal[4]) && (power <= pCal[5])){
			fk = (pCal[5] - pCal[4]) / 0.1F;
			fb = pCal[4] - fk * 0.5;
		}
		else if((power > pCal[5]) && (power <= pCal[6])){
			fk = (pCal[6] - pCal[5]) / 0.1F;
			fb = pCal[5] - fk * 0.6;
		}
		else if((power > pCal[6]) && (power <= pCal[7])){
			fk = (pCal[7] - pCal[6]) / 0.1F;
			fb = pCal[6] - fk * 0.7;
		}
		else if((power > pCal[7]) && (power <= pCal[8])){
			fk = (pCal[8] - pCal[7]) / 0.1F;
			fb = pCal[7] - fk * 0.8;
		}
		else if((power > pCal[8]) && (power <= pCal[9])){
			fk = (pCal[9] - pCal[8]) / 0.1F;
			fb = pCal[8] - fk * 0.9;
		}
		fout = (power - fb) / fk;
		printf("%s,%d,%s:Enable calibration mode\n", __FILE__, __LINE__, __func__);
		printf("%s,%d,%s:Calibration fK=%f, fB=%f\n", __FILE__, __LINE__, __func__, fk, fb);
		printf("%s,%d,%s:Calibration fOut=%f\n", __FILE__, __LINE__, __func__, fout);
	}
	else{//功率校正模式 ->按等比输出DAC值
		printf("%s,%d,%s:Disable calibration mode\n", __FILE__, __LINE__, __func__);
		fout = fpower / pmax;			
	}
	fout = fout * 4095.0F;
	if(fout > 4095.0F){
		fout = 4095;
	}
	if(fout < 0.0F){
		fout = 0;
	}
	out = (uint16_t)fout;
	printf("%s,%d,%s:Calibration fOut=%d\n", __FILE__, __LINE__, __func__, out);
	return out;
}

uint8_t saveSchemeToUdisk(void){//将FDRAM写入USB DISK
	//返回 1:写入成功 0:写入失败
//	FRESULT retUsbH;
//	FATFS	USBH_fatfs;
//	FIL saveFile;//FATFS File Object 下载完成信息
//	FILINFO FileInfo;//FATFS 文件信息
//	char fileName[64];
//	retUsbH = f_mount(&USBH_fatfs, FATFS_ROOT, 0);
//	if(retUsbH != FR_OK){//挂载U盘失败
//		printf("Bootloader:Mount Fatfs errror:%d!\n", retUsbH);
//		return false
//	}
//	else{//挂载U盘成功
//		printf("Bootloader:Mount Fatfs sucess!\n");
//	}
//	sprintf(fileName, "/las.cfg");
//	retUsbH = f_open(&saveFile, CFG_FIRMWARE_FILENAME, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);//读取完成信息文件
//	if(retUsbH != FR_OK){//读取失败跳过固件更新直接运行程序
//		printf("BootLoader:Open %s fail,ECODE=0x%02XH\n", CFG_FIRMWARE_FILENAME, retUsbH);
//	}
//	else{//读取成功检查文件内容
//		f_lseek(&CfgFile, 0);//读取指针移动到开头
//		if(f_write(&CfgFile, fileBuff, 3, (void *)&bwByte) != FR_OK){
//				bootLoadFailHandler(BT_FAIL_WRITE_CFG);
//			}
//			f_close(&CfgFile);
//	}
	return 0;
}
uint8_t loadSchemeFromUdisk(void){//从USB DISK载入FDRAM
	//返回 1:写入成功 0:写入失败
	return 0;
}

int16_t IncPidCalc(IncPid_t *t, int16_t ref, int16_t fb){//增量PID
	float tmp0, tmp1, tmp2, fout;
	t->ek0 = (ref - fb) * -1.0F;
	if((t->ek0 >= -1) && (t->ek0 <= 1) ){//死区消抖
		t->ek0 = 0;
	}
	tmp0 = t->kp * t->ek0;
	tmp1 = t->ki * t->ek1;
	tmp2 = t->kd * t->ek2;
	fout = tmp0 - tmp1 + tmp2;
	t->ek2 = t->ek1;
	t->ek1 = t->ek0;
	return (int16_t)(fout);
}	






