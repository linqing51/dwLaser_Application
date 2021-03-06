#include "MainAppLib.h"
/*****************************************************************************/
int16_t pulseWidthAdd(int16_t ps){//脉宽增加
	if(ps >= 1 && ps < 10){
		ps += 1;
	}
	else if(ps >= 10 && ps < 100){
		ps += 10;
	}
	else if(ps >= 100 && ps < 1000){
		ps += 50;
	}
	else if(ps >= 1000 && ps < 10000){
		ps += 1000;
	}
	return ps;
}
int16_t pulseWidthDec(int16_t ps){//脉宽减少
	if(ps > 1 && ps <= 10){
		ps -= 1;
	}
	else if(ps > 10 && ps <= 100){
		ps -= 10;
	}
	else if(ps > 100 && ps <= 1000){
		ps -= 50;
	}
	else if(ps > 1000 && ps <= 10000){
		ps -= 1000;
	}
	return ps;
}
void loadDefault(void){//恢复默认值
	uint8_t i;	
	RRES(MR_FOOSWITCH_HAND_SWITCH);
	RRES(MR_BEEM_TONE);			
	RRES(R_DISABLE_RFID);
	RRES(R_DISABLE_FIBER_PROBE);
	RRES(R_DISABLE_FAN_SPEED);
	NVRAM0[DM_BEEM_VOLUME] = CONFIG_MAX_BEEM_VOLUME;
	NVRAM0[DM_AIM_BRG] = CONFIG_MAX_AIM_BRG;
	NVRAM0[DM_LCD_BRG] = CONFIG_MAX_LCD_BRG;
	NVSAV();//强制储存NVRAM
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM;i ++){
		NVRAM0[DM_SCHEME_NUM] = i;
		defaultScheme();
		saveScheme();
	}
	NVRAM0[DM_SCHEME_NUM] = 0;
	FDSAV();
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

void defaultScheme(void){//当前选择方案恢复默认值						
	sprintf((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]),"Hello dwLaser S%d", (NVRAM0[DM_SCHEME_NUM] + 1));		
	NVRAM0[EM_LASER_SELECT]	= LASER_SELECT_ALL;//通道选择
	NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;//脉冲模式
	NVRAM0[EM_LASER_POWER_CH0] = NVRAM0[DM_SCHEME_NUM] * 5 + 20;//通道0功率
	NVRAM0[EM_LASER_POWER_CH1] = NVRAM0[DM_SCHEME_NUM] * 2 + 10;//通道1功率
	NVRAM0[EM_LASER_SP_POSWIDTH]= 500;//单脉冲正脉宽
	NVRAM0[EM_LASER_MP_POSWIDTH]= 400;//多脉冲正脉宽
	NVRAM0[EM_LASER_MP_NEGWIDTH]= 300;//多脉冲负脉宽
	NVRAM0[EM_LASER_GP_POSWIDTH]= 600;//Group脉冲正脉宽
	NVRAM0[EM_LASER_GP_NEGWIDTH]= 700;//Group脉冲负脉宽
	NVRAM0[EM_LASER_GP_TIMES] =	20;//Group脉冲数
	NVRAM0[EM_LASER_GP_GROUP_OFF] = 500;//Group脉冲间隔
	NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = CONFIG_MIN_LASER_ENERGY_INTERVAL;//EVLA_SIGNAL能量间隔
	NVRAM0[EM_LASER_DERMA_POSWIDTH]	= 550;//DERMA正脉宽
	NVRAM0[EM_LASER_DERMA_NEGWIDTH]	= 650;//DERMA负脉宽
	NVRAM0[EM_LASER_DERMA_SPOT_SIZE] = DERMA_SPOT_SIZE_0MM5;//DERMA光斑直径
}

void loadScheme(void){//FD->EM
	uint8_t *psrc, *pdist;
	if(NVRAM0[DM_SCHEME_NUM] > 31){
#if CONFIG_DEBUG_APP == 1
		printf("App->loadScheme:NVRAM0[DM_SCHEME_NUM] > 31 !\n");
#endif
		NVRAM0[DM_SCHEME_NUM] = 31;
	}
	if(NVRAM0[DM_SCHEME_NUM] < 0){
#if CONFIG_DEBUG_APP == 1
		printf("App->loadScheme:NVRAM0[DM_SCHEME_NUM] < 0 !\n");
#endif
		NVRAM0[DM_SCHEME_NUM] = 0;
	}
	psrc = (uint8_t*)&FDRAM[(FD_SCHEME_START_0 + NVRAM0[DM_SCHEME_NUM] * 64)];
	pdist = (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME];
	memcpy(pdist, psrc, ((FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1) * 2));
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			break;
		}
		case LASER_MODE_SP:{
			break;
		}
		case LASER_MODE_MP:{
			break;
		}
		case LASER_MODE_GP:{
			break;
		}
		case LASER_MODE_SIGNAL:{
			break;
		}
		case LASER_MODE_DERMA:{
			break;
		}
		default:{
#if CONFIG_DEBUG_APP == 1
			printf("App->loadScheme:load default scheme!\n");
#endif			
			defaultScheme();
			break;
		}
	}
#if CONFIG_USING_SINGLE_WAVE == 1
	NVRAM0[EM_LASER_POWER_CH1] = 0;
	NVRAM0[EM_LASER_POWER_CH2] = 0;
	NVRAM0[EM_LASER_POWER_CH3] = 0;
