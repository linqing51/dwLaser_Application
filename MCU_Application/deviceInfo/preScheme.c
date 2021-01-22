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
char const PRE_SCHEME_TABLE[16][CONFIG_MAX_SCHEME_NAME_SIZE]  = 
									   {{"EVLA Thigh"},
										{"EVLA calf"},
										{"EVLA Small Vessel"},
										{"Hemorrhoids Grade 2 250J"},
										{"Hemorrhoids Grade 3 350J"},
										{"Hemorrhoids Grade 4 350J"},
										{"Fistula"},
										{"Pilonidal Sinus"},
										{"Fissure Abaltion"},
										{"PLDD Total 800-1800J"},
										{"PLDD L4-L5 Total 800-1800J"},
										{"NULL"},
										{"NULL"},
										{"NULL"},
										{"NULL"},
										{"NULL"}};
#endif
										
////


										