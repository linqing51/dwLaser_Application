#include "sPlcMisc.h"
/*****************************************************************************/
void setRedLed(uint8_t st){
	if(st){
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
	}
}
void setGreenLed(uint8_t st){
	if(st){
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	}
}
void setBlueLed(uint8_t st){
	if(st){
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
	}	
}
void setBeem(uint8_t st){//���÷�����״̬
	
}
void setAim(uint8_t st){//������׼��״̬
}
void setAimBright(uint16_t br){//������׼������
}

void initWatchDog(void){//���Ź���ʼ��
	
}
void enableWatchDog(void){//ʹ�ܿ��Ź�

}
void disableWatchDog(void){//�رտ��Ź�(δ����)
	
}
void feedWatchDog(void) {//ι��

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

