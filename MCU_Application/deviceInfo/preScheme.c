//预设方案内容
#include "preScheme.h"
/*****************************************************************************/
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
	switch(NVRAM0[DM_SCHEME_CLASSIFY]){
		case SCHEME_PHLEBOLOGY:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_PHLEBOLOGY_SIZE - 1)){
				ADDS1(DM_SCHEME_INDEX);
			}
			break;
		}
		case SCHEME_PROCTOLOGY:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_PROCTOLOGY_SIZE - 1)){
				ADDS1(DM_SCHEME_INDEX);
			}
			break;
		}
		case SCHEME_GYNECOLOGY:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_GYNECOLOGY_SIZE - 1)){
				ADDS1(DM_SCHEME_INDEX);
			}
			break;
		}
		case SCHEME_ENT:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_ENT_SIZE - 1)){
				ADDS1(DM_SCHEME_INDEX);
			}
			break;
		}
		case SCHEME_NEUROSURGERY:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_NEUROSURGERY_SIZE - 1)){
				ADDS1(DM_SCHEME_INDEX);
			}				
			break;
		}
		case SCHEME_DERMATOLOGY:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_DERMATOLOGY_SIZE - 1)){
				ADDS1(DM_SCHEME_INDEX);
			}
			break;
		}
		case SCHEME_LIPOSUCTION:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_LIPOSUCTION_SIZE - 1)){
				ADDS1(DM_SCHEME_INDEX);
			}
			break;
		}
		case SCHEME_DENTISRTY:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_DENTISRTY_SIZE - 1)){
					ADDS1(DM_SCHEME_INDEX);
			}
			break;
		}
		case SCHMEM_THERAPY:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_THERAPY_SIZE - 1)){
				ADDS1(DM_SCHEME_INDEX);
			}
			break;
		}	
		case SCHEME_CUSTIOM:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_CUSTIOM_SIZE - 1)){
				ADDS1(DM_SCHEME_INDEX);
			}
			break;
		}
		default:break;
	}
}

