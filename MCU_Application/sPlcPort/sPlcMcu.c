#include "sPlcMcu.h"
/*****************************************************************************/
static data uint8_t sPlcInterrupt;
/*****************************************************************************/
void initWatchDog(void){//���Ź���ʼ��
	
}
void enableWatchDog(void){//ʹ�ܿ��Ź�
#if CONFIG_SPLC_USING_WDT == 1
	
#endif
}
void disableWatchDog(void){//�رտ��Ź�(δ����)
	
}
void feedWatchDog(void) {//ι��
#if CONFIG_SPLC_USING_WDT == 1
	
#endif
}
void mucReboot(void)  {//��λ
	
}
void enterSplcIsr(void) {//SPLC �����ж�
	
}
void exitSplcIsr(void) {//SPLC �˳��ж�
	
}
void disableSplcIsr(void) {//SPLC�ر�ȫ���ж�
	
}
void enableSplcIsr(void) {//SPLC��ȫ���ж�
	
}
void disalbeModbusSerialIsr(void){
	
}
void enableModbusSerialIsr(void){
	
}



