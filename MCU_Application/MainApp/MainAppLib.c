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
	else if(ps >= 1000 && ps < 15000){
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
	else if(ps > 1000 && ps <= 15000){
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
void lockPreScheme(void){//恢复预设方案
	uint8_t i;	
	for(i = 0;i <= 19;i ++){
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
	NVRAM0[EM_LASER_POWER_CH0] = NVRAM0[DM_SCHEME_NUM] * 2 + 20;//通道0功率
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
	switch(NVRAM0[DM_SCHEME_NUM]){
		case 0:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S0);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 80;//8.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 80;//EVLA_SIGNAL能量间隔 80J
			break;
		}
		case 1:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S1);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 60;//8.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 60;//EVLA_SIGNAL能量间隔
			break;
		}
		case 2:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S2);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 30;//8.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 30;//EVLA_SIGNAL能量间隔
			break;
		}
		case 3:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S3);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 60;//6.0W
			NVRAM0[EM_LASER_SP_POSWIDTH]= 3000;//Ton 3S
			break;
		}
		case 4:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S4);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 70;//7.0W
			NVRAM0[EM_LASER_SP_POSWIDTH]= 3000;//Ton 3S
			break;
		}
		case 5:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S5);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 80;//8.0W
			NVRAM0[EM_LASER_SP_POSWIDTH]= 3000;//Ton 3S
			break;
		}
		case 6:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S6);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 100;//10.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 100;//EVLA_SIGNAL能量间隔 100J
			break;
		}
		case 7:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S7);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 100;//10.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 100;//EVLA_SIGNAL能量间隔 100J
			break;
		}
		case 8:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S8);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SIGNAL;
			NVRAM0[EM_LASER_POWER_CH0] = 70;//7.0W
			NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] = 100;//EVLA_SIGNAL能量间隔 100J
			break;
		}
		case 9:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S9);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_CH0] = 60;//6.0W
			NVRAM0[EM_LASER_MP_POSWIDTH]= 500;//多脉冲正脉宽 500mS
			NVRAM0[EM_LASER_MP_NEGWIDTH]= 500;//多脉冲负脉宽 500mS
			break;
		}
		case 10:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S10);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_CH0] = 70;//7.0W
			NVRAM0[EM_LASER_MP_POSWIDTH]= 500;//多脉冲正脉宽 500mS
			NVRAM0[EM_LASER_MP_NEGWIDTH]= 500;//多脉冲负脉宽 500mS
			break;
		}
		case 11:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S11);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_CH0] = 80;//8.0W
			NVRAM0[EM_LASER_MP_POSWIDTH]= 500;//多脉冲正脉宽 500mS
			NVRAM0[EM_LASER_MP_NEGWIDTH]= 500;//多脉冲负脉宽 500mS
			break;
		}
		case 12:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S12);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_CH0] = 80;//8.0W
			NVRAM0[EM_LASER_MP_POSWIDTH]= 500;//多脉冲正脉宽 500mS
			NVRAM0[EM_LASER_MP_NEGWIDTH]= 500;//多脉冲负脉宽 500mS
			break;
		}
		case 13:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S13);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 60;//6.0W
			NVRAM0[EM_LASER_SP_POSWIDTH]= 15000;//单脉冲正脉宽 15S
			break;
		}
		case 14:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S14);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 100;//10.0W
			NVRAM0[EM_LASER_SP_POSWIDTH]= 15000;//单脉冲正脉宽 15S
			break;
		}
		case 15:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S15);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 50;//5.0W
			NVRAM0[EM_LASER_SP_POSWIDTH]= 15000;//单脉冲正脉宽 15S
			break;
		}
		case 16:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S16);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 50;//5.0W
			NVRAM0[EM_LASER_SP_POSWIDTH]= 10000;//单脉冲正脉宽 10S
			break;
			}
		case 17:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S17);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_SP;
			NVRAM0[EM_LASER_POWER_CH0] = 80;//8.0W
			NVRAM0[EM_LASER_SP_POSWIDTH]= 15000;//单脉冲正脉宽 15S
			break;
		}
		case 18:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S18);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_CH0] = 70;//7.0W
			NVRAM0[EM_LASER_MP_POSWIDTH]= 1000;//多脉冲正脉宽 1S
			NVRAM0[EM_LASER_MP_NEGWIDTH]= 5000;//多脉冲负脉宽 5S
			break;
		}
		case 19:{
			strcpy((char*)&NVRAM0[EM_LASER_SCHEME_NAME], PRE_SCHEME_TABLE_S19);
			NVRAM0[EM_LASER_PULSE_MODE]	= LASER_MODE_MP;
			NVRAM0[EM_LASER_POWER_CH0] = 70;//7.0W
			NVRAM0[EM_LASER_MP_POSWIDTH]= 1000;//多脉冲正脉宽 1S
			NVRAM0[EM_LASER_MP_NEGWIDTH]= 5000;//多脉冲负脉宽 5S
			break;
		}
		default:break;
	}
