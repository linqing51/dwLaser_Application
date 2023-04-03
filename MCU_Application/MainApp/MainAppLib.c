#include "MainAppLib.h"
/*****************************************************************************/
void addAcousticTime(void){//������ʾʱ�� +STEP
	NVRAM0[EM_ACOUSTIC_TIME] += NVRAM0[EM_ACOUSTIC_TIME_STEP];
	LIMS16(EM_ACOUSTIC_TIME, EM_ACOUSTIC_TIME_MIN, EM_ACOUSTIC_TIME_MAX);
	NVRAM0[EM_ACOUSTIC_ENERGY] += NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
	LIMS16(EM_ACOUSTIC_ENERGY, EM_ACOUSTIC_ENERGY_MIN, EM_ACOUSTIC_ENERGY_MAX);
}
void decAcousticTime(void){//��С��ʾʱ�� -STEP
	NVRAM0[EM_ACOUSTIC_TIME] -= NVRAM0[EM_ACOUSTIC_TIME_STEP];
	LIMS16(EM_ACOUSTIC_TIME, EM_ACOUSTIC_TIME_MIN, EM_ACOUSTIC_TIME_MAX);
	NVRAM0[EM_ACOUSTIC_ENERGY] -= NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
	LIMS16(EM_ACOUSTIC_ENERGY, EM_ACOUSTIC_ENERGY_MIN, EM_ACOUSTIC_ENERGY_MAX);
}
void addAcousticEnergy(void){//������ʾ���� +STEP
	NVRAM0[EM_ACOUSTIC_TIME] += NVRAM0[EM_ACOUSTIC_TIME_STEP];
	LIMS16(EM_ACOUSTIC_TIME, EM_ACOUSTIC_TIME_MIN, EM_ACOUSTIC_TIME_MAX);
	NVRAM0[EM_ACOUSTIC_ENERGY] += NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
	LIMS16(EM_ACOUSTIC_ENERGY, EM_ACOUSTIC_ENERGY_MIN, EM_ACOUSTIC_ENERGY_MAX);
}
void decAcousticEnergy(void){//��С��ʾ���� -STEP
	NVRAM0[EM_ACOUSTIC_TIME] -= NVRAM0[EM_ACOUSTIC_TIME_STEP];
	LIMS16(EM_ACOUSTIC_TIME, EM_ACOUSTIC_TIME_MIN, EM_ACOUSTIC_TIME_MAX);
	NVRAM0[EM_ACOUSTIC_ENERGY] -= NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
	LIMS16(EM_ACOUSTIC_ENERGY, EM_ACOUSTIC_ENERGY_MIN, EM_ACOUSTIC_ENERGY_MAX);
}

