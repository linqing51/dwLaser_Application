/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
//预设方案内容
#include "preScheme.h"
/*****************************************************************************/
#if defined(APP_CONFIG_WAVE_450_980)
//本配置(450_980)治疗方案走 FDRAM 路径(见 restoreScheme 中 FDRAM0 初始化),
//dcHmiApp.c 在本配置下不引用以下 sXxx 符号。这里仅为与 preScheme.h 的 const extern
//声明保持类型一致而保留, 全零固化在 Flash, 不占 RAM。
const myScheme_t sPhlebology[32] = {0};//0
const myScheme_t sProctology[32] = {0};//1
const myScheme_t sGynecology[32] = {0};//2
const myScheme_t sENT[32] = {0};//3
const myScheme_t sNeurosurgery[32] = {0};//4
const myScheme_t sDermatology[32] = {0};//5
const myScheme_t sLiposuction[32] = {0};//6
const myScheme_t sDentistry[32] = {0};//7
const myScheme_t sTherapy[32] = {0};//8
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

void restoreScheme(uint8_t reDef){//治疗方案初始化
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
			if(	(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_CH0) &&\
					(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_CH1) &&\
					(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_CH2)){//自定义方案不正确恢复默认值
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
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 40;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 1;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Pulse i");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 40;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 2;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Cw ii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 50;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 3;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Pulse ii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 50;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 4;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Cw iii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 60;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 5;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA Thigh Pulse iii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 60;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 6;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA calf cw i");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 20;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 7;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA calf Pulse i");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 20;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 8;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA calf CW ii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 30;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;

	i = 9;
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "EVLA calf Pulse ii");
	FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0 | LASER_CHANNEL_CH1;
	FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 30;
	FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
	FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
	FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;
	FDSAV();//FDRAM恢复后强制写回EPROM
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
	printf("%s,%d,%s:scheme power 450:%d\n", __FILE__, __LINE__, __func__,NVRAM0[EM_LASER_POWER_CH0]);
	printf("%s,%d,%s:scheme power 980:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH1]);
	printf("%s,%d,%s:scheme power 635:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_635]);
	printf("%s,%d,%s:scheme poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POSWIDTH]);
	printf("%s,%d,%s:scheme negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_NEGWIDTH]);
}

#endif