#if CONFIG_DEBUG_APP == 1
	printf("%s,%d,%s:scheme num:%d\n", __FILE__, __LINE__, __func__, NVRAM0[DM_SCHEME_NUM]);
	printf("%s,%d,%s:scheme name:%s\n", __FILE__, __LINE__, __func__, (char*)&NVRAM0[EM_LASER_SCHEME_NAME]);
	printf("%s,%d,%s:scheme select:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_SELECT]);
	printf("%s,%d,%s:scheme mode:%d\n", __FILE__, __LINE__, __func__,  NVRAM0[EM_LASER_PULSE_MODE]);
	printf("%s,%d,%s:scheme power ch0:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH0]);
	printf("%s,%d,%s:scheme power ch1:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH1]);
	printf("%s,%d,%s:scheme sp poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_SP_POSWIDTH]);
	printf("%s,%d,%s:scheme mp poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_MP_POSWIDTH]);
	printf("%s,%d,%s:scheme mp negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_MP_NEGWIDTH]);
	printf("%s,%d,%s:scheme gp poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_GP_POSWIDTH]);
	printf("%s,%d,%s:scheme gp negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_GP_NEGWIDTH]);
	printf("%s,%d,%s:scheme gp times:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_GP_TIMES]);
	printf("%s,%d,%s:scheme gp group off:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_GP_GROUP_OFF]);
	printf("%s,%d,%s:scheme signal energy interval:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL]);
	printf("%s,%d,%s:scheme derma poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_DERMA_POSWIDTH]);
	printf("%s,%d,%s:scheme derma negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_DERMA_SPOT_SIZE]);
	printf("%s,%d,%s:scheme derma spot size:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_DERMA_SPOT_SIZE]);
	printf("\n\n\n\n");
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
#if CONFIG_DEBUG_APP == 1
	printf("\n\n\n\n");
	printf("%s,%d,%s:load scheme!\n", __FILE__, __LINE__, __func__);
	printf("%s,%d,%s:scheme num:%d\n", __FILE__, __LINE__, __func__, NVRAM0[DM_SCHEME_NUM]);
	printf("%s,%d,%s:scheme name:%s\n", __FILE__, __LINE__, __func__, (char*)&NVRAM0[EM_LASER_SCHEME_NAME]);
	printf("%s,%d,%s:scheme select:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_SELECT]);
	printf("%s,%d,%s:scheme mode:%d\n", __FILE__, __LINE__, __func__,  NVRAM0[EM_LASER_PULSE_MODE]);
	printf("%s,%d,%s:scheme power ch0:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH0]);
	printf("%s,%d,%s:scheme power ch1:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH1]);
	printf("%s,%d,%s:scheme sp poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_SP_POSWIDTH]);
	printf("%s,%d,%s:scheme mp poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_MP_POSWIDTH]);
	printf("%s,%d,%s:scheme mp negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_MP_NEGWIDTH]);
	printf("%s,%d,%s:scheme gp poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_GP_POSWIDTH]);
	printf("%s,%d,%s:scheme gp negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_GP_NEGWIDTH]);
	printf("%s,%d,%s:scheme gp times:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_GP_TIMES]);
	printf("%s,%d,%s:scheme gp group off:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_GP_GROUP_OFF]);
	printf("%s,%d,%s:scheme signal energy interval:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL]);
	printf("%s,%d,%s:scheme derma poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_DERMA_POSWIDTH]);
	printf("%s,%d,%s:scheme derma negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_DERMA_SPOT_SIZE]);
	printf("%s,%d,%s:scheme derma spot size:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_DERMA_SPOT_SIZE]);
	printf("\n\n\n\n");
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
uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg){//功率->DAC CODE 使用校正表
	fp64_t fpower, fpmax, fpmin, fout, fk, fb;
	uint16_t *pCal;
	uint16_t out;
	fpower = (fp32_t)power / 10.0F;
	switch(ch){
		case 0:{
			fpmax = (fp32_t)CONFIG_MAX_LASERPOWER_CH0 / 10.0F;
			fpmin = (fp32_t)CONFIG_MIN_LASERPOWER_CH0 / 10.0F;
			pCal = deviceConfig.calibrationPwr0;
			break;
		}
		case 1:{
			fpmax = (fp32_t)CONFIG_MAX_LASERPOWER_CH1 / 10.0F;
			fpmin = (fp32_t)CONFIG_MIN_LASERPOWER_CH1 / 10.0F;
			pCal = deviceConfig.calibrationPwr1;
			break;
		}
		case 2:{
			fpmax = (fp32_t)CONFIG_MAX_LASERPOWER_CH2 / 10.0F;
			fpmin = (fp32_t)CONFIG_MIN_LASERPOWER_CH2 / 10.0F;
			pCal = deviceConfig.calibrationPwr2;
			break;
		}
		case 3:{
			fpmax = (fp32_t)CONFIG_MAX_LASERPOWER_CH3 / 10.0F;
			fpmin = (fp32_t)CONFIG_MIN_LASERPOWER_CH3 / 10.0F;
			pCal = deviceConfig.calibrationPwr3;
			break;
		}
		default:{
			break;
		}
	}
	if(fpower > fpmax){
		fpower = fpmax;
	}
	if(fpower < fpmin){
		fpower = fpmin;
	}
#if CONFIG_DEBUG_APP == 1
	printf("%s,%d,%s:Calibration input power = %f\n", __FILE__, __LINE__, __func__, fpower);
	printf("%s,%d,%s:Calibration max power = %f\n", __FILE__, __LINE__, __func__, fpmax);
	printf("%s,%d,%s:Calibration min power = %f\n", __FILE__, __LINE__, __func__, fpmin);
#endif
	if(LDB(R_CALIBRATION_MODE)){//正模式
		//通过校正表计算DAC值
#if CONFIG_DEBUG_APP == 1
		printf("%s,%d,%s:Enable calibration mode\n", __FILE__, __LINE__, __func__);
#endif
		if((fpower >= fpmin) && (fpower < (fpower * 0.1F))){//[0,0.1)区间
			fk = ((*(pCal + 1) - *pCal) / (0.1F * 4095.0F));//计算K值
			fb = *(pCal + 0) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else if(fpower >= (fpmax * 0.1) && fpower < (fpmax * 0.2)){//[0.1,0.2)区间
			fk = ((*(pCal + 2) - *(pCal + 1)) / (0.1F * 4095.0F));
			fb = *(pCal + 1) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else if(fpower >= (fpmax * 0.2) && fpower < (fpmax * 0.3)){//[0.2,0.3)区间
			fk = ((*(pCal + 3) - *(pCal + 2)) / (0.1F * 4095.0F));
			fb = (*pCal + 2) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else if(fpower >= (fpmax * 0.3) && fpower < (fpmax * 0.4)){//[0.3,0.4)区间
			fk = ((*(pCal + 4) - *(pCal + 3)) / (0.1F * 4095.0F));
			fb = *(pCal + 3) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else if(fpower >= (fpmax * 0.4) && fpower < (fpmax * 0.5)){//[0.4,0.5)区间
			fk = ((*(pCal + 5) - *(pCal + 4)) / (0.1F * 4095.0F));
			fb = *(pCal + 4) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else if(fpower >= (fpmax * 0.5) && fpower < (fpmax * 0.6)){//[0.5,0.6)
			fk = ((*(pCal + 6) - *(pCal + 5)) / (0.1F * 4095.0F));
			fb = *(pCal + 5) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else if(fpower >= (fpmax * 0.6) && fpower < (fpmax * 0.7)){//[0.6,0.7)
			fk = ((*(pCal + 7) - *(pCal + 6)) / (0.1F * 4095.0F));
			fb = *(pCal + 6) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else if(fpower >= (fpmax * 0.7) && fpower < (fpmax * 0.8)){//[0.7,0.8)
			fk = ((*(pCal + 8) - *(pCal + 7)) / (0.1F * 4095.0F));
			fb = *(pCal + 7) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else if(fpower >= (fpmax * 0.8) && fpower < (fpmax * 0.9)){//[0.8,0.9)
			fk = ((*(pCal + 9) - *(pCal + 8)) / (0.1F * 4095.0F));
			fb = *(pCal + 8) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else if(fpower >= (fpmax * 0.9) && fpower < fpmax){//1.0
			fk = ((*(pCal + 10) - *(pCal + 9)) / (0.1F * 4095.0F));
			fb = *(pCal + 9) - (fk * 0.1);//B值
			fout = fk * fpower + fb;//计算输出值
		}
		else{
			fout = 4095.0F;
		}
#if CONFIG_DEBUG_APP == 1
	printf("%s,%d,%s:Calibration fK=%f, fB=%f\n", __FILE__, __LINE__, __func__, fk, fb);
	printf("%s,%d,%s:Calibration fOut=%f\n", __FILE__, __LINE__, __func__, fout);
#endif		
	}
	else{//功率校正模式 ->按等比输出DAC值
#if CONFIG_DEBUG_APP == 1
		printf("%s,%d,%s:Disable calibration mode\n", __FILE__, __LINE__, __func__);
#endif
		fout = fpower / fpmax  * 4095 ;			
	}
	if(fout > 4095.0F){
		fout = 4095;
	}
	if(fout < 0.0F){
		fout = 0;
	}
	out = (uint16_t)fout;
#if CONFIG_DEBUG_APP == 1	
	printf("%s,%d,%s:Calibration fOut=%f\n", __FILE__, __LINE__, __func__, fout);
#endif	
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





