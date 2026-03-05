#include "MainApp.h"
/*****************************************************************************/
void StartMainAppTask(void *argument){
	sPlcInit();
	while(1){
		sPlcProcessStart();
		if(LD(SPCOIL_START_UP)){//
			dcHmiLoopInit();
		}
		dcHmiLoop();
		sPlcProcessEnd();
		hmiUartErrorReset();
	}
}



