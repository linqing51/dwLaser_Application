#ifndef __PRESCHEME_H__
#define __PRESCHEME_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
typedef struct{
	char const *name;//治疗名字
	int16_t channel;//激光通道选择
	int16_t pulse_mode;//脉冲模式
	int16_t power_1480;//功率 1470
	int16_t power_980;//功率 980
	int16_t power_635;//功率 635
	int16_t poswidth;
	int16_t negwidth;
}myScheme_t;



char const Phlebology_0[] 							= "EVLA Thigh";
char const Phlebology_1[] 							= "EVLA calf";
char const Phlebology_2[] 							= "EVLA Small Vessel";

char const Proctology_0[] 							= "Hemorrhoids Grade 2, 250J";
char const Proctology_1[] 							= "Hemorrhoids Grade 3, 350J";
char const Proctology_2[]								= "Hemorrhoids Grade 4, 350J";
char const Proctology_3[]								= "Fistula";
char const Proctology_4[]								= "Pilonidal Sinus";
char const Proctology_5[]								= "Fissure Ablation";

char const CosmoGynecology_0[]  				= "Laser Vaginal Tightening 1st 600J";
char const CosmoGynecology_1[] 					= "Laser Vaginal Tightening 2nd 600J";
char const CosmoGynecology_2[] 					= "Laser Vaginal Tightening 3rd 600J";
char const CosmoGynecology_3[] 					= "Laser Vaginal Tightening 4th 600J";
char const CosmoGynecology_4[] 					= "Laser Vaginal Rejuvenation 360J";
char const CosmoGynecology_5[] 					= "Laser Vaginal Rejuvenation+ 600J"; 
char const CosmoGynecology_6[] 					= "Stress Incontinence, 75J";
char const CosmoGynecology_7[] 					= "Infection control, 50J";
char const CosmoGynecology_8[] 					= "Treatment after Menopause, 480J";

char const GynecologyHysteroscopy_0[] 	= "Myomas";
char const GynecologyHysteroscopy_1[] 	= "Polyps";
char const GynecologyHysteroscopy_2[]		= "Septum";
char const GynecologyHysteroscopy_3[]		= "Adhesion";
char const GynecologyHysteroscopy_4[]		= "Dysmorphie Uterus";
char const GynecologyHysteroscopy_5[]		= "Isthmocele";
char const GynecologyHysteroscopy_6[]		= "T-Shape Uterus";

char const GynecologyLaparoscopy_0[]		= "Myomas";
char const GynecologyLaparoscopy_1[]		= "Ovarian Cysts";
char const GynecologyLaparoscopy_2[]		= "Adhesion";
char const GynecologyLaparoscopy_3[]		= "Salpingectomy";
char const GynecologyLaparoscopy_4[]		= "Cysts";
char const GynecologyLaparoscopy_5[]		= "Endometriosis";

char const Neurosurgery_0[] 						= "PLDD L2-L3, L3-L4, L5-S1 800-1500J";
char const Neurosurgery_1[] 						= "PLDD L4-L5 Total 800-1800J";
char const Neurosurgery_2[]							=	"Tumour";
char const Neurosurgery_3[]							=	"Tumour";

char const ENT_0[] 											= "Vocal Polyps";
char const ENT_1[] 											= "Cordectomy";
char const ENT_2[] 											= "Laryngeal Carcinoma";
char const ENT_3[] 											= "Haematomas";
char const ENT_4[] 											= "Fibromas";
char const ENT_5[] 											= "Larynxpapillomatosis";
char const ENT_6[] 											= "Paracentesis";					
char const ENT_7[]											= "Acoustic Neuroma";
char const ENT_8[]											= "Cholesteatoma";
char const ENT_9[]											= "Tonsillectomy";
char const ENT_10[]											= "Tumour Vaporisation";
char const ENT_11[]											= "Uvulopalatoplasty (LAUP)";
char const ENT_12[]											= "Conchotomy";
char const ENT_13[]											= "Dacryocystorhinostomy (DCR)";
char const ENT_14[]											= "Turbinate Reduction";
char const ENT_15[]											= "Nasal Polypectomy";

char const Dermatology_0[]							= "Cut";
char const Dermatology_1[]							= "Coagulation";
char const Dermatology_2[]							= "Moles Removal";
char const Dermatology_3[]							= "Warts Removal";
char const Dermatology_4[]							= "Nail Fungus";
char const Dermatology_5[]							= "Spider Vein 0.5mm";
char const Dermatology_6[] 							= "Spider Vein 1mm";
char const Dermatology_7[]							= "Spider Vein 1.5mm";

char const Liposuction_0[] 							= "Liposuction Under Eye";
char const Liposuction_1[] 							= "Liposuction Chin";
char const Liposuction_2[] 							= "Liposuction Arm";
char const Liposuction_3[] 							= "Liposuction Abdomen";
char const Liposuction_4[] 							= "Liposuction Buttock";
char const Liposuction_5[] 							= "Liposuction Thigh";

char const Gynecomastia_0[] 						= "Therapy";
char const Gynecomastia_1[] 						= "Orthopedie Pain";
char const Gynecomastia_2[] 						= "Spine Pain";
char const Gynecomastia_3[] 						= "Frozen Shoulder";
char const Gynecomastia_4[] 						= "Plantar Facilities";
char const Gynecomastia_5[] 						= "Pain Management";
char const Gynecomastia_6[] 						= "Would Healing";
char const Gynecomastia_7[] 						= "Low Laser Therapy";
char const Gynecomastia_8[] 						= "Biostimulation";



#define Phlebology_Size										3
#define Proctology_Size										6
#define CosmoGynecology_Size	   					9
#define GynecologyHysteroscopy_Size				7
#define GynecologyLaparoscopy_Size				6
#define Neurosurgery_Size									4
#define ENT_Size 													16
#define Dermatology_Size									8
#define Liposuction_Size									6
#define Gynecomastia_Size									9
#define Custom_Size												16

myScheme_t schemePhlebology[Phlebology_Size];
myScheme_t schemeProctology[Proctology_Size];
myScheme_t schemeCosmoGynecology[CosmoGynecology_Size];
myScheme_t schemeGynecologyHysteroscopy[GynecologyHysteroscopy_Size];
myScheme_t schemeGynecologyLaparoscopy[GynecologyLaparoscopy_Size];
myScheme_t schemeNeurosurgery[Neurosurgery_Size];
myScheme_t schemeENT[ENT_Size];
myScheme_t schemeDermatology[Dermatology_Size];
myScheme_t schemeLiposuction[Liposuction_Size];
myScheme_t schemeGynecomastia[Gynecomastia_Size];
myScheme_t schemeCustom[Custom_Size];



#endif