#endif
#if CONFIG_USING_DUAL_WAVE == 1
#endif
#if CONFIG_USING_TRIPE_WAVE	== 1
#endif
#if CONFIG_USING_QUAD_WAVE == 1
#endif
#if CONFIG_USING_FIVE_WAVE == 1
#endif
#if CONFIG_HMI_SCHEME_NUM == 1
#endif
}
void saveScheme(void){//EM->FD
	uint8_t *psrc, *pdist;
	if(NVRAM0[DM_SCHEME_NUM] > (CONFIG_HMI_SCHEME_NUM - 1))
		NVRAM0[DM_SCHEME_NUM] = (CONFIG_HMI_SCHEME_NUM - 1);
	if(NVRAM0[DM_SCHEME_NUM] < 0)
		NVRAM0[DM_SCHEME_NUM] = 0;
	pdist = (uint8_t*)&FDRAM[NVRAM0[DM_SCHEME_NUM] * 64];
	psrc = (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME];
	memcpy(pdist, psrc, 128);
}
int8_t checkScheme(int8_t cn){
	uint16_t strSize;
	int16_t temp;
	char *pstr;
	if(cn < 0){
		cn = 0;
	}
	if(cn > CONFIG_HMI_SCHEME_NUM){
		cn = CONFIG_HMI_SCHEME_NUM;
	}
	pstr = (char*)&FDRAM[cn * 30 + FD_LASER_SCHEME_NAME];//方案名称
	strSize = strlen(pstr);
	if(strSize > 30){//名称长度错误
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_SELECT];//通道选择
	if((temp != LASER_SELECT_CH0) || 
	   (temp != LASER_SELECT_CH1) ||
       (temp != LASER_SELECT_ALL)){
		return false;
	}		
	temp = FDRAM[cn * 30 + FD_LASER_PULSE_MODE];//脉冲模式
	if((temp != LASER_MODE_CW) || (temp != LASER_MODE_SP) || (temp != LASER_MODE_MP) || (temp != LASER_MODE_GP) ||
 	   (temp != LASER_MODE_SIGNAL) || (temp != LASER_MODE_DERMA)){
		return false;
	}
	
	temp = FDRAM[cn * 30 + FD_LASER_POWER_CH0];//通道0功率
	if(temp < CONFIG_MIN_LASERPOWER_CH0 || temp > CONFIG_MAX_LASERPOWER_CH0){
		return false;
	}
	
	temp = FDRAM[cn + 30 + FD_LASER_POWER_CH1];//通道1功率
	if(temp < CONFIG_MIN_LASERPOWER_CH1 || temp > CONFIG_MAX_LASERPOWER_CH1){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_SP_POSWIDTH];//单脉冲正脉宽
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_MP_POSWIDTH];//多脉冲正脉宽
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_MP_NEGWIDTH];////多脉冲负脉宽
	if(temp < CONFIG_MIN_LASER_NEGWIDTH || temp > CONFIG_MAX_LASER_NEGWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_GP_POSWIDTH];//Group脉冲正脉宽
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_GP_NEGWIDTH];//Group脉冲负脉宽
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_GP_TIMES];//Group脉冲数
	if(temp < CONFIG_MIN_LASER_TIMES || temp > CONFIG_MAX_LASER_TIMES){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_GP_GROUP_OFF];//Group脉冲间隔
	if(temp < CONFIG_MIN_LASER_GROUP_OFF || temp > CONFIG_MAX_LASER_GROUP_OFF){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_SIGNAL_ENERGY_INTERVAL];////SIGNAL能量间隔
	if(temp < CONFIG_MIN_LASER_ENERGY_INTERVAL || temp > CONFIG_MAX_LASER_ENERGY_INTERVAL){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_DERMA_POSWIDTH];//DERMA正脉宽
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_DERMA_NEGWIDTH];//DERMA负脉宽
	if(temp < CONFIG_MIN_LASER_NEGWIDTH || temp > CONFIG_MAX_LASER_NEGWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_DERMA_SPOT_SIZE];//DERMA光斑直径
	if((temp != DERMA_SPOT_SIZE_0MM5) ||
	   (temp != DERMA_SPOT_SIZE_1MM0) ||
	   (temp != DERMA_SPOT_SIZE_2MM0) ||
	   (temp != DERMA_SPOT_SIZE_3MM0)){
		return false;
	}
	return true;
}
uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg){//功率->DAC CODE
	fp32_t fin, ftemp0, ftemp1, ftemp2, ftemp3;
	int16_t out;
	if(ch > 8){
		ch = 8;
	}
	fin = (fp32_t)power;	
	//进行3次多项式拟合Y = A*X^3 + B*X^2 + C*X + D
	ftemp0 = pow((fp64_t)fin, 3) * pcfg->laserNotesB3[ch];//3次方
	ftemp1 = pow((fp64_t)fin, 2) * pcfg->laserNotesB2[ch];//2次方
	ftemp2 = (fp32_t)fin * pcfg->laserNotesB1[ch];//1次方
	ftemp3 = ftemp0 + ftemp1 + ftemp2 + pcfg->laserNotesIntercept[ch];
	if(ftemp3 >= 0xFFFF){
		ftemp3 = 0xFFFF;
	}
	if(ftemp3 < 0x0){
		ftemp3 = 0;
	}
	out = (uint16_t)ftemp3;
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





