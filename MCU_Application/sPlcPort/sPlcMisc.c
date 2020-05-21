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
void setBeem(uint8_t st){//设置蜂鸣器状态
	
}
void setAim(uint8_t st){//设置瞄准光状态
}
void setAimBright(uint16_t br){//设置瞄准光亮度
}

void initWatchDog(void){//看门狗初始化
	
}
void enableWatchDog(void){//使能看门狗

}
void disableWatchDog(void){//关闭看门狗(未锁定)
	
}
void feedWatchDog(void) {//喂狗

}
void mucReboot(void)  {//复位
	
}
void enterSplcIsr(void) {//SPLC 进入中断
	
}
void exitSplcIsr(void) {//SPLC 退出中断
	
}
void disableSplcIsr(void) {//SPLC关闭全局中断
	
}
void enableSplcIsr(void) {//SPLC打开全局中断
	
}
void disalbeModbusSerialIsr(void){
	
}
void enableModbusSerialIsr(void){
	
}