void goLastScheme(void){//切换上一个方案
	if(NVRAM0[DM_SCHEME_INDEX] > 0){
			DECS1(DM_SCHEME_INDEX);
	}
}
void loadSelectScheme(int16_t classify, int16_t index){//将方案写入EM	
	switch(classify){
		case SCHEME_PHLEBOLOGY:{
			if(NVRAM0[DM_SCHEME_INDEX] > (CONFIG_PHLEBOLOGY_SIZE-1)){
				NVRAM0[DM_SCHEME_INDEX] = (CONFIG_PHLEBOLOGY_SIZE-1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sPhlebology[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sPhlebology[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sPhlebology[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_1470] = sPhlebology[index].power_1470;
			NVRAM0[EM_LASER_POWER_980] = sPhlebology[index].power_980;
			NVRAM0[EM_LASER_POWER_635] = sPhlebology[index].power_635;
			NVRAM0[EM_LASER_POSWIDTH] = sPhlebology[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sPhlebology[index].negwidth;
			break;
		}
		case SCHEME_PROCTOLOGY:{
			if(index > (CONFIG_PROCTOLOGY_SIZE - 1)){
				 index = (CONFIG_PROCTOLOGY_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sProctology[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sProctology[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sProctology[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_1470] = sProctology[index].power_1470;
			NVRAM0[EM_LASER_POWER_980] = sProctology[index].power_980;
			NVRAM0[EM_LASER_POWER_635] = sProctology[index].power_635;
			NVRAM0[EM_LASER_POSWIDTH] = sProctology[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sProctology[index].negwidth;
			break;			
		}
		case SCHEME_GYNECOLOGY:{
			if(index > (CONFIG_GYNECOLOGY_SIZE - 1)){
				index = (CONFIG_GYNECOLOGY_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sGynecology[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sGynecology[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sGynecology[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_1470] = sGynecology[index].power_1470;
			NVRAM0[EM_LASER_POWER_980] = sGynecology[index].power_980;
			NVRAM0[EM_LASER_POWER_635] = sGynecology[index].power_635;
			NVRAM0[EM_LASER_POSWIDTH] = sGynecology[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sGynecology[index].negwidth;
			break;
		}			
		case SCHEME_ENT:{
			if(index > (CONFIG_ENT_SIZE - 1)){
				index = (CONFIG_ENT_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sENT[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sENT[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sENT[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_1470] = sENT[index].power_1470;
			NVRAM0[EM_LASER_POWER_980] = sENT[index].power_980;
			NVRAM0[EM_LASER_POWER_635] = sENT[index].power_635;
			NVRAM0[EM_LASER_POSWIDTH] = sENT[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sENT[index].negwidth;
			break;
		}			
		case SCHEME_NEUROSURGERY:{
			if(index > (CONFIG_NEUROSURGERY_SIZE - 1)){
				index = (CONFIG_NEUROSURGERY_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sNeurosurgery[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sNeurosurgery[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sNeurosurgery[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_1470] = sNeurosurgery[index].power_1470;
			NVRAM0[EM_LASER_POWER_980] = sNeurosurgery[index].power_980;
			NVRAM0[EM_LASER_POWER_635] = sNeurosurgery[index].power_635;
			NVRAM0[EM_LASER_POSWIDTH] = sNeurosurgery[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sNeurosurgery[index].negwidth;
			break;
		}
		case SCHEME_DERMATOLOGY:{
			if(index > (CONFIG_DERMATOLOGY_SIZE - 1)){
				index = (CONFIG_DERMATOLOGY_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sDermatology[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sDermatology[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sDermatology[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_1470] = sDermatology[index].power_1470;
			NVRAM0[EM_LASER_POWER_980] = sDermatology[index].power_980;
			NVRAM0[EM_LASER_POWER_635] = sDermatology[index].power_635;
			NVRAM0[EM_LASER_POSWIDTH] = sDermatology[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sDermatology[index].negwidth;			
			break;
		}
		case SCHEME_LIPOSUCTION:{
			if(index > (CONFIG_LIPOSUCTION_SIZE - 1)){
				index = (CONFIG_LIPOSUCTION_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sLiposuction[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sLiposuction[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sLiposuction[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_1470] = sLiposuction[index].power_1470;
			NVRAM0[EM_LASER_POWER_980] = sLiposuction[index].power_980;
			NVRAM0[EM_LASER_POWER_635] = sLiposuction[index].power_635;
			NVRAM0[EM_LASER_POSWIDTH] = sLiposuction[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sLiposuction[index].negwidth;
			break;
		}
		case SCHEME_DENTISRTY:{
			if(index > (CONFIG_DENTISRTY_SIZE - 1)){
				index = (CONFIG_DENTISRTY_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sDentistry[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sDentistry[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sDentistry[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_1470] = sDentistry[index].power_1470;
			NVRAM0[EM_LASER_POWER_980] = sDentistry[index].power_980;
			NVRAM0[EM_LASER_POWER_635] = sDentistry[index].power_635;
			NVRAM0[EM_LASER_POSWIDTH] = sDentistry[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sDentistry[index].negwidth;
			break;
		}
		case SCHMEM_THERAPY:{
			if(index > (CONFIG_THERAPY_SIZE - 1)){
				index = (CONFIG_THERAPY_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sTherapy[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sTherapy[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sTherapy[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_1470] = sTherapy[index].power_1470;
			NVRAM0[EM_LASER_POWER_980] = sTherapy[index].power_980;
			NVRAM0[EM_LASER_POWER_635] = sTherapy[index].power_635;
			NVRAM0[EM_LASER_POSWIDTH] = sTherapy[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sTherapy[index].negwidth;			
			break;
		}
		case SCHEME_CUSTIOM:{
			if(index > (CONFIG_CUSTIOM_SIZE - 1)){
				index = (CONFIG_CUSTIOM_SIZE - 1);
			}
			memcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(&FDRAM0[index * 64 + FD_LASER_SCHEME_NAME]) , 112);
			NVRAM0[EM_LASER_CHANNEL_SELECT] = FDRAM0[index * 64 + FD_LASER_CHANNEL_SELECT];
			NVRAM0[EM_LASER_PULSE_MODE] = FDRAM0[index * 64 + FD_LASER_PULSE_MODE];
			NVRAM0[EM_LASER_POWER_1940] = FDRAM0[index * 64 + FD_LASER_POWER_1940];
			NVRAM0[EM_LASER_POWER_1470] = FDRAM0[index * 64 + FD_LASER_POWER_1470];
			NVRAM0[EM_LASER_POWER_980] = FDRAM0[index * 64 + FD_LASER_POWER_980];
			NVRAM0[EM_LASER_POWER_635] = FDRAM0[index * 64 + FD_LASER_POWER_635];
			NVRAM0[EM_LASER_POSWIDTH] = FDRAM0[index * 64 + FD_LASER_POSWIDTH];
			NVRAM0[EM_LASER_NEGWIDTH] = FDRAM0[index * 64 + FD_LASER_NEGWIDTH];				
			break;
		}
		default:break;		
	}
	printf("%s,%d,%s:scheme classify:%d\n", __FILE__, __LINE__, __func__, classify);
	printf("%s,%d,%s:scheme index:%d\n", __FILE__, __LINE__, __func__, index);
	printf("%s,%d,%s:scheme name:%s\n", __FILE__, __LINE__, __func__, (char*)(&NVRAM0[EM_LASER_SCHEME_NAME]));
	printf("%s,%d,%s:scheme select:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_CHANNEL_SELECT]);
	printf("%s,%d,%s:scheme mode:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_PULSE_MODE]);
	printf("%s,%d,%s:scheme power 1940:%d\n", __FILE__, __LINE__, __func__,NVRAM0[EM_LASER_POWER_1940]);
	printf("%s,%d,%s:scheme power 1470:%d\n", __FILE__, __LINE__, __func__,NVRAM0[EM_LASER_POWER_1470]);
	printf("%s,%d,%s:scheme power 980:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_980]);
	printf("%s,%d,%s:scheme power 635:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_635]);
	printf("%s,%d,%s:scheme poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POSWIDTH]);
	printf("%s,%d,%s:scheme negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_NEGWIDTH]);
}

void schemeInit(uint8_t reDef){//治疗方案初始化
	int16_t i;
#if defined(MODEL_PVGLS_7W_1940)
	for (i = 10;i < 32; i ++){
		if(reDef == 1){//自定义方案恢复默认值
			sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "custom %d", (i - 9)); 
			FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_1940;
			FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
			FDRAM0[FD_LASER_POWER_1940 + (i * 64)] = 10;
			FDRAM0[FD_LASER_POWER_1470 + (i * 64)] = 0;
			FDRAM0[FD_LASER_POWER_980 + (i * 64)] = 0;
			FDRAM0[FD_LASER_POWER_635 + (i * 64)] = 0;
			FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
			FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;			
		}
	}
#endif
	
#if defined(MODEL_PVGLS_15W_1470)
		//S0
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (0 * 64)]), "EVLA Thigh"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (0 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (0 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1940 + (0 * 64)] = 0;
		FDRAM0[FD_LASER_POWER_1470 + (0 * 64)] = 80;
		FDRAM0[FD_LASER_POWER_980 + (0 * 64)] = 0;
		FDRAM0[FD_LASER_POWER_635 + (0 * 64)] = 0;
		FDRAM0[FD_LASER_POSWIDTH + (0 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (0 * 64)] = 1000;	
		//S1
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (1 * 64)]), "EVLA calf"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (1 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (1 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1940 + (1 * 64)] = 0;
		FDRAM0[FD_LASER_POWER_1470 + (1 * 64)] = 60;
		FDRAM0[FD_LASER_POWER_980 + (1 * 64)] = 0;
		FDRAM0[FD_LASER_POWER_635 + (1 * 64)] = 0;
		FDRAM0[FD_LASER_POSWIDTH + (1 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (1 * 64)] = 1000;	
		//S2
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (2 * 64)]), "EVLA Small Vessel"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (2 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (2 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (2 * 64)] = 30;
		FDRAM0[FD_LASER_POWER_980 + (2 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (2 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (2 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (2 * 64)] = 1000;
		//S3
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (3 * 64)]), "Hemorrhoids Grade 2, 250J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (3 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (3 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (3 * 64)] = 60;
		FDRAM0[FD_LASER_POWER_980 + (3 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (3 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (3 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (3 * 64)] = 1000;
		//S4
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (4 * 64)]), "Hemorrhoids Grade 3, 250J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (4 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (4 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (4 * 64)] = 70;
		FDRAM0[FD_LASER_POWER_980 + (4 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (4 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (4 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (4 * 64)] = 1000;
		//S5
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (5 * 64)]), "Hemorrhoids Grade 4, 250J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (5 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (5 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (5 * 64)] = 80;
		FDRAM0[FD_LASER_POWER_980 + (5 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (5 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (5 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (5 * 64)] = 1000;
		//S6
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (6 * 64)]), "Fistula"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (6 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (6 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (6 * 64)] = 120;
		FDRAM0[FD_LASER_POWER_980 + (6 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (6 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (6 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (6 * 64)] = 1000;
		//S7
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (7 * 64)]), "Pilonidal Sinus"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (7 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (7 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (7 * 64)] = 120;
		FDRAM0[FD_LASER_POWER_980 + (7 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (7 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (7 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (7 * 64)] = 1000;
		//S8
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (8 * 64)]), "Fissure Ablation"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (8 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (8 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (8 * 64)] = 70;
		FDRAM0[FD_LASER_POWER_980 + (8 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (8 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (8 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (8 * 64)] = 1000;
		//S9
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (9* 64)]), "Laser Vaginal Tightening 1st 600J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (9 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (9 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (9 * 64)] = 60;
		FDRAM0[FD_LASER_POWER_980 + (9 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (9 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (9 * 64)] = 500;
		FDRAM0[FD_LASER_NEGWIDTH + (9 * 64)] = 500;
		//S10
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (10 * 64)]), "Laser Vaginal Tightening 2nd 600J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (10 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (10 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (10 * 64)] = 70;
		FDRAM0[FD_LASER_POWER_980 + (10 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (10 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (10 * 64)] = 500;
		FDRAM0[FD_LASER_NEGWIDTH + (10 * 64)] = 500;
		//S11
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (11 * 64)]), "Laser Vaginal Tightening 3rd 600J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (11 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (11 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (11 * 64)] = 80;
		FDRAM0[FD_LASER_POWER_980 + (11 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (11 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (11 * 64)] = 500;
		FDRAM0[FD_LASER_NEGWIDTH + (11 * 64)] = 500;
		//S12
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (12 * 64)]), "Laser Vaginal Tightening 4th 600J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (12 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (12 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (12 * 64)] = 80;
		FDRAM0[FD_LASER_POWER_980 + (12 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (12 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (12 * 64)] = 500;
		FDRAM0[FD_LASER_NEGWIDTH + (12 * 64)] = 500;
		//S13
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (13 * 64)]), "Laser Vaginal Rejuvenation 360J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (13 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (13 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (13 * 64)] = 60;
		FDRAM0[FD_LASER_POWER_980 + (13 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (13 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (13 * 64)] = 15000;
		FDRAM0[FD_LASER_NEGWIDTH + (13 * 64)] = 1000;
		//S14
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (14 * 64)]), "Laser Vaginal Rejuvenation+ 600J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (14 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (14 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (14 * 64)] = 100;
		FDRAM0[FD_LASER_POWER_980 + (14 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (14 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (14 * 64)] = 15000;
		FDRAM0[FD_LASER_NEGWIDTH + (14 * 64)] = 1000;	
		//S15
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (15 * 64)]), "Stress Incontinence, 75J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (15 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (15 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (15 * 64)] = 50;
		FDRAM0[FD_LASER_POWER_980 + (15 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (15 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (15 * 64)] = 15000;
		FDRAM0[FD_LASER_NEGWIDTH + (15 * 64)] = 1000;
		//S16
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (16 * 64)]), "Infection control, 50J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (16 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (16 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (16 * 64)] = 50;
		FDRAM0[FD_LASER_POWER_980 + (16 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (16 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (16 * 64)] = 10000;
		FDRAM0[FD_LASER_NEGWIDTH + (16 * 64)] = 1000;
		//S17
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (17 * 64)]), "Treatment after Menopause, 480J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (17 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (17 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (17 * 64)] = 80;
		FDRAM0[FD_LASER_POWER_980 + (17 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (17 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (17 * 64)] = 15000;
		FDRAM0[FD_LASER_NEGWIDTH + (17 * 64)] = 1000;
		//S18
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (18 * 64)]), "PLDD L2-L3, L3-L4, L5-S1 800-1500J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (18 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (18 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (18 * 64)] = 70;
		FDRAM0[FD_LASER_POWER_980 + (18 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (18 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (18 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (18 * 64)] = 5000;
		//S19
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (19 * 64)]), "PLDD L4-L5 Total 800-1800J"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (19 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (19 * 64)] = LASER_MODE_MP;
		FDRAM0[FD_LASER_POWER_1470 + (19 * 64)] = 70;
		FDRAM0[FD_LASER_POWER_980 + (19 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (19 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (19 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (19 * 64)] = 5000;
		//S20
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (20 * 64)]), "Liposuction Under Eye"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (20 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (20 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (20 * 64)] = 30;
		FDRAM0[FD_LASER_POWER_980 + (20 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (20 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (20 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (20 * 64)] = 1000;
		//S21
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (21 * 64)]), "Liposuction Chin"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (21 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (21 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (21 * 64)] = 60;
		FDRAM0[FD_LASER_POWER_980 + (21 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (21 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (21 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (21 * 64)] = 1000;
		//S22
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (22 * 64)]), "Liposuction Arm"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (22 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (22 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (22 * 64)] = 80;
		FDRAM0[FD_LASER_POWER_980 + (22 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (22 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (22 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (22 * 64)] = 1000;
		//S23
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (23 * 64)]), "Liposuction Abdomen"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (23 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (23 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (23 * 64)] = 120;
		FDRAM0[FD_LASER_POWER_980 + (23 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (23 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (23 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (23 * 64)] = 1000;
		//S24
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (24 * 64)]), "Liposuction Buttock"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (24 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (24 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (24 * 64)] = 100;
		FDRAM0[FD_LASER_POWER_980 + (24 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (24 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (24 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (24 * 64)] = 1000;
		//S25
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (25 * 64)]), "Liposuction Thigh"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (25 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (25 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (25 * 64)] = 8;
		FDRAM0[FD_LASER_POWER_980 + (25 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (25 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (25 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (25 * 64)] = 1000;	
		//S26
		sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (26 * 64)]), "Gynecomastia"); 
		FDRAM0[FD_LASER_CHANNEL_SELECT + (26 * 64)] = LASER_CHANNEL_1470;
		FDRAM0[FD_LASER_PULSE_MODE + (26 * 64)] = LASER_MODE_CW;
		FDRAM0[FD_LASER_POWER_1470 + (26 * 64)] = 8;
		FDRAM0[FD_LASER_POWER_980 + (26 * 64)] = 1;
		FDRAM0[FD_LASER_POWER_635 + (26 * 64)] = 1;
		FDRAM0[FD_LASER_POSWIDTH + (26 * 64)] = 1000;
		FDRAM0[FD_LASER_NEGWIDTH + (26 * 64)] = 1000;			
		NVRAM0[DM_SCHEME_CLASSIFY] = SCHEME_CUSTIOM;
#endif
/***************************************************************************/
#if defined(MODEL_PVGLS_TRI) || defined(MODEL_PVGLS_TRI_COMBINE)
	//Phlebology
	//1470nm, CW 8w 80J/cm
	sPhlebology[0].name = "EVLA Thigh";
	sPhlebology[0].channel = LASER_CHANNEL_1470;
	sPhlebology[0].pulse_mode = LASER_MODE_CW; 
	sPhlebology[0].power_1470 = 80;
	sPhlebology[0].power_980 = 1;
	sPhlebology[0].power_635 = 1;
	sPhlebology[0].poswidth = 1000;
	sPhlebology[0].negwidth = 1000;
	
	//1470nm, CW 6w 60J/cm
	sPhlebology[1].name = "EVLA calf";
	sPhlebology[1].channel = LASER_CHANNEL_1470;
	sPhlebology[1].pulse_mode = LASER_MODE_CW; 
	sPhlebology[1].power_1470 = 60;
	sPhlebology[1].power_980 = 1;
	sPhlebology[1].power_635 = 1;
	sPhlebology[1].poswidth = 1000;
	sPhlebology[1].negwidth = 1000;
	
	//1470nm, CW 3w 30J/cm
	sPhlebology[2].name = "EVLA Small Vessel";
	sPhlebology[2].channel = LASER_CHANNEL_1470;
	sPhlebology[2].pulse_mode = LASER_MODE_CW; 
	sPhlebology[2].power_1470 = 30;
	sPhlebology[2].power_980 = 1;
	sPhlebology[2].power_635 = 1;
	sPhlebology[2].poswidth = 1000;
	sPhlebology[2].negwidth = 1000;
/***************************************************************************/
	//Proctology
	//1470nm, CW 6w, 250 Joules per hemorrhoid
	sProctology[0].name = "Hemorrhoids Grade 2, 250J";
	sProctology[0].channel = LASER_CHANNEL_1470;
	sProctology[0].pulse_mode = LASER_MODE_CW; 
	sProctology[0].power_1470 = 70;
	sProctology[0].power_980 = 1;
	sProctology[0].power_635 = 1;
	sProctology[0].poswidth = 1000;
	sProctology[0].negwidth = 1000;
	
	//1470nm, CW 7w, 350 Joules per hemorrhoid
	sProctology[1].name ="Hemorrhoids Grade 3, 350J";
	sProctology[1].channel = LASER_CHANNEL_1470;
	sProctology[1].pulse_mode = LASER_MODE_CW; 
	sProctology[1].power_1470 = 80;
	sProctology[1].power_980 = 1;
	sProctology[1].power_635 = 1;
	sProctology[1].poswidth = 1000;
	sProctology[1].negwidth = 1000; 	
	
	//1470nm, CW 8w, 350 Joules per hemorrhoid
	sProctology[2].name = "Hemorrhoids Grade 4, 350J";
	sProctology[2].channel = LASER_CHANNEL_1470;
	sProctology[2].pulse_mode = LASER_MODE_CW; 
	sProctology[2].power_1470 = 80;
	sProctology[2].power_980 = 1;
	sProctology[2].power_635 = 1;
	sProctology[2].poswidth = 1000;
	sProctology[2].negwidth = 1000; 
	
	//1470nm, CW 10w 100J/cm
	sProctology[3].name = "Fistula";
	sProctology[3].channel = LASER_CHANNEL_1470;
	sProctology[3].pulse_mode = LASER_MODE_CW; 
	sProctology[3].power_1470 = 120;
	sProctology[3].power_980 = 1;
	sProctology[3].power_635 = 1;
	sProctology[3].poswidth = 1000;
	sProctology[3].negwidth = 1000; 

	//1470nm, CW 10w 100J/cm
	sProctology[4].name = "Pilonidal Sinus";
	sProctology[4].channel = LASER_CHANNEL_1470;
	sProctology[4].pulse_mode = LASER_MODE_CW; 
	sProctology[4].power_1470 = 120;
	sProctology[4].power_980 = 1;
	sProctology[4].power_635 = 1;
	sProctology[4].poswidth = 1000;
	sProctology[4].negwidth = 1000; 
	
	//1470nm, CW 7w 100J/cm
	sProctology[5].name = "Fissure Ablation";
	sProctology[5].channel = LASER_CHANNEL_1470;
	sProctology[5].pulse_mode = LASER_MODE_CW; 
	sProctology[5].power_1470 = 70;
	sProctology[5].power_980 = 1;
	sProctology[5].power_635 = 1;
	sProctology[5].poswidth = 1000;
	sProctology[5].negwidth = 1000; 
/*****************************************************************************/
	//1470nm, Pulse 6w 500ms Ton, 500ms Toff
	sGynecology[0].name = "Laser Vaginal Tightening 1st 600J";
	sGynecology[0].channel = LASER_CHANNEL_1470;
	sGynecology[0].pulse_mode = LASER_MODE_MP; 
	sGynecology[0].power_1470 = 60;
	sGynecology[0].power_980 = 1;
	sGynecology[0].power_635 = 1;
	sGynecology[0].poswidth = 500;
	sGynecology[0].negwidth = 500; 	
	
	//1470nm, Pulse 7w 500ms Ton, 500ms Toff
	sGynecology[1].name = "Laser Vaginal Tightening 2nd 600J";
	sGynecology[1].channel = LASER_CHANNEL_1470;
	sGynecology[1].pulse_mode = LASER_MODE_MP; 
	sGynecology[1].power_1470 = 70;
	sGynecology[1].power_980 = 1;
	sGynecology[1].power_635 = 1;
	sGynecology[1].poswidth = 500;
	sGynecology[1].negwidth = 500; 
	
	//1470nm, Pulse 8w 500ms Ton, 500ms Toff
	sGynecology[2].name = "Laser Vaginal Tightening 3rd 600J";
	sGynecology[2].channel = LASER_CHANNEL_1470;
	sGynecology[2].pulse_mode = LASER_MODE_MP; 
	sGynecology[2].power_1470 = 80;
	sGynecology[2].power_980 = 1;
	sGynecology[2].power_635 = 1;
	sGynecology[2].poswidth = 500;
	sGynecology[2].negwidth = 500; 
	
	//1470nm, Pulse 8w 500ms Ton, 500ms Toff
	sGynecology[3].name = "Laser Vaginal Tightening 4th 600J";
	sGynecology[3].channel = LASER_CHANNEL_1470;
	sGynecology[3].pulse_mode = LASER_MODE_MP; 
	sGynecology[3].power_1470 = 80;
	sGynecology[3].power_980 = 1;
	sGynecology[3].power_635 = 1;
	sGynecology[3].poswidth = 500;
	sGynecology[3].negwidth = 500; 
	
	//1470nm, CW 6w 15s Ton
	sGynecology[4].name ="Laser Vaginal Rejuvenation 360J";
	sGynecology[4].channel = LASER_CHANNEL_1470;
	sGynecology[4].pulse_mode = LASER_MODE_CW; 
	sGynecology[4].power_1470 = 60;
	sGynecology[4].power_980 = 1;
	sGynecology[4].power_635 = 1;
	sGynecology[4].poswidth = 1000;
	sGynecology[4].negwidth = 1000; 	
	
	//1470nm, CW 10w 15s Ton
	sGynecology[5].name = "Laser Vaginal Rejuvenation+ 600J"; 
	sGynecology[5].channel = LASER_CHANNEL_1470;
	sGynecology[5].pulse_mode = LASER_MODE_CW; 
	sGynecology[5].power_1470 = 100;
	sGynecology[5].power_980 = 1;
	sGynecology[5].power_635 = 1;
	sGynecology[5].poswidth = 15000;
	sGynecology[5].negwidth = 1000; 	
	
	//1470nm, CW 5w
	sGynecology[6].name = "Stress Incontinence, 75J";
	sGynecology[6].channel = LASER_CHANNEL_1470;
	sGynecology[6].pulse_mode = LASER_MODE_CW; 
	sGynecology[6].power_1470 = 50;
	sGynecology[6].power_980 = 1;
	sGynecology[6].power_635 = 1;
	sGynecology[6].poswidth = 1000;
	sGynecology[6].negwidth = 1000; 
	
	//1470nm, CW 5w
	sGynecology[7].name = "Infection control, 50J";
	sGynecology[7].channel = LASER_CHANNEL_1470;
	sGynecology[7].pulse_mode = LASER_MODE_CW; 
	sGynecology[7].power_1470 = 50;
	sGynecology[7].power_980 = 1;
	sGynecology[7].power_635 = 1;
	sGynecology[7].poswidth = 1000;
	sGynecology[7].negwidth = 1000; 	
	
	//1470nm, CW 8w
	sGynecology[8].name = "Treatment after Menopause, 480J";
	sGynecology[8].channel = LASER_CHANNEL_1470;
	sGynecology[8].pulse_mode = LASER_MODE_CW; 
	sGynecology[8].power_1470 = 80;
	sGynecology[8].power_980 = 1;
	sGynecology[8].power_635 = 1;
	sGynecology[8].poswidth = 1000;
	sGynecology[8].negwidth = 1000; 	

	//1470nm 12w CW
	sGynecology[9].name = "Hysteroscopy Myomas";
	sGynecology[9].channel = LASER_CHANNEL_1470;
	sGynecology[9].pulse_mode = LASER_MODE_CW; 
	sGynecology[9].power_1470 = 120;
	sGynecology[9].power_980 = 1;
	sGynecology[9].power_635 = 1;
	sGynecology[9].poswidth = 1000;
	sGynecology[9].negwidth = 1000;
	
	//1470nm 8w CW
	sGynecology[10].name = "Hysteroscopy Polyps";
	sGynecology[10].channel = LASER_CHANNEL_1470;
	sGynecology[10].pulse_mode = LASER_MODE_CW; 
	sGynecology[10].power_1470 = 80;
	sGynecology[10].power_980 = 1;
	sGynecology[10].power_635 = 1;
	sGynecology[10].poswidth = 1000;
	sGynecology[10].negwidth = 1000;	
	
	//1470nm 10w CW
	sGynecology[11].name = "Hysteroscopy Septum";
	sGynecology[11].channel = LASER_CHANNEL_1470;
	sGynecology[11].pulse_mode = LASER_MODE_CW; 
	sGynecology[11].power_1470 = 100;
	sGynecology[11].power_980 = 1;
	sGynecology[11].power_635 = 1;
	sGynecology[11].poswidth = 1000;
	sGynecology[11].negwidth = 1000;		
	
	//1470nm 10w CW
	sGynecology[12].name = "Hysteroscopy Adhesion";
	sGynecology[12].channel = LASER_CHANNEL_1470;
	sGynecology[12].pulse_mode = LASER_MODE_CW; 
	sGynecology[12].power_1470 = 100;
	sGynecology[12].power_980 = 1;
	sGynecology[12].power_635 = 1;
	sGynecology[12].poswidth = 1000;
	sGynecology[12].negwidth = 1000;		
	
	//1470nm 12w CW
	sGynecology[13].name = "Hysteroscopy Dysmorphie Uterus";
	sGynecology[13].channel = LASER_CHANNEL_1470;
	sGynecology[13].pulse_mode = LASER_MODE_CW; 
	sGynecology[13].power_1470 = 120;
	sGynecology[13].power_980 = 1;
	sGynecology[13].power_635 = 1;
	sGynecology[13].poswidth = 1000;
	sGynecology[13].negwidth = 1000;		
	
	//1470nm 12w CW
	sGynecology[14].name = "Hysteroscopy Isthmocele";
	sGynecology[14].channel = LASER_CHANNEL_1470;
	sGynecology[14].pulse_mode = LASER_MODE_CW; 
	sGynecology[14].power_1470 = 120;
	sGynecology[14].power_980 = 1;
	sGynecology[14].power_635 = 1;
	sGynecology[14].poswidth = 1000;
	sGynecology[14].negwidth = 1000;		
	
	//1470nm 12w CW
	sGynecology[15].name = "Hysteroscopy T-Shape Uterus";
	sGynecology[15].channel = LASER_CHANNEL_1470;
	sGynecology[15].pulse_mode = LASER_MODE_CW; 
	sGynecology[15].power_1470 = 120;
	sGynecology[15].power_980 = 1;
	sGynecology[15].power_635 = 1;
	sGynecology[15].poswidth = 1000;
	sGynecology[15].negwidth = 1000;		
	
	//1470nm 12w CW
	sGynecology[16].name = "Laparoscopy Myomas";
	sGynecology[16].channel = LASER_CHANNEL_1470;
	sGynecology[16].pulse_mode = LASER_MODE_CW; 
	sGynecology[16].power_1470 = 120;
	sGynecology[16].power_980 = 1;
	sGynecology[16].power_635 = 1;
	sGynecology[16].poswidth = 1000;
	sGynecology[16].negwidth = 1000;

	//1470nm 10w CW
	sGynecology[17].name = "Laparoscopy Ovarian Cysts";
	sGynecology[17].channel = LASER_CHANNEL_1470;
	sGynecology[17].pulse_mode = LASER_MODE_CW; 
	sGynecology[17].power_1470 = 100;
	sGynecology[17].power_980 = 1;
	sGynecology[17].power_635 = 1;
	sGynecology[17].poswidth = 1000;
	sGynecology[17].negwidth = 1000;
	
	//1470nm 10w CW
	sGynecology[18].name = "Laparoscopy Adhesion";
	sGynecology[18].channel = LASER_CHANNEL_1470;
	sGynecology[18].pulse_mode = LASER_MODE_CW; 
	sGynecology[18].power_1470 = 100;
	sGynecology[18].power_980 = 1;
	sGynecology[18].power_635 = 1;
	sGynecology[18].poswidth = 1000;
	sGynecology[18].negwidth = 1000;
	
	//1470nm 10w CW
	sGynecology[19].name = "Laparoscopy Salpingectomy";
	sGynecology[19].channel = LASER_CHANNEL_1470;
	sGynecology[19].pulse_mode = LASER_MODE_CW; 
	sGynecology[19].power_1470 = 100;
	sGynecology[19].power_980 = 1;
	sGynecology[19].power_635 = 1;
	sGynecology[19].poswidth = 1000;
	sGynecology[19].negwidth = 1000;
	
	//1470nm 10w CW
	sGynecology[20].name = "Laparoscopy Cysts";
	sGynecology[20].channel = LASER_CHANNEL_1470;
	sGynecology[20].pulse_mode = LASER_MODE_CW; 
	sGynecology[20].power_1470 = 100;
	sGynecology[20].power_980 = 1;
	sGynecology[20].power_635 = 1;
	sGynecology[20].poswidth = 1000;
	sGynecology[20].negwidth = 1000;	
	
	//1470nm 10w CW
	sGynecology[21].name = "Laparoscopy Endometriosis";
	sGynecology[21].channel = LASER_CHANNEL_1470;
	sGynecology[21].pulse_mode = LASER_MODE_CW; 
	sGynecology[21].power_1470 = 100;
	sGynecology[21].power_980 = 1;
	sGynecology[21].power_635 = 1;
	sGynecology[21].poswidth = 1000;
	sGynecology[21].negwidth = 1000;
	
/*****************************************************************************/
	//1470nm, Pulse 7w 1s Ton, 5s Toff
	sNeurosurgery[0].name = "PLDD L2-L3, L3-L4, L5-S1 800-1500J";
	sNeurosurgery[0].channel = LASER_CHANNEL_1470;
	sNeurosurgery[0].pulse_mode = LASER_MODE_MP; 
	sNeurosurgery[0].power_1470 = 70;
	sNeurosurgery[0].power_980 = 1;
	sNeurosurgery[0].power_635 = 1;
	sNeurosurgery[0].poswidth = 1000;
	sNeurosurgery[0].negwidth = 5000;

	//1470nm, Pulse 7w 1s Ton, 5s Toff
	sNeurosurgery[1].name = "PLDD L4-L5 Total 800-1800J";
	sNeurosurgery[1].channel = LASER_CHANNEL_1470;
	sNeurosurgery[1].pulse_mode = LASER_MODE_MP; 
	sNeurosurgery[1].power_1470 = 70;
	sNeurosurgery[1].power_980 = 1;
	sNeurosurgery[1].power_635 = 1;
	sNeurosurgery[1].poswidth = 1000;
	sNeurosurgery[1].negwidth = 5000;
	
	//1470nm, Pulse 7w, 1s Ton, 5s Toff
	sNeurosurgery[2].name = "PLDD 980nm";
	sNeurosurgery[2].channel = LASER_CHANNEL_980;
	sNeurosurgery[2].pulse_mode = LASER_MODE_MP; 
	sNeurosurgery[2].power_1470 = 1;
	sNeurosurgery[2].power_980 = 75;
	sNeurosurgery[2].power_635 = 1;
	sNeurosurgery[2].poswidth = 700;
	sNeurosurgery[2].negwidth = 700;		
	
	//1470nm, Pulse 7w, 1s Ton, 5s Toff
	sNeurosurgery[3].name = "Tumour 1470nm";
	sNeurosurgery[3].channel = LASER_CHANNEL_1470;
	sNeurosurgery[3].pulse_mode = LASER_MODE_MP; 
	sNeurosurgery[3].power_1470 = 70;
	sNeurosurgery[3].power_980 = 1;
	sNeurosurgery[3].power_635 = 1;
	sNeurosurgery[3].poswidth = 1000;
	sNeurosurgery[3].negwidth = 5000;	
	
	//980m, Pulse 8w 1s Ton, 5s Toff
	sNeurosurgery[4].name = "Tumour 980nm";
	sNeurosurgery[4].channel = LASER_CHANNEL_980;
	sNeurosurgery[4].pulse_mode = LASER_MODE_MP; 
	sNeurosurgery[4].power_1470 = 1;
	sNeurosurgery[4].power_980 = 80;
	sNeurosurgery[4].power_635 = 1;
	sNeurosurgery[4].poswidth = 1000;
	sNeurosurgery[4].negwidth = 5000;
/*****************************************************************************/
	//ENT
	//980nm 13w CW
	sENT[0].name = "Vocal Polyps";
	sENT[0].channel = LASER_CHANNEL_980;
	sENT[0].pulse_mode = LASER_MODE_CW; 
	sENT[0].power_1470 = 1;
	sENT[0].power_980 = 130;
	sENT[0].power_635 = 1;
	sENT[0].poswidth = 1000;
	sENT[0].negwidth = 1000;

	//980nm 12w CW
	sENT[1].name = "Cordectomy";
	sENT[1].channel = LASER_CHANNEL_980;
	sENT[1].pulse_mode = LASER_MODE_CW; 
	sENT[1].power_1470 = 1;
	sENT[1].power_980 = 120;
	sENT[1].power_635 = 1;
	sENT[1].poswidth = 1000;
	sENT[1].negwidth = 1000;
	
	//980nm 14w CW
	sENT[2].name = "Laryngeal Carcinoma";
	sENT[2].channel = LASER_CHANNEL_980;
	sENT[2].pulse_mode = LASER_MODE_CW; 
	sENT[2].power_1470 = 1;
	sENT[2].power_980 = 140;
	sENT[2].power_635 = 1;
	sENT[2].poswidth = 1000;
	sENT[2].negwidth = 1000;
	
	//980nm 14w CW
	sENT[3].name = "Haematomas";
	sENT[3].channel = LASER_CHANNEL_980;
	sENT[3].pulse_mode = LASER_MODE_CW; 
	sENT[3].power_1470 = 1;
	sENT[3].power_980 = 140;
	sENT[3].power_635 = 1;
	sENT[3].poswidth = 1000;
	sENT[3].negwidth = 1000;
	
	//980nm 14w CW
	sENT[4].name = "Fibromas";
	sENT[4].channel = LASER_CHANNEL_980;
	sENT[4].pulse_mode = LASER_MODE_CW; 
	sENT[4].power_1470 = 1;
	sENT[4].power_980 = 140;
	sENT[4].power_635 = 1;
	sENT[4].poswidth = 1000;
	sENT[4].negwidth = 1000;
	
	//980nm 14w CW
	sENT[5].name = "Larynxpapillomatosis";
	sENT[5].channel = LASER_CHANNEL_980;
	sENT[5].pulse_mode = LASER_MODE_CW; 
	sENT[5].power_1470 = 1;
	sENT[5].power_980 = 140;
	sENT[5].power_635 = 1;
	sENT[5].poswidth = 1000;
	sENT[5].negwidth = 1000;
	
	//980nm 13w CW
	sENT[6].name = "Paracentesis";		
	sENT[6].channel = LASER_CHANNEL_980;
	sENT[6].pulse_mode = LASER_MODE_CW; 
	sENT[6].power_1470 = 1;
	sENT[6].power_980 = 130;
	sENT[6].power_635 = 1;
	sENT[6].poswidth = 1000;
	sENT[6].negwidth = 1000;
	
	//980nm 13w CW
	sENT[7].name = "Acoustic Neuroma";
	sENT[7].channel = LASER_CHANNEL_980;
	sENT[7].pulse_mode = LASER_MODE_CW; 
	sENT[7].power_1470 = 1;
	sENT[7].power_980 = 130;
	sENT[7].power_635 = 1;
	sENT[7].poswidth = 1000;
	sENT[7].negwidth = 1000;
	
	//980nm 10w CW
	sENT[8].name = "Cholesteatoma";
	sENT[8].channel = LASER_CHANNEL_980;
	sENT[8].pulse_mode = LASER_MODE_CW; 
	sENT[8].power_1470 = 1;
	sENT[8].power_980 = 100;
	sENT[8].power_635 = 1;
	sENT[8].poswidth = 1000;
	sENT[8].negwidth = 1000;
	
	//980nm 13w CW
	sENT[9].name = "Tonsillectomy";
	sENT[9].channel = LASER_CHANNEL_980;
	sENT[9].pulse_mode = LASER_MODE_CW; 
	sENT[9].power_1470 = 1;
	sENT[9].power_980 = 130;
	sENT[9].power_635 = 1;
	sENT[9].poswidth = 1000;
	sENT[9].negwidth = 1000;
	
	//980nm 13w CW
	sENT[10].name = "Tumour Vaporisation";
	sENT[10].channel = LASER_CHANNEL_980;
	sENT[10].pulse_mode = LASER_MODE_CW; 
	sENT[10].power_1470 = 1;
	sENT[10].power_980 = 130;
	sENT[10].power_635 = 1;
	sENT[10].poswidth = 1000;
	sENT[10].negwidth = 1000;
	
	//980nm 10w CW
	sENT[11].name = "Uvulopalatoplasty (LAUP)";
	sENT[11].channel = LASER_CHANNEL_980;
	sENT[11].pulse_mode = LASER_MODE_CW; 
	sENT[11].power_1470 = 1;
	sENT[11].power_980 = 100;
	sENT[11].power_635 = 1;
	sENT[11].poswidth = 1000;
	sENT[11].negwidth = 1000;
	
	//980nm 13w CW
	sENT[12].name = "Conchotomy";
	sENT[12].channel = LASER_CHANNEL_980;
	sENT[12].pulse_mode = LASER_MODE_CW; 
	sENT[12].power_1470 = 1;
	sENT[12].power_980 = 130;
	sENT[12].power_635 = 1;
	sENT[12].poswidth = 1000;
	sENT[12].negwidth = 1000;
	
	//980nm 10w Pulse, 50ms Ton, 90ms Toff 
	sENT[13].name = "Dacryocystorhinostomy (DCR)";
	sENT[13].channel = LASER_CHANNEL_980;
	sENT[13].pulse_mode = LASER_MODE_MP; 
	sENT[13].power_1470 = 1;
	sENT[13].power_980 = 100;
	sENT[13].power_635 = 1;
	sENT[13].poswidth = 50;
	sENT[13].negwidth = 90;
	
	//980nm 10w CW
	sENT[14].name = "Turbinate Reduction";
	sENT[14].channel = LASER_CHANNEL_980;
	sENT[14].pulse_mode = LASER_MODE_CW; 
	sENT[14].power_1470 = 1;
	sENT[14].power_980 = 100;
	sENT[14].power_635 = 1;
	sENT[14].poswidth = 1000;
	sENT[14].negwidth = 1000;
	
	//980nm 12w CW
	sENT[15].name = "Nasal Polypectomy";
	sENT[15].channel = LASER_CHANNEL_980;
	sENT[15].pulse_mode = LASER_MODE_CW; 
	sENT[15].power_1470 = 1;
	sENT[15].power_980 = 120;
	sENT[15].power_635 = 1;
	sENT[15].poswidth = 1000;
	sENT[15].negwidth = 1000;
	
/*****************************************************************************/
	//Dermatology
	//980nm, CW 10W
	sDermatology[0].name = "Cut";
	sDermatology[0].channel = LASER_CHANNEL_980;
	sDermatology[0].pulse_mode = LASER_MODE_CW; 
	sDermatology[0].power_1470 = 1;
	sDermatology[0].power_980 = 100;
	sDermatology[0].power_635 = 1;
	sDermatology[0].poswidth = 1000;
	sDermatology[0].negwidth = 1000;
	//980nm, CW 6w
	sDermatology[1].name = "Coagulation";
	sDermatology[1].channel = LASER_CHANNEL_980;
	sDermatology[1].pulse_mode = LASER_MODE_CW; 
	sDermatology[1].power_1470 = 1;
	sDermatology[1].power_980 = 30;
	sDermatology[1].power_635 = 1;
	sDermatology[1].poswidth = 1000;
	sDermatology[1].negwidth = 1000;	
	//980nm, CW 8w
	sDermatology[2].name = "Moles Removal";
	sDermatology[2].channel = LASER_CHANNEL_980;
	sDermatology[2].pulse_mode = LASER_MODE_CW; 
	sDermatology[2].power_1470 = 1;
	sDermatology[2].power_980 = 80;
	sDermatology[2].power_635 = 1;
	sDermatology[2].poswidth = 1000;
	sDermatology[2].negwidth = 1000;
	//980nm, CW 10w
	sDermatology[3].name = "Warts Removal";
	sDermatology[3].channel = LASER_CHANNEL_980;
	sDermatology[3].pulse_mode = LASER_MODE_CW; 
	sDermatology[3].power_1470 = 1;
	sDermatology[3].power_980 = 100;
	sDermatology[3].power_635 = 1;
	sDermatology[3].poswidth = 1000;
	sDermatology[3].negwidth = 1000;
	//980nm, Pulse, 6w, 1s Ton, 1s Toff
	sDermatology[4].name = "Nail Fungus";
	sDermatology[4].channel = LASER_CHANNEL_980;
	sDermatology[4].pulse_mode = LASER_MODE_MP; 
	sDermatology[4].power_1470 = 1;
	sDermatology[4].power_980 = 60;
	sDermatology[4].power_635 = 1;
	sDermatology[4].poswidth = 1000;
	sDermatology[4].negwidth = 1000;
	//980nm, Pulse, 6w, 1s Ton, 1s Toff
	sDermatology[5].name = "Venectasia";
	sDermatology[5].channel = LASER_CHANNEL_980;
	sDermatology[5].pulse_mode = LASER_MODE_MP; 
	sDermatology[5].power_1470 = 1;
	sDermatology[5].power_980 = 150;
	sDermatology[5].power_635 = 1;
	sDermatology[5].poswidth = 70;
	sDermatology[5].negwidth = 120;
	//980nm, Pulse, 8w, 1s Ton, 5s Toff
	sDermatology[6].name = "Spider Vein 0.5mm";
	sDermatology[6].channel = LASER_CHANNEL_980;
	sDermatology[6].pulse_mode = LASER_MODE_MP; 
	sDermatology[6].power_1470 = 1;
	sDermatology[6].power_980 = 80;
	sDermatology[6].power_635 = 1;
	sDermatology[6].poswidth = 1000;
	sDermatology[6].negwidth = 5000;
	//980nm, Pulse, 8w, 1s Ton, 5s Toff
	sDermatology[7].name = "Spider Vein 1mm";
	sDermatology[7].channel = LASER_CHANNEL_980;
	sDermatology[7].pulse_mode = LASER_MODE_MP; 
	sDermatology[7].power_1470 = 1;
	sDermatology[7].power_980 = 80;
	sDermatology[7].power_635 = 1;
	sDermatology[7].poswidth = 1000;
	sDermatology[7].negwidth = 5000;
	//980nm, Pulse, 8w, 1s Ton, 5s Toff
	sDermatology[8].name = "Spider Vein 1.5mm";
	sDermatology[8].channel = LASER_CHANNEL_980;
	sDermatology[8].pulse_mode = LASER_MODE_MP; 
	sDermatology[8].power_1470 = 1;
	sDermatology[8].power_980 = 80;
	sDermatology[8].power_635 = 1;
	sDermatology[8].poswidth = 1000;
	sDermatology[8].negwidth = 5000;
/*****************************************************************************/
	//Liposuction
	//1470nm, 3w CW
	sLiposuction[0].name =  "Liposuction Under Eye";
	sLiposuction[0].channel = LASER_CHANNEL_1470;
	sLiposuction[0].pulse_mode = LASER_MODE_CW; 
	sLiposuction[0].power_1470 = 30;
	sLiposuction[0].power_980 = 1;
	sLiposuction[0].power_635 = 1;
	sLiposuction[0].poswidth = 1000;
	sLiposuction[0].negwidth = 1000;
	//1470nm 6w CW	
	sLiposuction[1].name = "Liposuction Chin";
	sLiposuction[1].channel = LASER_CHANNEL_1470;
	sLiposuction[1].pulse_mode = LASER_MODE_CW; 
	sLiposuction[1].power_1470 = 60;
	sLiposuction[1].power_980 = 1;
	sLiposuction[1].power_635 = 1;
	sLiposuction[1].poswidth = 1000;
	sLiposuction[1].negwidth = 1000;
	//1470nm 8w CW
	sLiposuction[2].name = "Liposuction Arm";
	sLiposuction[2].channel = LASER_CHANNEL_1470;
	sLiposuction[2].pulse_mode = LASER_MODE_CW; 
	sLiposuction[2].power_1470 = 80;
	sLiposuction[2].power_980 = 1;
	sLiposuction[2].power_635 = 1;
	sLiposuction[2].poswidth = 1000;
	sLiposuction[2].negwidth = 1000;
	//1470nm 12 CW
	sLiposuction[3].name = "Liposuction Abdomen";
	sLiposuction[3].channel = LASER_CHANNEL_1470;
	sLiposuction[3].pulse_mode = LASER_MODE_CW; 
	sLiposuction[3].power_1470 = 120;
	sLiposuction[3].power_980 = 1;
	sLiposuction[3].power_635 = 1;
	sLiposuction[3].poswidth = 1000;
	sLiposuction[3].negwidth = 1000;
	//1470nm 10w CW
	sLiposuction[4].name = "Liposuction Buttock";
	sLiposuction[4].channel = LASER_CHANNEL_1470;
	sLiposuction[4].pulse_mode = LASER_MODE_CW; 
	sLiposuction[4].power_1470 = 100;
	sLiposuction[4].power_980 = 1;
	sLiposuction[4].power_635 = 1;
	sLiposuction[4].poswidth = 1000;
	sLiposuction[4].negwidth = 1000;
	//1470nm 8w CW
	sLiposuction[5].name = "Liposuction Thigh";
	sLiposuction[5].channel = LASER_CHANNEL_1470;
	sLiposuction[5].pulse_mode = LASER_MODE_CW; 
	sLiposuction[5].power_1470 = 80;
	sLiposuction[5].power_980 = 1;
	sLiposuction[5].power_635 = 1;
	sLiposuction[5].poswidth = 1000;
	sLiposuction[5].negwidth = 1000;
	//1470nm 8w CW	
	sLiposuction[6].name = "Gynecomastia";
	sLiposuction[6].channel = LASER_CHANNEL_1470;
	sLiposuction[6].pulse_mode = LASER_MODE_CW; 
	sLiposuction[6].power_1470 = 80;
	sLiposuction[6].power_980 = 1;
	sLiposuction[6].power_635 = 1;
	sLiposuction[6].poswidth = 1000;
	sLiposuction[6].negwidth = 1000;
/*****************************************************************************/
	//DENTISTRY
	//
	sDentistry[0].name = "Incision & Drainage Of Abscess";
	sDentistry[0].channel = LASER_CHANNEL_980;
	sDentistry[0].pulse_mode = LASER_MODE_CW; 
	sDentistry[0].power_1470 = 1;
	sDentistry[0].power_980 = 12;
	sDentistry[0].power_635 = 1;
	sDentistry[0].poswidth = 1000;
	sDentistry[0].negwidth = 1000;
	//
	sDentistry[1].name = "Excision & Incisional Biopsy";
	sDentistry[1].channel = LASER_CHANNEL_980;
	sDentistry[1].pulse_mode = LASER_MODE_CW; 
	sDentistry[1].power_1470 = 1;
	sDentistry[1].power_980 = 10;
	sDentistry[1].power_635 = 1;
	sDentistry[1].poswidth = 1000;
	sDentistry[1].negwidth = 1000;
	//
	sDentistry[2].name = "Aphthous Ulcer & herpetic";
	sDentistry[2].channel = LASER_CHANNEL_980;
	sDentistry[2].pulse_mode = LASER_MODE_MP; 
	sDentistry[2].power_1470 = 1;
	sDentistry[2].power_980 = 20;
	sDentistry[2].power_635 = 1;
	sDentistry[2].poswidth = 50;
	sDentistry[2].negwidth = 50;	
	//
	sDentistry[3].name = "Pulpotomy";
	sDentistry[3].channel = LASER_CHANNEL_980;
	sDentistry[3].pulse_mode = LASER_MODE_MP; 
	sDentistry[3].power_1470 = 1;
	sDentistry[3].power_980 = 15;
	sDentistry[3].power_635 = 1;
	sDentistry[3].poswidth = 50;
	sDentistry[3].negwidth = 50;	
	//
	sDentistry[4].name = "Expose of unerupted teeth";
	sDentistry[4].channel = LASER_CHANNEL_980;
	sDentistry[4].pulse_mode = LASER_MODE_CW; 
	sDentistry[4].power_1470 = 1;
	sDentistry[4].power_980 = 10;
	sDentistry[4].power_635 = 1;
	sDentistry[4].poswidth = 1000;
	sDentistry[4].negwidth = 1000;	
	//
	sDentistry[5].name = "Fibroma Removal";
	sDentistry[5].channel = LASER_CHANNEL_980;
	sDentistry[5].pulse_mode = LASER_MODE_CW; 
	sDentistry[5].power_1470 = 1;
	sDentistry[5].power_980 = 10;
	sDentistry[5].power_635 = 1;
	sDentistry[5].poswidth = 1000;
	sDentistry[5].negwidth = 1000;	
	//
	sDentistry[6].name = "Frenectomy";
	sDentistry[6].channel = LASER_CHANNEL_980;
	sDentistry[6].pulse_mode = LASER_MODE_CW; 
	sDentistry[6].power_1470 = 1;
	sDentistry[6].power_980 = 10;
	sDentistry[6].power_635 = 1;
	sDentistry[6].poswidth = 1000;
	sDentistry[6].negwidth = 1000;	
	//
	sDentistry[7].name = "Gingivectomy";
	sDentistry[7].channel = LASER_CHANNEL_980;
	sDentistry[7].pulse_mode = LASER_MODE_CW; 
	sDentistry[7].power_1470 = 1;
	sDentistry[7].power_980 = 10;
	sDentistry[7].power_635 = 1;
	sDentistry[7].poswidth = 1000;
	sDentistry[7].negwidth = 1000;	
	//
	sDentistry[8].name = "Gingivoplasty";
	sDentistry[8].channel = LASER_CHANNEL_980;
	sDentistry[8].pulse_mode = LASER_MODE_CW; 
	sDentistry[8].power_1470 = 1;
	sDentistry[8].power_980 = 10;
	sDentistry[8].power_635 = 1;
	sDentistry[8].poswidth = 1000;
	sDentistry[8].negwidth = 1000;	
	//
	sDentistry[9].name = "Gingival incision & excision Hemostasis";
	sDentistry[9].channel = LASER_CHANNEL_980;
	sDentistry[9].pulse_mode = LASER_MODE_CW; 
	sDentistry[9].power_1470 = 1;
	sDentistry[9].power_980 = 10;
	sDentistry[9].power_635 = 1;
	sDentistry[9].poswidth = 1000;
	sDentistry[9].negwidth = 1000;	
	//
	sDentistry[10].name = "Crown Lenthening";
	sDentistry[10].channel = LASER_CHANNEL_980;
	sDentistry[10].pulse_mode = LASER_MODE_MP; 
	sDentistry[10].power_1470 = 1;
	sDentistry[10].power_980 = 18;
	sDentistry[10].power_635 = 1;
	sDentistry[10].poswidth = 50;
	sDentistry[10].negwidth = 50;	
	//
	sDentistry[11].name = "Reduction of Gingival Hypertrophy";
	sDentistry[11].channel = LASER_CHANNEL_980;
	sDentistry[11].pulse_mode = LASER_MODE_CW; 
	sDentistry[11].power_1470 = 1;
	sDentistry[11].power_980 = 15;
	sDentistry[11].power_635 = 1;
	sDentistry[11].poswidth = 1000;
	sDentistry[11].negwidth = 1000;	
	//
	sDentistry[12].name = "Implant Recovery";
	sDentistry[12].channel = LASER_CHANNEL_980;
	sDentistry[12].pulse_mode = LASER_MODE_CW; 
	sDentistry[12].power_1470 = 1;
	sDentistry[12].power_980 = 10;
	sDentistry[12].power_635 = 1;
	sDentistry[12].poswidth = 1000;
	sDentistry[12].negwidth = 1000;	
	//
	sDentistry[15].name = "Hemostasis and Coagulation";
	sDentistry[15].channel = LASER_CHANNEL_980;
	sDentistry[15].pulse_mode = LASER_MODE_CW; 
	sDentistry[15].power_1470 = 1;
	sDentistry[15].power_980 = 12;
	sDentistry[15].power_635 = 1;
	sDentistry[15].poswidth = 1000;
	sDentistry[15].negwidth = 1000;
	//
	sDentistry[14].name = "Gingival Troughing";
	sDentistry[14].channel = LASER_CHANNEL_980;
	sDentistry[14].pulse_mode = LASER_MODE_CW; 
	sDentistry[14].power_1470 = 1;
	sDentistry[14].power_980 = 18;
	sDentistry[14].power_635 = 1;
	sDentistry[14].poswidth = 1000;
	sDentistry[14].negwidth = 1000;
	//
	sDentistry[15].name = "Operculectomy";
	sDentistry[15].channel = LASER_CHANNEL_980;
	sDentistry[15].pulse_mode = LASER_MODE_CW; 
	sDentistry[15].power_1470 = 1;
	sDentistry[15].power_980 = 15;
	sDentistry[15].power_635 = 1;
	sDentistry[15].poswidth = 1000;
	sDentistry[15].negwidth = 1000;
	//
	sDentistry[16].name = "Infected Pockets Removal";
	sDentistry[16].channel = LASER_CHANNEL_980;
	sDentistry[16].pulse_mode = LASER_MODE_CW; 
	sDentistry[16].power_1470 = 1;
	sDentistry[16].power_980 = 18;
	sDentistry[16].power_635 = 1;
	sDentistry[16].poswidth = 1000;
	sDentistry[16].negwidth = 1000;
	//
	sDentistry[17].name = "Gingival Bleeding Index";
	sDentistry[17].channel = LASER_CHANNEL_980;
	sDentistry[17].pulse_mode = LASER_MODE_CW; 
	sDentistry[17].power_1470 = 1;
	sDentistry[17].power_980 = 8;
	sDentistry[17].power_635 = 1;
	sDentistry[17].poswidth = 1000;
	sDentistry[17].negwidth = 1000;

	//
	sDentistry[18].name = "Sulcular Debridement";
	sDentistry[18].channel = LASER_CHANNEL_980;
	sDentistry[18].pulse_mode = LASER_MODE_CW; 
	sDentistry[18].power_1470 = 1;
	sDentistry[18].power_980 = 8;
	sDentistry[18].power_635 = 1;
	sDentistry[18].poswidth = 1000;
	sDentistry[18].negwidth = 1000;
	//
	sDentistry[19].name = "Leukoplakia";
	sDentistry[19].channel = LASER_CHANNEL_980;
	sDentistry[19].pulse_mode = LASER_MODE_CW; 
	sDentistry[19].power_1470 = 1;
	sDentistry[19].power_980 = 10;
	sDentistry[19].power_635 = 1;
	sDentistry[19].poswidth = 1000;
	sDentistry[19].negwidth = 1000;
	//
	sDentistry[20].name = "Vestibuloplasty";
	sDentistry[20].channel = LASER_CHANNEL_980;
	sDentistry[20].pulse_mode = LASER_MODE_CW; 
	sDentistry[20].power_1470 = 1;
	sDentistry[20].power_980 = 10;
	sDentistry[20].power_635 = 1;
	sDentistry[20].poswidth = 1000;
	sDentistry[20].negwidth = 1000;
	//
	sDentistry[21].name = "Oral Papilectomies";
	sDentistry[21].channel = LASER_CHANNEL_980;
	sDentistry[21].pulse_mode = LASER_MODE_CW; 
	sDentistry[21].power_1470 = 1;
	sDentistry[21].power_980 = 9;
	sDentistry[21].power_635 = 1;
	sDentistry[21].poswidth = 1000;
	sDentistry[21].negwidth = 1000;
	//
	sDentistry[22].name = "Tooth Whitening";
	sDentistry[22].channel = LASER_CHANNEL_980;
	sDentistry[22].pulse_mode = LASER_MODE_MP; 
	sDentistry[22].power_1470 = 1;
	sDentistry[22].power_980 = 50;
	sDentistry[22].power_635 = 1;
	sDentistry[22].poswidth = 50;
	sDentistry[22].negwidth = 50;
/*****************************************************************************/
	//Therapy
	//980nm 8w pulse, 50ms on, 50ms off
	sTherapy[0].name = "Orthopedie Pain";
	sTherapy[0].channel = LASER_CHANNEL_980;
	sTherapy[0].pulse_mode = LASER_MODE_MP; 
	sTherapy[0].power_1470 = 1;
	sTherapy[0].power_980 = 80;
	sTherapy[0].power_635 = 1;
	sTherapy[0].poswidth = 50;
	sTherapy[0].negwidth = 50;
	//980nm 8w pulse 50ms on, 50ms off
	sTherapy[1].name = "Spine Pain";
	sTherapy[1].channel = LASER_CHANNEL_980;
	sTherapy[1].pulse_mode = LASER_MODE_MP; 
	sTherapy[1].power_1470 = 1;
	sTherapy[1].power_980 = 80;
	sTherapy[1].power_635 = 1;
	sTherapy[1].poswidth = 50;
	sTherapy[1].negwidth = 50;
	//980nm 10w pulse 50ms on, 50ms off
	sTherapy[2].name = "Frozen Shoulder";
	sTherapy[2].channel = LASER_CHANNEL_980;
	sTherapy[2].pulse_mode = LASER_MODE_MP; 
	sTherapy[2].power_1470 = 1;
	sTherapy[2].power_980 = 100;
	sTherapy[2].power_635 = 1;
	sTherapy[2].poswidth = 50;
	sTherapy[2].negwidth = 50;
	//980nm 6w pulse 50ms on, 50ms off
	sTherapy[3].name = "Plantar Facilities";
	sTherapy[3].channel = LASER_CHANNEL_980;
	sTherapy[3].pulse_mode = LASER_MODE_MP; 
	sTherapy[3].power_1470 = 1;
	sTherapy[3].power_980 = 60;
	sTherapy[3].power_635 = 1;
	sTherapy[3].poswidth = 50;
	sTherapy[3].negwidth = 50;
	//980nm 6w pulse 50ms on, 50ms off
	sTherapy[4].name = "Pain Management";
	sTherapy[4].channel = LASER_CHANNEL_980;
	sTherapy[4].pulse_mode = LASER_MODE_MP; 
	sTherapy[4].power_1470 = 1;
	sTherapy[4].power_980 = 60;
	sTherapy[4].power_635 = 1;
	sTherapy[4].poswidth = 50;
	sTherapy[4].negwidth = 50;
	//635nm CW
	sTherapy[5].name = "Would Healing";
	sTherapy[5].channel = LASER_CHANNEL_635;
	sTherapy[5].pulse_mode = LASER_MODE_CW; 
	sTherapy[5].power_1470 = 1;
	sTherapy[5].power_980 = 1;
	sTherapy[5].power_635 = 5;
	sTherapy[5].poswidth = 1000;
	sTherapy[5].negwidth = 1000;
	//635nm CW
	sTherapy[6].name = "Low Laser Therapy";
	sTherapy[6].channel = LASER_CHANNEL_635;
	sTherapy[6].pulse_mode = LASER_MODE_CW; 
	sTherapy[6].power_1470 = 1;
	sTherapy[6].power_980 = 1;
	sTherapy[6].power_635 = 5;
	sTherapy[6].poswidth = 1000;
	sTherapy[6].negwidth = 1000;
	//635nm CW
	sTherapy[7].name = "Biostimulation";
	sTherapy[7].channel = LASER_CHANNEL_635;
	sTherapy[7].pulse_mode = LASER_MODE_CW; 
	sTherapy[7].power_1470 = 1;
	sTherapy[7].power_980 = 1;
	sTherapy[7].power_635 = 5;
	sTherapy[7].poswidth = 1000;
	sTherapy[7].negwidth = 1000;
#endif

#if defined(MODEL_PVGLS_7W_1940)
	//S0
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (0 * 64)]), "EVLA Thigh CW i"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (0 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (0 * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_1470 + (0 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (0 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (0 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (0 * 64)] = 40;
	FDRAM0[FD_LASER_POSWIDTH + (0 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (0 * 64)] = 1000;	
	//S1
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (1 * 64)]), "EVLA Thigh Pulse i"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (1 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (1 * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_1470 + (1 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (1 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (1 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (1 * 64)] = 40;
	FDRAM0[FD_LASER_POSWIDTH + (1 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (1 * 64)] = 1000;	
	//S2
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (2 * 64)]), "EVLA Thigh CW ii"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (2 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (2 * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_1470 + (2 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (2 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (2 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (2 * 64)] = 50;
	FDRAM0[FD_LASER_POSWIDTH + (2 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (2 * 64)] = 1000;
	//S3
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (3 * 64)]), "EVLA Thigh Pulse ii"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (3 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (3 * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_1470 + (3 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (3 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (3 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (3 * 64)] = 50;
	FDRAM0[FD_LASER_POSWIDTH + (3 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (3 * 64)] = 1000;
	//S4
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (4 * 64)]), "EVLA Thigh CW iii"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (4 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (4 * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_1470 + (4 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (4 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (4 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (4 * 64)] = 60;
	FDRAM0[FD_LASER_POSWIDTH + (4 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (4 * 64)] = 1000;
	//S5
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (5 * 64)]), "EVLA Thigh Pulse iii"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (5 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (5 * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_1470 + (5 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (5 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (5 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (5 * 64)] = 60;
	FDRAM0[FD_LASER_POSWIDTH + (5 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (5 * 64)] = 1000;
	//S6
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (6 * 64)]), "EVLA calf CW i"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (6 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (6 * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_1470 + (6 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (6 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (6 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (6 * 64)] = 20;
	FDRAM0[FD_LASER_POSWIDTH + (6 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (6 * 64)] = 1000;
	//S7
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (7 * 64)]), "EVLA calf Pulse i"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (7 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (7 * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_1470 + (7 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (7 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (7 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (7 * 64)] = 20;
	FDRAM0[FD_LASER_POSWIDTH + (7 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (7 * 64)] = 1000;
	//S8
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (8 * 64)]), "EVLA calf CW ii"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (8 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (8 * 64)] = LASER_MODE_CW;
	FDRAM0[FD_LASER_POWER_1470 + (8 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (8 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (8 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (8 * 64)] = 30;
	FDRAM0[FD_LASER_POSWIDTH + (8 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (8 * 64)] = 1000;
	//S9
	sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (9* 64)]), "EVLA calf Pulse ii"); 
	FDRAM0[FD_LASER_CHANNEL_SELECT + (9 * 64)] = LASER_CHANNEL_1940;
	FDRAM0[FD_LASER_PULSE_MODE + (9 * 64)] = LASER_MODE_MP;
	FDRAM0[FD_LASER_POWER_1470 + (9 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_980 + (9 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_635 + (9 * 64)] = 0;
	FDRAM0[FD_LASER_POWER_1940 + (9 * 64)] = 30;
	FDRAM0[FD_LASER_POSWIDTH + (9 * 64)] = 1000;
	FDRAM0[FD_LASER_NEGWIDTH + (9 * 64)] = 1000;
#endif

}
