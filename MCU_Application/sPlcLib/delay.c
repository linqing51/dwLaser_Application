#include "delay.h"
/*****************************************************************************/
void delayUs(uint16_t us) reentrant{//΢����ʱ
	while(us){
#if CONFIG_SPLC_USING_WDT == 1
		NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
        NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
		feedWatchDog();
#else
		NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();	
#endif
		us --;	
	}
}
void delayMs(uint16_t ms) reentrant{//������ʱ
	while(ms--){
		delayUs(1000);
		feedWatchDog();
	}
}


