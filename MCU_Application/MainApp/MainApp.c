#include "MainApp.h"
/*****************************************************************************/
void mainAppTask(void *argument){
	sPlcInit();
	while(1){
		sPlcProcessStart();
		//if(LD(SPCOIL_START_UP)){//
			
		//}

		sPlcProcessEnd();
	}
}




