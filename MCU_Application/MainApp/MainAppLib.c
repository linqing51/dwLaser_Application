#include "MainAppLib.h"
/*****************************************************************************/
int16_t pulseWidthAdd(int16_t ps){//��������
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
int16_t pulseWidthDec(int16_t ps){//�������
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
void loadDefault(void){//�ָ�Ĭ��ֵ
	uint8_t i;	
	RRES(MR_FOOSWITCH_HAND_SWITCH);
	RRES(MR_BEEM_TONE);			
	RRES(R_DISABLE_RFID);
	RRES(R_DISABLE_FIBER_PROBE);
	RRES(R_DISABLE_FAN_SPEED);
	NVRAM0[DM_BEEM_VOLUME] = CONFIG_MAX_BEEM_VOLUME;
	NVRAM0[DM_AIM_BRG] = CONFIG_MAX_AIM_BRG;
	NVRAM0[DM_LCD_BRG] = CONFIG_MAX_LCD_BRG;
	NVSAV();//ǿ�ƴ���NVRAM
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM;i ++){
		NVRAM0[DM_SCHEME_NUM] = i;
		defaultScheme();
		saveScheme();
	}
	NVRAM0[DM_SCHEME_NUM] = 0;
	FDSAV();
}
uint8_t getLcdDuty(int16_t LcdBrg){//��Ļ����ֵת��Ϊռ�ձ�
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

void defaultScheme(void){//��ǰѡ�񷽰��ָ�Ĭ��ֵ						
	char *psrc, *pdist;
	sprintf((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]),"Hello dwLaser S%d", (NVRAM0[DM_SCHEME_NUM] + 1));		
	NVRAM0[EM_LASER_SELECT]	= LASER_SELECT_ALL;//ͨ��ѡ��
	NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;//����ģʽ
	NVRAM0[EM_LASER_POWER_CH0] = NVRAM0[DM_SCHEME_NUM] * 5 + 20;//ͨ��0����
	NVRAM0[EM_LASER_POWER_CH1] = NVRAM0[DM_SCHEME_NUM] * 2 + 10;//ͨ��1����
	NVRAM0[EM_LASER_SP_POSWIDTH]= 500;//������������
	NVRAM0[EM_LASER_MP_POSWIDTH]= 400;//������������
	NVRAM0[EM_LASER_MP_NEGWIDTH]= 300;//�����帺����
	NVRAM0[EM_LASER_GP_POSWIDTH]= 600;//Group����������
	NVRAM0[EM_LASER_GP_NEGWIDTH]= 700;//Group���帺����
	NVRAM0[EM_LASER_GP_TIMES] =	20;//Group������
	NVRAM0[EM_LASER_GP_GROUP_OFF] = 500;//Group������
	NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = CONFIG_MIN_LASER_ENERGY_INTERVAL;//EVLA_SIGNAL�������
	NVRAM0[EM_LASER_DERMA_POSWIDTH]	= 550;//DERMA������
	NVRAM0[EM_LASER_DERMA_NEGWIDTH]	= 650;//DERMA������
	NVRAM0[EM_LASER_DERMA_SPOT_SIZE] = DERMA_SPOT_SIZE_0MM5;//DERMA���ֱ��
#if	CONFIG_SPLC_USING_DEFAULT_SCHEME == 1
	switch(NVRAM0[DM_SCHEME_NUM]){
		case 0:{
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[0]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 80;//8.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 80;//EVLA_SIGNAL�������
			break;
		}
		case 1:{
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[1]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 60;//8.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 60;//EVLA_SIGNAL�������
			break;
		}
		case 2:{
			//psrc = (char*)PRE_SCHEME_TABLE[2];
			//pdist = (char*)&NVRAM0[EM_LASER_SCHEME_NAME];
			//memcpy(pdist, psrc, CONFIG_MAX_SCHEME_NAME_SIZE);
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[2]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 30;//8.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 30;//EVLA_SIGNAL�������
			break;
		}
		case 3:{
			//psrc = (char*)PRE_SCHEME_TABLE[3];
			//pdist = (char*)&NVRAM0[EM_LASER_SCHEME_NAME];
			//memcpy(pdist, psrc, CONFIG_MAX_SCHEME_NAME_SIZE);
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[3]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 60;//6.0W
			NVRAM0[EM_LASER_GP_POSWIDTH]= 3000;//Ton 3S
			break;
		}
		case 4:{
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[4]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 70;//7.0W
			NVRAM0[EM_LASER_GP_POSWIDTH]= 3000;//Ton 3S
			break;
		}
		case 5:{
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[5]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 80;//8.0W
			NVRAM0[EM_LASER_GP_POSWIDTH]= 3000;//Ton 3S
			break;
		}
		case 6:{
			//psrc = (char*)PRE_SCHEME_TABLE[6];
			//pdist = (char*)&NVRAM0[EM_LASER_SCHEME_NAME];
			//memcpy(pdist, psrc, CONFIG_MAX_SCHEME_NAME_SIZE);
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[6]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 100;//10.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 100;//EVLA_SIGNAL�������
			break;
		}
		case 7:{
			//psrc = (char*)PRE_SCHEME_TABLE[7];
			//pdist = (char*)&NVRAM0[EM_LASER_SCHEME_NAME];
			//memcpy(pdist, psrc, CONFIG_MAX_SCHEME_NAME_SIZE);
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[7]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 100;//10.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 100;//EVLA_SIGNAL�������
			break;
		}
		case 8:{
			//psrc = (char*)PRE_SCHEME_TABLE[8];
			//pdist = (char*)&NVRAM0[EM_LASER_SCHEME_NAME];
			//memcpy(pdist, psrc, CONFIG_MAX_SCHEME_NAME_SIZE);
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[8]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 70;//7.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 100;//EVLA_SIGNAL�������
			break;
		}
		case 9:{
			//psrc = (char*)PRE_SCHEME_TABLE[9];
			//pdist = (char*)&NVRAM0[EM_LASER_SCHEME_NAME];
			//memcpy(pdist, psrc, CONFIG_MAX_SCHEME_NAME_SIZE);
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[9]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_CH0] = 70;//7.0W
			NVRAM0[EM_LASER_MP_POSWIDTH]= 1000;//������������ 1S
			NVRAM0[EM_LASER_MP_NEGWIDTH]= 5000;//�����帺���� 5S
			break;
		}
		case 10:{
			//psrc = (char*)PRE_SCHEME_TABLE[10];
			//pdist = (char*)&NVRAM0[EM_LASER_SCHEME_NAME];
			//memcpy(pdist, psrc, CONFIG_MAX_SCHEME_NAME_SIZE);
			memset((char*)&NVRAM0[EM_LASER_SCHEME_NAME], 0x0, ((EM_LASER_SELECT - EM_LASER_SCHEME_NAME - 1) * 2));
			sprintf((char*)&NVRAM0[EM_LASER_SCHEME_NAME], "%s", PRE_SCHEME_TABLE[10]);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_CH0] = 70;//7.0W
			NVRAM0[EM_LASER_MP_POSWIDTH]= 1000;//������������ 1S
			NVRAM0[EM_LASER_MP_NEGWIDTH]= 5000;//�����帺���� 5S
			break;
		}
		default:break;
	}
