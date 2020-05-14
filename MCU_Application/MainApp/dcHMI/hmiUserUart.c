/*****************************************************************************/
#include "hmiUserUart.h"
/*****************************************************************************/
void hmiUartSendChar(uint8_t t){//UART1����
	uint8_t SFRPAGE_SAVE = SFRPAGE;        // Save Current SFR page
	SFRPAGE = UART0_PAGE;
	TI0 = 0;
	SBUF0 = t;
	feedWatchDog();
    while(!TI0);
	TI0 = 0;//TI1 = 0
	SFRPAGE = SFRPAGE_SAVE;             // Restore SFR page   
} 

#if CONFIG_SPLC_USING_UART0 == 1
void Uart0Isr(void) interrupt INTERRUPT_UART0 {//UART1�ж�
	if(RI0){
        RI0 = 0;  
		queue_push(SBUF0);//ѹ�뵽ָ�����
	}
}
#endif