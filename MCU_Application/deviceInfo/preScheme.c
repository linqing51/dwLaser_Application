#include "preScheme.h"
/*****************************************************************************/
#if CONFIG_APP_LONGNAME_SCHEME == 1
char const PRE_SCHEME_TABLE[16][CONFIG_MAX_SCHEME_NAME_SIZE]  = 
									   {{"EVLA Thigh"},
										{"EVLA calf"},
										{"EVLA Small Vessel"},
										{"Hemorrhoids Grade 2 250 Joules per hemorrhoid"},
										{"Hemorrhoids Grade 3 350 Joules per hemorrhoid"},
										{"Hemorrhoids Grade 4 350 Joules per hemorrhoid"},
										{"Fistula"},
										{"Pilonidal Sinus"},
										{"Fissure Abaltion"},
										{"PLDD L2-L3, L3-L4, L5-S1 Total 800-1500J"},
										{"PLDD L4-L5 Total 800-1800J"},
										{"NULL"},
										{"NULL"},
										{"NULL"},
										{"NULL"},
										{"NULL"}};
#endif
#if CONFIG_APP_SHORTNAME_SCHEME == 1								
char const *PRE_SCHEME_TABLE_S0  = "EVLA Thigh";
char const *PRE_SCHEME_TABLE_S1  = "EVLA calf";
char const *PRE_SCHEME_TABLE_S2	 = "EVLA Small Vessel";
char const *PRE_SCHEME_TABLE_S3	 = "Hemorrhoids Grade 2 250J";
char const *PRE_SCHEME_TABLE_S4  = "Hemorrhoids Grade 3 350J";
char const *PRE_SCHEME_TABLE_S5	 = "Hemorrhoids Grade 4 350J";
char const *PRE_SCHEME_TABLE_S6	 = "Fistula";
char const *PRE_SCHEME_TABLE_S7	 = "Pilonidal Sinus";
char const *PRE_SCHEME_TABLE_S8	 = "Fissure Abaltio";
char const *PRE_SCHEME_TABLE_S9	 = "PLDD Total 800-1800J";
char const *PRE_SCHEME_TABLE_S10 = "PLDD L4-L5 Total 800-1800J";
#endif
										
////


										