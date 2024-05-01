#include "sPlc.h"
/*****************************************************************************/
int8_t inputFilter[(X_END - X_START + 1) * 16];//IO�����˲���������
/*****************************************************************************/
void sPlcInputInit(void){//IO�����˲�����ʼ��
	memset((uint8_t*)inputFilter, 0x0, ((X_END - X_START + 1) * 16));
	printf("%s,%d,%s:input init......\n",__FILE__, __LINE__, __func__);
}
void sPlcInputRefresh(void){//��ȡ����IO
	uint8_t	temp;
	//X0 ��ͣ
	temp = GET_ESTOP_NC;
	if(temp == 0){//��ͣ����
		if(inputFilter[0] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[0] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 0);
		}
	}
	else{//��ͣ����
		if(inputFilter[0] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[0] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 0);
		}
	}
	//X1 ��ȫ����
	temp = GET_INTERLOCK_NC;
	if(temp == 0){
		if(inputFilter[1] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[1] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 1);
		}
	}
	else{
		if(inputFilter[1] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[1] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 1);
		}
	}
	//X2 ��̤����
	temp = GET_FSWITCH_NO;//��ȡ������̤����״̬
	if(temp == 0){
		if(inputFilter[2] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[2] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 2);
		}
	}
	else{
		if(inputFilter[2] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[2] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 2);
		}
	}
	//X3 ��̤����
	temp = GET_FSWITCH_NC;
	if(temp == 0){
		if(inputFilter[3] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[3] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 3);
		}
	}
	else{
		if(inputFilter[3] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[3] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 3);
		}
	}
	//X4 ����̽��
	if(NVRAM0[SPREG_ADC_2] <= deviceConfig.fiberDetect){
		if(inputFilter[4] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[4] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 4);
		}
	}
	else{
		if(inputFilter[4] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[4] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 4);
		}
	}	
}

