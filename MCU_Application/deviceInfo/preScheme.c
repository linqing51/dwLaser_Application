//预设方案内容
#include "preScheme.h"



#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
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
		case SCHEME_DENTISTRY:{
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
			NVRAM0[EM_LASER_POWER_CH0] = sPhlebology[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sPhlebology[index].power_ch1;
			NVRAM0[EM_LASER_POWER_635] = sPhlebology[index].power_red;
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
			NVRAM0[EM_LASER_POWER_CH0] = sProctology[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sProctology[index].power_ch1;
			NVRAM0[EM_LASER_POWER_635] = sProctology[index].power_red;
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
			NVRAM0[EM_LASER_POWER_CH0] = sGynecology[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sGynecology[index].power_ch1;
			NVRAM0[EM_LASER_POWER_635] = sGynecology[index].power_red;
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
			NVRAM0[EM_LASER_POWER_CH0] = sENT[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sENT[index].power_ch1;
			NVRAM0[EM_LASER_POWER_635] = sENT[index].power_red;
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
			NVRAM0[EM_LASER_POWER_CH0] = sNeurosurgery[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sNeurosurgery[index].power_ch1;
			NVRAM0[EM_LASER_POWER_635] = sNeurosurgery[index].power_red;
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
			NVRAM0[EM_LASER_POWER_CH0] = sDermatology[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sDermatology[index].power_ch1;
			NVRAM0[EM_LASER_POWER_635] = sDermatology[index].power_red;
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
			NVRAM0[EM_LASER_POWER_CH0] = sLiposuction[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sLiposuction[index].power_ch1;
			NVRAM0[EM_LASER_POWER_635] = sLiposuction[index].power_red;
			NVRAM0[EM_LASER_POSWIDTH] = sLiposuction[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sLiposuction[index].negwidth;
			break;
		}
		case SCHEME_DENTISTRY:{
			if(index > (CONFIG_DENTISRTY_SIZE - 1)){
				index = (CONFIG_DENTISRTY_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sDentistry[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sDentistry[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sDentistry[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_CH0] = sDentistry[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sDentistry[index].power_ch1;
			NVRAM0[EM_LASER_POWER_635] = sDentistry[index].power_red;
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
			NVRAM0[EM_LASER_POWER_CH0] = sTherapy[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sTherapy[index].power_ch1;
			NVRAM0[EM_LASER_POWER_635] = sTherapy[index].power_red;
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
			NVRAM0[EM_LASER_POWER_CH0] = FDRAM0[index * 64 + FD_LASER_POWER_CH0];
			NVRAM0[EM_LASER_POWER_CH1] = FDRAM0[index * 64 + FD_LASER_POWER_CH1];
			NVRAM0[EM_LASER_POWER_635] = FDRAM0[index * 64 + FD_LASER_POWER_RED];
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
	printf("%s,%d,%s:scheme power 1470:%d\n", __FILE__, __LINE__, __func__,NVRAM0[EM_LASER_POWER_CH0]);
	printf("%s,%d,%s:scheme power 980:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH1]);
	printf("%s,%d,%s:scheme power 635:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_635]);
	printf("%s,%d,%s:scheme poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POSWIDTH]);
	printf("%s,%d,%s:scheme negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_NEGWIDTH]);
}

void schemeInit(uint8_t reDef){//治疗方案初始化
	myScheme_t *p;
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
/***************************************************************************/
	//Phlebology
	//1470nm, CW 8w 80J/cm
	sPhlebology[0].name = "EVLA Thigh";
	sPhlebology[0].channel = LASER_CHANNEL_CH0;
	sPhlebology[0].pulse_mode = LASER_MODE_CW; 
	sPhlebology[0].power_ch0 = 80;
	sPhlebology[0].power_ch1 = 1;
	sPhlebology[0].power_red = 1;
	sPhlebology[0].poswidth = 1000;
	sPhlebology[0].negwidth = 1000;
	
	//1470nm, CW 6w 60J/cm
	sPhlebology[1].name = "EVLA calf";
	sPhlebology[1].channel = LASER_CHANNEL_CH0;
	sPhlebology[1].pulse_mode = LASER_MODE_CW; 
	sPhlebology[1].power_ch0 = 60;
	sPhlebology[1].power_ch1 = 1;
	sPhlebology[1].power_red = 1;
	sPhlebology[1].poswidth = 1000;
	sPhlebology[1].negwidth = 1000;
	
	//1470nm, CW 3w 30J/cm
	p = &sPhlebology[2];
	p->name = "EVLA Small Vessel";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 30;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
/***************************************************************************/
	//Proctology
	//1470nm, CW 6w, 250 Joules per hemorrhoid
	p = &sProctology[0];
	p->name = "Hemorrhoids Grade 2, 250J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm, CW 7w, 350 Joules per hemorrhoid
	p = &sProctology[1];
	p->name ="Hemorrhoids Grade 3, 350J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	//1470nm, CW 8w, 350 Joules per hemorrhoid
	p = &sProctology[2];
	p->name = "Hemorrhoids Grade 4, 350J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	//1470nm, CW 10w 100J/cm
	p = &sProctology[3];
	p->name = "Fistula";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 

	//1470nm, CW 10w 100J/cm
	p = &sProctology[4];
	p->name = "Pilonidal Sinus";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	//1470nm, CW 7w 100J/cm
	p = &sProctology[5];
	p->name = "Fissure Ablation";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
/*****************************************************************************/
	//1470nm, Pulse 6w 500ms Ton, 500ms Toff
	p = &sGynecology[0];
	p->name = "Laser Vaginal Tightening 1st 600J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 60;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 500;
	p->negwidth = 500; 	
	
	//1470nm, Pulse 7w 500ms Ton, 500ms Toff
	p = &sGynecology[1];
	p->name = "Laser Vaginal Tightening 2nd 600J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 500;
	p->negwidth = 500; 
	
	//1470nm, Pulse 8w 500ms Ton, 500ms Toff
	p = &sGynecology[2];
	p->name = "Laser Vaginal Tightening 3rd 600J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 500;
	p->negwidth = 500; 
	
	//1470nm, Pulse 8w 500ms Ton, 500ms Toff
	p = &sGynecology[3];
	p->name = "Laser Vaginal Tightening 4th 600J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 500;
	p->negwidth = 500; 
	
	//1470nm, CW 6w 15s Ton
	p = &sGynecology[4];
	p->name ="Laser Vaginal Rejuvenation 360J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 60;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	//1470nm, CW 10w 15s Ton
	p = &sGynecology[5];
	p->name = "Laser Vaginal Rejuvenation+ 600J"; 
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 15000;
	p->negwidth = 1000; 	
	
	//1470nm, CW 5w
	p = &sGynecology[6];
	p->name = "Stress Incontinence, 75J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 50;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 
	
	//1470nm, CW 5w
	p = &sGynecology[7];
	p->name = "Infection control, 50J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 50;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	
	
	//1470nm, CW 8w
	p = &sGynecology[8];
	p->name = "Treatment after Menopause, 480J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000; 	

	//1470nm 12w CW
	p = &sGynecology[9];
	p->name = "Hysteroscopy Myomas";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 8w CW
	p = &sGynecology[10];
	p->name = "Hysteroscopy Polyps";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	//1470nm 10w CW
	p = &sGynecology[11];
	p->name = "Hysteroscopy Septum";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 10w CW
	p = &sGynecology[12];
	p->name = "Hysteroscopy Adhesion";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 12w CW
	p = &sGynecology[13];
	p->name = "Hysteroscopy Dysmorphic Uterus";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 12w CW
	p = &sGynecology[14];
	p->name = "Hysteroscopy Isthmocele";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 12w CW
	p = &sGynecology[15];
	p->name = "Hysteroscopy T-Shape Uterus";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;		
	
	//1470nm 12w CW
	p = &sGynecology[16];
	p->name = "Laparoscopy Myomas";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//1470nm 10w CW
	p = &sGynecology[17];
	p->name = "Laparoscopy Ovarian Cysts";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 10w CW
	p = &sGynecology[18];
	p->name = "Laparoscopy Adhesion";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 10w CW
	p = &sGynecology[19];
	p->name = "Laparoscopy Salpingectomy";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 10w CW
	p = &sGynecology[20];
	p->name = "Laparoscopy Cysts";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	//1470nm 10w CW
	p = &sGynecology[21];
	p->name = "Laparoscopy Endometriosis";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
/*****************************************************************************/
#if defined(MODEL_PVGLS_TRI_A0)
	//1470nm, Pulse 7w 1s Ton, 5s Toff
	p = &sNeurosurgery[0];
	p->name = "PLDD L2-L3, L3-L4, L5-S1 800-1500J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;

	//1470nm, Pulse 7w 1s Ton, 5s Toff
	p = &sNeurosurgery[1];
	p->name = "PLDD L4-L5 Total 800-1800J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
	//1470nm, Pulse 7w, 1s Ton, 5s Toff
	p = &sNeurosurgery[2];
	p->name = "PLDD 980nm";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 75;
	p->power_red = 1;
	p->poswidth = 700;
	p->negwidth = 700;		
	
	//1470nm, Pulse 7w, 1s Ton, 5s Toff
	p = &sNeurosurgery[3];
	p->name = "Tumour 1470nm";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;	
	
	//980m, Pulse 8w 1s Ton, 5s Toff
	p = &sNeurosurgery[4];
	p->name = "Tumour 980nm";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
//1470nm, Pulse 7w 1s Ton, 5s Toff
	p = &sNeurosurgery[0];
	p->name = "PLDD L2-L3, L3-L4, L5-S1 800-1500J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;

	//1470nm, Pulse 7w 1s Ton, 5s Toff
	p = &sNeurosurgery[1];
	p->name = "PLDD L4-L5 Total 800-1800J";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
	
	//1470nm, Pulse 7w, 1s Ton, 5s Toff
	p = &sNeurosurgery[2];
	p->name = "Tumour 1470nm";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 70;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;	
#endif
/*****************************************************************************/
	//ENT
	//980nm 13w CW
	p = &sENT[0];
	p->name = "Vocal Polyps";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//980nm 12w CW
	p = &sENT[1];
	p->name = "Cordectomy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 120;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 14w CW
	p = &sENT[2];
	p->name = "Laryngeal Carcinoma";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 140;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 14w CW
	p = &sENT[3];
	p->name = "Haematomas";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 140;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 14w CW
	p = &sENT[4];
	p->name = "Fibromas";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 140;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 14w CW
	p = &sENT[5];
	p->name = "Larynxpapillomatosis";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 140;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &sENT[6];
	p->name = "Paracentesis";		
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &sENT[7];
	p->name = "Acoustic Neuroma";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 10w CW
	p = &sENT[8];
	p->name = "Cholesteatoma";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &sENT[9];
	p->name = "Tonsillectomy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &sENT[10];
	p->name = "Tumour Vaporisation";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 10w CW
	p = &sENT[11];
	p->name = "Uvulopalatoplasty (LAUP)";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 13w CW
	p = &sENT[12];
	p->name = "Conchotomy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 130;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 10w Pulse, 50ms Ton, 90ms Toff 
	p = &sENT[13];
	p->name = "Dacryocystorhinostomy (DCR)";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 90;
	
	//980nm 10w CW
	p = &sENT[14];
	p->name = "Turbinate Reduction";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm 12w CW
	p = &sENT[15];
	p->name = "Nasal Polypectomy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 120;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
/*****************************************************************************/
	//Dermatology
	//980nm, CW 10W
	p = &sDermatology[0];
	p->name = "Cut";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm, CW 6w
	p = &sDermatology[1];
	p->name = "Coagulation";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 30;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	//980nm, CW 8w
	p = &sDermatology[2];
	p->name = "Moles Removal";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//980nm, CW 10w
	p = &sDermatology[3];
	p->name = "Warts Removal";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//980nm, Pulse, 6w, 1s Ton, 1s Toff
	p = &sDermatology[4];
	p->name = "Nail Fungus";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 60;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//980nm, Pulse, 6w, 1s Ton, 1s Toff
	p = &sDermatology[5];
	p->name = "Venectasia";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 150;
	p->power_red = 1;
	p->poswidth = 70;
	p->negwidth = 120;

	//980nm, Pulse, 8w, 1s Ton, 5s Toff
	p = &sDermatology[6];
	p->name = "Spider Vein 0.5mm";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
	//980nm, Pulse, 8w, 1s Ton, 5s Toff
	p = &sDermatology[7];
	p->name = "Spider Vein 1mm";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;

	//980nm, Pulse, 8w, 1s Ton, 5s Toff
	p = &sDermatology[8];
	p->name = "Spider Vein 1.5mm";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 5000;
	
/*****************************************************************************/
	//Liposuction
	//1470nm, 3w CW
	p = &sLiposuction[0];
	p->name =  "Liposuction Under Eye";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 30;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//1470nm 6w CW	
	p = &sLiposuction[1];
	p->name = "Liposuction Chin";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 60;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 8w CW
	p = &sLiposuction[2];
	p->name = "Liposuction Arm";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 12 CW
	p = &sLiposuction[3];
	p->name = "Liposuction Abdomen";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 120;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 10w CW
	p = &sLiposuction[4];
	p->name = "Liposuction Buttock";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 100;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	//1470nm 8w CW
	p = &sLiposuction[5];
	p->name = "Liposuction Thigh";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
		
	//1470nm 8w CW	
	p = &sLiposuction[6];
	p->name = "Gynecomastia";
	p->channel = LASER_CHANNEL_CH0;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 80;
	p->power_ch1 = 1;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
/*****************************************************************************/
	//DENTISTRY
	//
	p = &sDentistry[0];
	p->name = "Incision & Drainage Of Abscess";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 12;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[1];
	p->name = "Excision & Incisional Biopsy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[2];
	p->name = "Aphthous Ulcer & herpetic";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 20;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;	
	
	p = &sDentistry[3];
	p->name = "Pulpotomy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 15;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;	
	
	p = &sDentistry[4];
	p->name = "Expose of unerupted teeth";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[5];
	p->name = "Fibroma Removal";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[6];
	p->name = "Frenectomy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[7];
	p->name = "Gingivectomy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[8];
	p->name = "Gingivoplasty";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[9];
	p->name = "Gingival incision & excision Hemostasis";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[10];
	p->name = "Crown Lengthening";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 18;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;	
	
	p = &sDentistry[11];
	p->name = "Reduction of Gingival Hypertrophy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 15;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[12];
	p->name = "Implant Recovery";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;	
	
	p = &sDentistry[13];
	p->name = "Hemostasis and Coagulation";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 12;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	p = &sDentistry[14];
	p->name = "Gingival Troughing";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 18;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[15];
	p->name = "Operculectomy";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 15;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[16];
	p->name = "Infected Pockets Removal";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 18;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[17];
	p->name = "Gingival Bleeding Index";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 8;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	p = &sDentistry[18];
	p->name = "Sulcular Debridement";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 8;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[19];
	p->name = "Leukoplakia";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	p = &sDentistry[20];
	p->name = "Vestibuloplasty";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 10;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;
	
	p = &sDentistry[21];
	p->name = "Oral Papilectomies";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 9;
	p->power_red = 1;
	p->poswidth = 1000;
	p->negwidth = 1000;

	p = &sDentistry[22];
	p->name = "Tooth Whitening";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 50;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;

/*****************************************************************************/
#if defined(MODEL_PVGLS_TRI_A0)
	//Therapy
	//980nm 8w pulse, 50ms on, 50ms off
	p = &sTherapy[0];
	p->name = "Orthopedic Pain";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;
	
	//980nm 8w pulse 50ms on, 50ms off
	p = &sTherapy[1];
	p->name = "Spine Pain";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 80;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;

	//980nm 10w pulse 50ms on, 50ms off
	p = &sTherapy[2];
	p->name = "Frozen Shoulder";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 100;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;

//980nm 6w pulse 50ms on, 50ms off
	p = &sTherapy[3];
	p->name = "Fasciitis";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 60;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;
	
//980nm 6w pulse 50ms on, 50ms off
	p = &sTherapy[4];
	p->name = "Pain Management";
	p->channel = LASER_CHANNEL_CH1;
	p->pulse_mode = LASER_MODE_MP; 
	p->power_ch0 = 1;
	p->power_ch1 = 60;
	p->power_red = 1;
	p->poswidth = 50;
	p->negwidth = 50;

//635nm CW
	p = &sTherapy[5];
	p->name = "Wound Healing";
	p->channel = LASER_CHANNEL_RED;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 1;
	p->power_red = 5;
	p->poswidth = 1000;
	p->negwidth = 1000;

//635nm CW
	p = &sTherapy[6];
	p->name = "Low Laser Therapy";
	p->channel = LASER_CHANNEL_RED;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 1;
	p->power_red = 5;
	p->poswidth = 1000;
	p->negwidth = 1000;

//635nm CW
	p = &sTherapy[7];
	p->name = "Biostimulation";
	p->channel = LASER_CHANNEL_RED;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 1;
	p->power_red = 5;
	p->poswidth = 1000;
	p->negwidth = 1000;
#endif
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
	//Therapy
	//635nm CW
	p = &sTherapy[0];
	p->name = "Wound Healing";
	p->channel = LASER_CHANNEL_RED;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 1;
	p->power_red = 5;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//635nm CW
	p = &sTherapy[1];
	p->name = "Low Laser Therapy";
	p->channel = LASER_CHANNEL_RED;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 1;
	p->power_red = 5;
	p->poswidth = 1000;
	p->negwidth = 1000;

	//635nm CW
	p = &sTherapy[2];
	p->name = "Biostimulation";
	p->channel = LASER_CHANNEL_RED;
	p->pulse_mode = LASER_MODE_CW; 
	p->power_ch0 = 1;
	p->power_ch1 = 1;
	p->power_red = 5;
	p->poswidth = 1000;
	p->negwidth = 1000;

#endif

}

#endif


#if defined(MODEL_PVGLS_10W_1940_A1)

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

