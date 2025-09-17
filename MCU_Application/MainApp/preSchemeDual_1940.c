//预设方案内容
#include "preScheme.h"
/*****************************************************************************/
#if defined(APP_CONFIG_WAVE_1940_650)
myScheme_t sPhlebology[32];//0
myScheme_t sProctology[32];//1
myScheme_t sGynecology[32];//2
myScheme_t sENT[32];//3
myScheme_t sNeurosurgery[32];//4
myScheme_t sDermatology[32];//5
myScheme_t sLiposuction[32];//6
myScheme_t sDentistry[32];//7
myScheme_t sTherapy[32];//8
/*****************************************************************************/
void goNextScheme(void){//切换下一个方案
	if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_CUSTIOM_SIZE - 1)){
		ADDS1(DM_SCHEME_INDEX);
	}
}

void goLastScheme(void){//切换上一个方案
	if(NVRAM0[DM_SCHEME_INDEX] > 0){
			DECS1(DM_SCHEME_INDEX);
	}
}

void schemeInit(uint8_t reDef){//治疗方案初始化
	int16_t i;
	for (i = 0;i < 32; i ++){
		if(reDef == 1){//自定义方案恢复默认值
			sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "Custom %d", (i+1)); 
			FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
			FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
			FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 10;
			FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
			FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
			FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
			FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;	
		}
		else{
			if(	(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_CH0) 			&&
					(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_CH1)  			&&
					(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_RED)  			&&
					(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_CH0_RED)		&&
					(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_CH1_RED)){//自定义方案不正确恢复默认值
				sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "Custom %d", (i+1)); 
				FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
				FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
				FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 10;
				FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
				FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
				FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
				FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;		
			}
		}
	}
	//恢复默认方案
	i = 0;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh cw i");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 40;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 1;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Pulse i");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 40;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 2;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Cw ii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 50;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 3;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Pulse ii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 50;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 4;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Cw iii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 60;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 5;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Pulse iii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 60;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 6;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA calf cw i");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 20;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 7;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA calf Pulse i");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 20;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 8;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA calf CW ii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 30;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 9;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA calf Pulse ii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 30;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;
}

void loadSelectScheme(int16_t classify, int16_t index){//将方案写入EM		
	if(index > (CONFIG_CUSTIOM_SIZE - 1)){
		index = (CONFIG_CUSTIOM_SIZE - 1);
	}
	memcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(&FDRAM0[index * 64 + FD_LASER_SCHEME_NAME]) , 112);
	NVRAM0[EM_LASER_CHANNEL_SELECT] = FDRAM0[index * 64 + FD_LASER_CHANNEL_SELECT];
	NVRAM0[EM_LASER_PULSE_MODE] = FDRAM0[index * 64 + FD_LASER_PULSE_MODE];
	NVRAM0[EM_LASER_POWER_CH0] = FDRAM0[index * 64 + FD_LASER_POWER_CH0];
	NVRAM0[EM_LASER_POWER_CH1] = FDRAM0[index * 64 + FD_LASER_POWER_CH1];
	NVRAM0[EM_LASER_POWER_635] = FDRAM0[index * 64 + FD_LASER_POWER_RED];
	NVRAM0[EM_LASER_POSWIDTH] = FDRAM0[index * 64 + FD_LASER_POSWIDTH];
	NVRAM0[EM_LASER_NEGWIDTH] = FDRAM0[index * 64 + FD_LASER_NEGWIDTH];

	printf("%s,%d,%s:scheme classify:%d\n", __FILE__, __LINE__, __func__, classify);
	printf("%s,%d,%s:scheme index:%d\n", __FILE__, __LINE__, __func__, index);
	printf("%s,%d,%s:scheme name:%s\n", __FILE__, __LINE__, __func__, (char*)(&NVRAM0[EM_LASER_SCHEME_NAME]));
	printf("%s,%d,%s:scheme select:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_CHANNEL_SELECT]);
	printf("%s,%d,%s:scheme mode:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_PULSE_MODE]);
	printf("%s,%d,%s:scheme power 1470:%d\n", __FILE__, __LINE__, __func__,NVRAM0[EM_LASER_POWER_CH0]);
	printf("%s,%d,%s:scheme power 980:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH1]);
	printf("%s,%d,%s:scheme power 635:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_635]);
	printf("%s,%d,%s:scheme poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POSWIDTH]);
	printf("%s,%d,%s:scheme negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_NEGWIDTH]);
}

#endif