#endif
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
	psrc = (uint8_t*)&FDRAM[FD_SCHEME_START_0 + (NVRAM0[DM_SCHEME_NUM] * 64)];
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
	pstr = (char*)&FDRAM[cn * 30 + FD_LASER_SCHEME_NAME];//��������
	strSize = strlen(pstr);
	if(strSize > 30){//���Ƴ��ȴ���
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_SELECT];//ͨ��ѡ��
	if((temp != LASER_SELECT_CH0) || 
	   (temp != LASER_SELECT_CH1) ||
       (temp != LASER_SELECT_ALL)){
		return false;
	}		
	temp = FDRAM[cn * 30 + FD_LASER_PULSE_MODE];//����ģʽ
	if((temp != LASER_MODE_CW) || (temp != LASER_MODE_SP) || (temp != LASER_MODE_MP) || (temp != LASER_MODE_GP) ||
 	   (temp != LASER_MODE_SIGNAL) || (temp != LASER_MODE_DERMA)){
		return false;
	}
	
	temp = FDRAM[cn * 30 + FD_LASER_POWER_CH0];//ͨ��0����
	if(temp < CONFIG_MIN_LASERPOWER_CH0 || temp > CONFIG_MAX_LASERPOWER_CH0){
		return false;
	}
	
	temp = FDRAM[cn + 30 + FD_LASER_POWER_CH1];//ͨ��1����
	if(temp < CONFIG_MIN_LASERPOWER_CH1 || temp > CONFIG_MAX_LASERPOWER_CH1){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_SP_POSWIDTH];//������������
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_MP_POSWIDTH];//������������
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_MP_NEGWIDTH];////�����帺����
	if(temp < CONFIG_MIN_LASER_NEGWIDTH || temp > CONFIG_MAX_LASER_NEGWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_GP_POSWIDTH];//Group����������
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_GP_NEGWIDTH];//Group���帺����
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_GP_TIMES];//Group������
	if(temp < CONFIG_MIN_LASER_TIMES || temp > CONFIG_MAX_LASER_TIMES){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_GP_GROUP_OFF];//Group������
	if(temp < CONFIG_MIN_LASER_GROUP_OFF || temp > CONFIG_MAX_LASER_GROUP_OFF){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_SIGNAL_ENERGY_INTERVAL];////SIGNAL�������
	if(temp < CONFIG_MIN_LASER_ENERGY_INTERVAL || temp > CONFIG_MAX_LASER_ENERGY_INTERVAL){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_DERMA_POSWIDTH];//DERMA������
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_DERMA_NEGWIDTH];//DERMA������
	if(temp < CONFIG_MIN_LASER_NEGWIDTH || temp > CONFIG_MAX_LASER_NEGWIDTH){
		return false;
	}
	temp = FDRAM[cn * 30 + FD_LASER_DERMA_SPOT_SIZE];//DERMA���ֱ��
	if((temp != DERMA_SPOT_SIZE_0MM5) ||
	   (temp != DERMA_SPOT_SIZE_1MM0) ||
	   (temp != DERMA_SPOT_SIZE_2MM0) ||
	   (temp != DERMA_SPOT_SIZE_3MM0)){
		return false;
	}
	return true;
}
uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg){//����->DAC CODE
	fp32_t fin, ftemp0, ftemp1, ftemp2, ftemp3;
	int16_t out;
	if(ch > 8){
		ch = 8;
	}
	fin = (fp32_t)power;	
	//����3�ζ���ʽ���Y = A*X^3 + B*X^2 + C*X + D
	ftemp0 = pow((fp64_t)fin, 3) * pcfg->laserNotesB3[ch];//3�η�
	ftemp1 = pow((fp64_t)fin, 2) * pcfg->laserNotesB2[ch];//2�η�
	ftemp2 = (fp32_t)fin * pcfg->laserNotesB1[ch];//1�η�
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

uint8_t saveSchemeToUdisk(void){//��FDRAMд��USB DISK
	//���� 1:д��ɹ� 0:д��ʧ��
//	FRESULT retUsbH;
//	FATFS	USBH_fatfs;
//	FIL saveFile;//FATFS File Object ���������Ϣ
//	FILINFO FileInfo;//FATFS �ļ���Ϣ
//	char fileName[64];
//	retUsbH = f_mount(&USBH_fatfs, FATFS_ROOT, 0);
//	if(retUsbH != FR_OK){//����U��ʧ��
//		printf("Bootloader:Mount Fatfs errror:%d!\n", retUsbH);
//		return false
//	}
//	else{//����U�̳ɹ�
//		printf("Bootloader:Mount Fatfs sucess!\n");
//	}
//	sprintf(fileName, "/las.cfg");
//	retUsbH = f_open(&saveFile, CFG_FIRMWARE_FILENAME, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);//��ȡ�����Ϣ�ļ�
//	if(retUsbH != FR_OK){//��ȡʧ�������̼�����ֱ�����г���
//		printf("BootLoader:Open %s fail,ECODE=0x%02XH\n", CFG_FIRMWARE_FILENAME, retUsbH);
//	}
//	else{//��ȡ�ɹ�����ļ�����
//		f_lseek(&CfgFile, 0);//��ȡָ���ƶ�����ͷ
//		if(f_write(&CfgFile, fileBuff, 3, (void *)&bwByte) != FR_OK){
//				bootLoadFailHandler(BT_FAIL_WRITE_CFG);
//			}
//			f_close(&CfgFile);
//	}
	return 0;
}
uint8_t loadSchemeFromUdisk(void){//��USB DISK����FDRAM
	//���� 1:д��ɹ� 0:д��ʧ��
	return 0;
}





