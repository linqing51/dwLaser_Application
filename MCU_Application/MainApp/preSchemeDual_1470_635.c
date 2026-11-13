/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
//预设方案内容
#include "preScheme.h"
/*****************************************************************************/
#if defined(APP_CONFIG_WAVE_1470_635)
/*****************************************************************************/
//预设方案固化在 Flash(只读): 运行期不回存, 每次上电直接使用以下常量。
//未显式列出的字段由 C 初始化规则自动置 0, 与原 .bss 零初始化后再部分赋值的结果一致。
const myScheme_t sPhlebology[32] = {//0
	//1470nm, CW 8w 80J/cm
	{.name="EVLA Thigh", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=80, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm, CW 6w 60J/cm
	{.name="EVLA calf", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=60, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm, CW 3w 30J/cm
	{.name="EVLA Small Vessel", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=30, .power_ch2=1, .poswidth=1000, .negwidth=1000},
};
const myScheme_t sProctology[32] = {//1
	//1470nm, CW 6w, 250 Joules per hemorrhoid
	{.name="Hemorrhoids Grade 2, 250J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=70, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm, CW 7w, 350 Joules per hemorrhoid
	{.name="Hemorrhoids Grade 3, 350J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=80, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm, CW 8w, 350 Joules per hemorrhoid
	{.name="Hemorrhoids Grade 4, 350J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=80, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm, CW 10w 100J/cm
	{.name="Fistula", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=120, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm, CW 10w 100J/cm
	{.name="Pilonidal Sinus", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=120, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm, CW 7w 100J/cm
	{.name="Fissure Ablation", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=70, .power_ch2=1, .poswidth=1000, .negwidth=1000},
};
const myScheme_t sGynecology[32] = {//2
	//1470nm, Pulse 6w 500ms Ton, 500ms Toff
	{.name="Laser Vaginal Tightening 1st 600J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=60, .power_ch2=1, .poswidth=500, .negwidth=500},
	//1470nm, Pulse 7w 500ms Ton, 500ms Toff
	{.name="Laser Vaginal Tightening 2nd 600J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=70, .power_ch2=1, .poswidth=500, .negwidth=500},
	//1470nm, Pulse 8w 500ms Ton, 500ms Toff
	{.name="Laser Vaginal Tightening 3rd 600J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=80, .power_ch2=1, .poswidth=500, .negwidth=500},
	//1470nm, Pulse 8w 500ms Ton, 500ms Toff
	{.name="Laser Vaginal Tightening 4th 600J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=80, .power_ch2=1, .poswidth=500, .negwidth=500},
	//1470nm, CW 6w 15s Ton
	{.name="Laser Vaginal Rejuvenation 360J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=60, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm, CW 10w 15s Ton
	{.name="Laser Vaginal Rejuvenation+ 600J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=100, .power_ch2=1, .poswidth=15000, .negwidth=1000},
	//1470nm, CW 5w
	{.name="Stress Urinary Incontinence,75J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=50, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 10w CW
	{.name="LVR/SUI Pro @ 4 Passes / 2400J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP,
#if defined( MODLE_M1470_640_10_30_05_D200_22_G9_PK)
	 .power_ch0=170,
#else
	 .power_ch0=150,
#endif
	 .poswidth=50, .negwidth=150},
	//1470nm, CW 5w
	{.name="Infection control, 50J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=50, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm, CW 8w
	{.name="Treatment after Menopause, 480J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=80, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 12w CW
	{.name="Hysteroscopy Myomas", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=120, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 8w CW
	{.name="Hysteroscopy Polyps", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=80, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 10w CW
	{.name="Hysteroscopy Septum", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=100, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 10w CW
	{.name="Hysteroscopy Adhesion", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=100, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 12w CW
	{.name="Hysteroscopy Dysmorphic Uterus", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=120, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 12w CW
	{.name="Hysteroscopy Isthmocele", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=120, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 12w CW
	{.name="Hysteroscopy T-Shape Uterus", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=120, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 12w CW
	{.name="Laparoscopy Myomas", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=120, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 10w CW
	{.name="Laparoscopy Ovarian Cysts", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=100, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 10w CW
	{.name="Laparoscopy Adhesion", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=100, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 10w CW
	{.name="Laparoscopy Salpingectomy", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=100, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 10w CW
	{.name="Laparoscopy Cysts", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=100, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 10w CW
	{.name="Laparoscopy Endometriosis", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=100, .power_ch2=1, .poswidth=1000, .negwidth=1000},
};
const myScheme_t sENT[32] = {0};//3 当前配置无预设方案, 保留符号供 UI 空科室分支索引
const myScheme_t sNeurosurgery[32] = {//4
	//1470nm, Pulse 7w 1s Ton, 5s Toff
	{.name="PLDD L2-L3, L3-L4, L5-S1 800-1500J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=70, .power_ch2=1, .poswidth=1000, .negwidth=5000},
	//1470nm, Pulse 7w 1s Ton, 5s Toff
	{.name="PLDD L4-L5 Total 800-1800J", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=70, .power_ch2=1, .poswidth=1000, .negwidth=5000},
	//1470nm, Pulse 7w, 1s Ton, 5s Toff
	{.name="Tumour 1470nm", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=70, .power_ch2=1, .poswidth=1000, .negwidth=5000},
};
const myScheme_t sDermatology[32] = {0};//5 当前配置无预设方案
const myScheme_t sLiposuction[32] = {//6
	//1470nm, 3w CW
	{.name="Liposuction Under Eye", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=30, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 6w CW
	{.name="Liposuction Chin", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=60, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 8w CW
	{.name="Liposuction Arm", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=80, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 12 CW
	{.name="Liposuction Abdomen", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=120, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 10w CW
	{.name="Liposuction Buttock", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=100, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 8w CW
	{.name="Liposuction Thigh", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=80, .power_ch2=1, .poswidth=1000, .negwidth=1000},
	//1470nm 8w CW
	{.name="Gynecomastia", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_CW, .power_ch0=80, .power_ch2=1, .poswidth=1000, .negwidth=1000},
};
const myScheme_t sDentistry[32] = {0};//7 当前配置无预设方案
const myScheme_t sTherapy[32] = {//8
	//635nm CW
	{.name="Wound Healing", .channel=LASER_CHANNEL_CH2, .pulse_mode=LASER_MODE_CW, .power_ch0=1, .power_ch2=5, .poswidth=1000, .negwidth=1000},
	//635nm CW
	{.name="Low Laser Therapy", .channel=LASER_CHANNEL_CH2, .pulse_mode=LASER_MODE_CW, .power_ch0=1, .power_ch2=5, .poswidth=1000, .negwidth=1000},
	//635nm CW
	{.name="Biostimulation", .channel=LASER_CHANNEL_CH2, .pulse_mode=LASER_MODE_CW, .power_ch0=1, .power_ch2=5, .poswidth=1000, .negwidth=1000},
};
const myScheme_t sEndolift[32] = {//11
	{.name="Face Lower eyelids", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=6, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Face Cheeks", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=15, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Face Mandib bord", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=13, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Face Under chin", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=15, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Face Neck", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=15, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Body Arms", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=30, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Body Abdomen", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=30, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Body Sides", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=30, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Body Trochanter", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=30, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Body Inside led", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=30, .power_ch2=1, .poswidth=50, .negwidth=50},
	{.name="Body Anckle", .channel=LASER_CHANNEL_CH0, .pulse_mode=LASER_MODE_MP, .power_ch0=30, .power_ch2=1, .poswidth=50, .negwidth=50},
};
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
		case SCHEME_ENDOLIFT:{
			if(NVRAM0[DM_SCHEME_INDEX] < (CONFIG_ENDOLIFT_SIZE - 1)){
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
	int16_t tmp16;
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
      NVRAM0[EM_LASER_POWER_CH2] = sPhlebology[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sPhlebology[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sPhlebology[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sPhlebology[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sPhlebology[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sPhlebology[index].power_ch7;
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
      NVRAM0[EM_LASER_POWER_CH2] = sProctology[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sProctology[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sProctology[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sProctology[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sProctology[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sProctology[index].power_ch7;
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
      NVRAM0[EM_LASER_POWER_CH2] = sGynecology[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sGynecology[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sGynecology[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sGynecology[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sGynecology[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sGynecology[index].power_ch7;
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
      NVRAM0[EM_LASER_POWER_CH2] = sENT[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sENT[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sENT[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sENT[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sENT[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sENT[index].power_ch7;
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
      NVRAM0[EM_LASER_POWER_CH2] = sNeurosurgery[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sNeurosurgery[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sNeurosurgery[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sNeurosurgery[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sNeurosurgery[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sNeurosurgery[index].power_ch7;
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
      NVRAM0[EM_LASER_POWER_CH2] = sDermatology[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sDermatology[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sDermatology[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sDermatology[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sDermatology[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sDermatology[index].power_ch7;
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
      NVRAM0[EM_LASER_POWER_CH2] = sLiposuction[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sLiposuction[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sLiposuction[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sLiposuction[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sLiposuction[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sLiposuction[index].power_ch7;
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
      NVRAM0[EM_LASER_POWER_CH2] = sDentistry[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sDentistry[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sDentistry[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sDentistry[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sDentistry[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sDentistry[index].power_ch7;
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
      NVRAM0[EM_LASER_POWER_CH2] = sTherapy[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sTherapy[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sTherapy[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sTherapy[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sTherapy[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sTherapy[index].power_ch7;
			NVRAM0[EM_LASER_POSWIDTH] = sTherapy[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sTherapy[index].negwidth;			
			break;
		}
		case SCHEME_ENDOLIFT:{
			if(index > (CONFIG_ENDOLIFT_SIZE - 1)){
				index = (CONFIG_ENDOLIFT_SIZE - 1);
			}
			strcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(sEndolift[index].name));
			NVRAM0[EM_LASER_CHANNEL_SELECT] = sEndolift[index].channel;
			NVRAM0[EM_LASER_PULSE_MODE] = sEndolift[index].pulse_mode;
			NVRAM0[EM_LASER_POWER_CH0] = sEndolift[index].power_ch0;
			NVRAM0[EM_LASER_POWER_CH1] = sEndolift[index].power_ch1;
      NVRAM0[EM_LASER_POWER_CH2] = sEndolift[index].power_ch2;
      NVRAM0[EM_LASER_POWER_CH3] = sEndolift[index].power_ch3;
			NVRAM0[EM_LASER_POWER_CH4] = sEndolift[index].power_ch4;
      NVRAM0[EM_LASER_POWER_CH5] = sEndolift[index].power_ch5;
      NVRAM0[EM_LASER_POWER_CH6] = sEndolift[index].power_ch6;
      NVRAM0[EM_LASER_POWER_CH7] = sEndolift[index].power_ch7;
			NVRAM0[EM_LASER_POSWIDTH] = sEndolift[index].poswidth;
			NVRAM0[EM_LASER_NEGWIDTH] = sEndolift[index].negwidth;					
			break;
		}
		case SCHEME_CUSTIOM:{
			if(index > (CONFIG_CUSTIOM_SIZE - 1)){
				index = (CONFIG_CUSTIOM_SIZE - 1);
			}		
			tmp16 = ((EM_LASER_CHANNEL_SELECT - EM_LASER_SCHEME_NAME + 1) * 2);  
			memcpy((char*)(&NVRAM0[EM_LASER_SCHEME_NAME]), (char*)(&FDRAM0[index * 64 + FD_LASER_SCHEME_NAME]) , tmp16);
			NVRAM0[EM_LASER_CHANNEL_SELECT] = FDRAM0[index * 64 + FD_LASER_CHANNEL_SELECT];
			NVRAM0[EM_LASER_PULSE_MODE] = FDRAM0[index * 64 + FD_LASER_PULSE_MODE];
			NVRAM0[EM_LASER_POWER_CH0] = FDRAM0[index * 64 + FD_LASER_POWER_CH0];
			NVRAM0[EM_LASER_POWER_CH1] = FDRAM0[index * 64 + FD_LASER_POWER_CH1];
      NVRAM0[EM_LASER_POWER_CH2] = FDRAM0[index * 64 + FD_LASER_POWER_CH2];
			NVRAM0[EM_LASER_POWER_CH3] = FDRAM0[index * 64 + FD_LASER_POWER_CH3];
      NVRAM0[EM_LASER_POWER_CH4] = FDRAM0[index * 64 + FD_LASER_POWER_CH4];
			NVRAM0[EM_LASER_POWER_CH5] = FDRAM0[index * 64 + FD_LASER_POWER_CH5];
      NVRAM0[EM_LASER_POWER_CH6] = FDRAM0[index * 64 + FD_LASER_POWER_CH6];
			NVRAM0[EM_LASER_POWER_CH7] = FDRAM0[index * 64 + FD_LASER_POWER_CH7];
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
	printf("%s,%d,%s:scheme power ch0:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH0]);
	printf("%s,%d,%s:scheme power ch1:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH1]);
	printf("%s,%d,%s:scheme power ch2:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH2]);
  printf("%s,%d,%s:scheme power ch3:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH3]);
	printf("%s,%d,%s:scheme power ch4:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH4]);
	printf("%s,%d,%s:scheme power ch5:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH5]);
  printf("%s,%d,%s:scheme power ch6:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH6]);
	printf("%s,%d,%s:scheme power ch7:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_CH7]);
	printf("%s,%d,%s:scheme power 635:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POWER_635]);
	printf("%s,%d,%s:scheme poswidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_POSWIDTH]);
	printf("%s,%d,%s:scheme negwidth:%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_LASER_NEGWIDTH]);
}

void restoreScheme(uint8_t reDef){//治疗方案初始化FDRAM
	int16_t i;
	for (i = 0;i < 32; i ++){
		if(reDef == 1){//自定义方案恢复默认值
			sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "Custom %d", (i+1)); 
			FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
			FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
			FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 1;
			FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
			FDRAM0[FD_LASER_POWER_CH2 + (i * 64)] = 1;
			FDRAM0[FD_LASER_POWER_CH3 + (i * 64)] = 1;
			FDRAM0[FD_LASER_POWER_CH4 + (i * 64)] = 1;
			FDRAM0[FD_LASER_POWER_CH5 + (i * 64)] = 1;
			FDRAM0[FD_LASER_POWER_CH6 + (i * 64)] = 1;
			FDRAM0[FD_LASER_POWER_CH7 + (i * 64)] = 1;
			FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
			FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
			FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;	
		}
		else{
			if(	(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_CH0) &&\
					(FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] != LASER_CHANNEL_CH1)){//自定义方案不正确恢复默认值
				sprintf(((char*)&FDRAM0[FD_LASER_SCHEME_NAME + (i * 64)]), "Custom %d", (i+1)); 
				FDRAM0[FD_LASER_CHANNEL_SELECT + (i * 64)] = LASER_CHANNEL_CH0;
				FDRAM0[FD_LASER_PULSE_MODE + (i * 64)] = LASER_MODE_CW;
				FDRAM0[FD_LASER_POWER_CH0 + (i * 64)] = 1;
				FDRAM0[FD_LASER_POWER_CH1 + (i * 64)] = 1;
				FDRAM0[FD_LASER_POWER_CH2 + (i * 64)] = 1;
				FDRAM0[FD_LASER_POWER_CH3 + (i * 64)] = 1;
				FDRAM0[FD_LASER_POWER_CH4 + (i * 64)] = 1;
				FDRAM0[FD_LASER_POWER_CH5 + (i * 64)] = 1;
				FDRAM0[FD_LASER_POWER_CH6 + (i * 64)] = 1;
				FDRAM0[FD_LASER_POWER_CH7 + (i * 64)] = 1;   
        FDRAM0[FD_LASER_POWER_RED + (i * 64)] = 1;
				FDRAM0[FD_LASER_POSWIDTH + (i * 64)] = 1000;
				FDRAM0[FD_LASER_NEGWIDTH + (i * 64)] = 1000;		
			}
		}
	}
	//预设方案已固化为 Flash 常量(见文件顶部), 这里仅恢复 FDRAM 自定义方案, 随后强制写回。
	FDSAV();//FDRAM恢复后强制写回EPROM
}

#endif