int16_t keyRuleAdd(int16_t ps, int16_t max){//����
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
int16_t keyRuleDec(int16_t ps, int16_t min){//����
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
void loadDefault(void){//�ָ�Ĭ��ֵ
	uint8_t i;
	RRES(MR_FOOSWITCH_HAND_SWITCH);
	RRES(MR_BEEP_TONE);			
	RRES(R_DISABLE_RFID);
	RRES(R_DISABLE_FIBER_PROBE);
	RRES(R_DISABLE_FAN_SPEED);
	NVRAM0[DM_BEEM_VOLUME] = CONFIG_BEEM_MAX_VOLUME / 2;
	NVRAM0[DM_AIM_BRG] = CONFIG_MAX_LASER_POWER_650;
	NVRAM0[DM_LCD_BRG] = CONFIG_LCD_MAX_DC;
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM;i ++){
		NVRAM0[DM_SCHEME_NUM] = i;
		defaultScheme();
		saveScheme();
	}
	NVRAM0[DM_SCHEME_NUM] = 0;
	NVRAM0[EM_LASER_SCHEME_NAME] = NVRAM0[DM_SCHEME_NUM];
	FDSAV();
	NVFSAVE();
}
void lockPreScheme(void){//�ָ�Ԥ�跽��
	uint8_t i;
	uint16_t oldNum;
	oldNum = NVRAM0[DM_SCHEME_NUM];
	for(i = 0;i <= 26;i ++){
		NVRAM0[DM_SCHEME_NUM] = i;
		defaultScheme();
		saveScheme();
	}
	NVRAM0[DM_SCHEME_NUM] = oldNum;
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
	sprintf((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]),"Customize %d", (NVRAM0[DM_SCHEME_NUM] - 25));		
	NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;//����ģʽ
	NVRAM0[EM_LASER_POWER_1470] = NVRAM0[DM_SCHEME_NUM] + 1;//ͨ��0����
	NVRAM0[EM_LASER_POWER_980] = 0;
	NVRAM0[EM_LASER_POWER_635] = 0;
	NVRAM0[EM_LASER_POSWIDTH]= 400;//������
	NVRAM0[EM_LASER_NEGWIDTH]= 300;//������
	switch(NVRAM0[DM_SCHEME_NUM]){
		case 0:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S0);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 80;//8.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 1:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S1);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 60;//6.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 2:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S2);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 30;//8.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 3:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S3);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 60;//6.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;			
			break;
		}
		case 4:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S4);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 70;//7.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 5:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S5);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 80;//8.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 6:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S6);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 120;//12.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 7:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S7);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 120;//12.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 8:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S8);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 70;//7.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 9:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S9);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 60;//6.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 500;//������ 500mS
			NVRAM0[EM_LASER_NEGWIDTH]= 500;//������ 500mS
			break;
		}
		case 10:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S10);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 70;//7.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 500;//������ 500mS
			NVRAM0[EM_LASER_NEGWIDTH]= 500;//������ 500mS
			break;
		}
		case 11:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S11);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 80;//8.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 500;//������ 500mS
			NVRAM0[EM_LASER_NEGWIDTH]= 500;//������ 500mS
			break;
		}
		case 12:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S12);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 80;//8.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 500;//������ 500mS
			NVRAM0[EM_LASER_NEGWIDTH]= 500;//������ 500mS
			break;
		}
		case 13:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S13);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 60;//6.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 15000;//������ 15S
			NVRAM0[EM_LASER_NEGWIDTH]= 1000;//������ 1S
			break;
		}
		case 14:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S14);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 100;//10.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 15000;//������ 15S
			NVRAM0[EM_LASER_NEGWIDTH]= 1000;//������ 1S
			break;
		}
		case 15:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S15);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 50;//5.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 15000;//������ 15S
			NVRAM0[EM_LASER_NEGWIDTH]= 1000;//������ 1S
			break;
		}
		case 16:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S16);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 50;//5.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 15000;//������ 15S
			NVRAM0[EM_LASER_NEGWIDTH]= 1000;//������ 1S
			break;
		}
		case 17:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S17);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 80;//8.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 15000;//������ 15S
			NVRAM0[EM_LASER_NEGWIDTH]= 1000;//������ 1S
			break;
		}
		case 18:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S18);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 70;//7.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 1000;//������ 1S
			NVRAM0[EM_LASER_NEGWIDTH]= 5000;//������ 5S
			break;			
		}
		case 19:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S19);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_1470] = 70;//7.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			NVRAM0[EM_LASER_POSWIDTH]= 1000;//������ 1S
			NVRAM0[EM_LASER_NEGWIDTH]= 5000;//������ 5S
			break;
		}
		case 20:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S20);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 30;//3.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 21:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S21);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 60;//6.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 22:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S22);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 80;//8.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 23:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S23);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 120;//12.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 24:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S24);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 100;//10.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 25:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S25);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 80;//8.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		case 26:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S26);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_CW;
			NVRAM0[EM_LASER_POWER_1470] = 80;//8.0W
			NVRAM0[EM_LASER_POWER_980] = 0;//0.0W
			NVRAM0[EM_LASER_POWER_635] = 0;
			break;
		}
		default:break;
	}
}

void loadScheme(void){//FD->EM
	uint8_t *psrc, *pdist;
	if(NVRAM0[DM_SCHEME_NUM] > 31){
		printf("App->loadScheme:NVRAM0[DM_SCHEME_NUM] > 31 !\n");
		NVRAM0[DM_SCHEME_NUM] = 31;
	}
	if(NVRAM0[DM_SCHEME_NUM] < 0){
		printf("App->loadScheme:NVRAM0[DM_SCHEME_NUM] < 0 !\n");
		NVRAM0[DM_SCHEME_NUM] = 0;
	}
	printf("%s,%d,%s:loadScheme:%d\n", __FILE__, __LINE__, __func__, NVRAM0[DM_SCHEME_NUM]);
	psrc = (uint8_t*)&FDRAM0[FD_SCHEME_START_0 + (NVRAM0[DM_SCHEME_NUM] * 64)];
	pdist = (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME];
	memcpy(pdist, psrc, ((FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1) * 2));
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			break;
		}
		case LASER_MODE_MP:{
			break;
		}
		default:{
			printf("App->loadScheme:load default scheme!\n");
			defaultScheme();
			break;
		}
	}
	printf("\n\n\n\n");
	printf("%s,%d,%s:load scheme!\n", __FILE__, __LINE__, __func__);
	printf("%s,%d,%s:scheme num:%d\n", __FILE__, __LINE__, __func__, NVRAM0[DM_SCHEME_NUM]);
	printf("%s,%d,%s:scheme name:%s\n", __FILE__, __LINE__, __func__, (char*)&NVRAM0[EM_LASER_SCHEME_NAME]);
	printf("%s,%d,%s:scheme mode:%d\n", __FILE__, __LINE__, __func__,  NVRAM0[EM_LASER_PULSE_MODE]);
	printf("%s,%d,%s:scheme power:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_1470]);
	printf("%s,%d,%s:scheme power:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_980]);
	printf("%s,%d,%s:scheme power:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_635]);
	printf("%s,%d,%s:scheme poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POSWIDTH]);
	printf("%s,%d,%s:scheme negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_NEGWIDTH]);
	printf("\n\n\n\n");
}
void saveScheme(void){//EM->FD
	uint8_t *psrc, *pdist;
	if(NVRAM0[DM_SCHEME_NUM] > (CONFIG_HMI_SCHEME_NUM - 1))
		NVRAM0[DM_SCHEME_NUM] = (CONFIG_HMI_SCHEME_NUM - 1);
	if(NVRAM0[DM_SCHEME_NUM] < 0)
		NVRAM0[DM_SCHEME_NUM] = 0;
	pdist = (uint8_t*)&FDRAM0[NVRAM0[DM_SCHEME_NUM] * (FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1)];
	psrc = (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME];
	memcpy(pdist, psrc, ((FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1) * 2));
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
	pstr = (char*)&FDRAM0[cn * 30 + FD_LASER_SCHEME_NAME];//��������
	strSize = strlen(pstr);
	if(strSize > 30){//���Ƴ��ȴ���
		return false;
	}	
	temp = FDRAM0[cn * 30 + FD_LASER_PULSE_MODE];//����ģʽ
	if((temp != LASER_MODE_CW) || (temp != LASER_MODE_MP)){
		return false;
	}
	temp = FDRAM0[cn * 30 + FD_LASER_POWER_1470];//ͨ��1470����
	if(temp < CONFIG_MIN_LASER_POWER_1470 || temp > CONFIG_MAX_LASER_POWER_1470){
		return false;
	}
	
	temp = FDRAM0[cn + 30 + FD_LASER_POWER_980];//ͨ��980����
	if(temp < CONFIG_MIN_LASER_POWER_980 || temp > CONFIG_MAX_LASER_POWER_980){
		return false;
	}
	
	temp = FDRAM0[cn + 30 + FD_LASER_POWER_980];//ͨ��635����
	if(temp < CONFIG_MIN_LASER_POWER_635 || temp > CONFIG_MAX_LASER_POWER_635){
		return false;
	}

	temp = FDRAM0[cn + 30 + FD_LASER_POWER_980];//ͨ��650����
	if(temp < CONFIG_MIN_LASER_POWER_650 || temp > CONFIG_MAX_LASER_POWER_650){
		return false;
	}
	
	temp = FDRAM0[cn * 30 + FD_LASER_SP_POSWIDTH];//������������
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM0[cn * 30 + FD_LASER_MP_POSWIDTH];//������������
	if(temp < CONFIG_MIN_LASER_POSWIDTH || temp > CONFIG_MAX_LASER_POSWIDTH){
		return false;
	}
	temp = FDRAM0[cn * 30 + FD_LASER_MP_NEGWIDTH];////�����帺����
	if(temp < CONFIG_MIN_LASER_NEGWIDTH || temp > CONFIG_MAX_LASER_NEGWIDTH){
		return false;
	}
	return true;
}
uint16_t fitLaserToCodeLine(uint8_t ch, int16_t power){//����->DAC CODE ʹ��Ĭ�����У����
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
uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg){//����->DAC CODE ʹ��У����
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
	if(LDB(R_CALIBRATION_MODE)){//��ģʽ
		//ͨ��У�������DACֵ
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
	else{//����У��ģʽ ->���ȱ����DACֵ
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





