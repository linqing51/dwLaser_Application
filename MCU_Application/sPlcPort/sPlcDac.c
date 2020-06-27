#include "sPlcDac.h"
/*****************************************************************************/
static void setSYNC(uint8_t dat){//PC13
	if(dat){
		HAL_GPIO_WritePin(DA_SYNC_GPIO_Port, DA_SYNC_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(DA_SYNC_GPIO_Port, DA_SYNC_Pin, GPIO_PIN_RESET);
	}
}
static void setCLK(uint8_t dat){//PC15
	if(dat){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
	}
}
static void setDIN(uint8_t dat){//PC14
	if(dat){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
	}
}
static void spiWrite(uint32_t dat){//DAC8568 SPI写入
	uint8_t tmp, i;
	setSYNC(true);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	setCLK(true);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	setSYNC(false);
	for(i = 0;i < 32;i ++){
		tmp = (uint8_t)(dat >> (31 - i)) & 0x01;
		setDIN(tmp);
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		setCLK(false);
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		setCLK(true);
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	setSYNC(true);
}

static void dac8568_Init(void){//DAC8568初始化
	uint32_t tmp;
	tmp = 0x07000000;//Software Reset
	spiWrite(tmp);
	tmp = 0x08000001;//Write Sequence for Enabling Internal Reference (Static Mode)
	spiWrite(tmp);
	//覆盖LDAC引脚
	tmp = 0x0600000F;
	spiWrite(tmp);
	//覆盖CLR引脚
	tmp = 0x05000003;
	spiWrite(tmp);
}
static void dac8568_WriteDacRegister(uint8_t ch, uint16_t dat){//写入输入寄存器并更新输出
	uint32_t tmp;
	ch &= 0x0F;
	tmp = 0x03000000;
	tmp |= (uint32_t)((uint32_t)ch << 20);
	tmp |= (uint32_t)((uint32_t)dat << 4);
	spiWrite(tmp);
}

void initChipDac(void){//DAC初始化
	dac8568_Init();
}
void UPDAC0(void){//立即从SPREG_DAC_0中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_0];
	if(temp > CONFIG_MAX_DAC_CH0)
		temp = CONFIG_MAX_DAC_CH0;
	if(temp <= CONFIG_MIN_DAC_CH0)
		temp = CONFIG_MIN_DAC_CH0;
	dac8568_WriteDacRegister(0x06, temp);
}
void UPDAC1(void){//立即从SPREG_DAC_1更新DAC1
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_1];
	if(temp > CONFIG_MAX_DAC_CH1)
		temp = CONFIG_MAX_DAC_CH1;
	if(temp <= CONFIG_MIN_DAC_CH1)
		temp = CONFIG_MIN_DAC_CH1;
	dac8568_WriteDacRegister(0x04, temp);
}
void UPDAC2(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_2];
	if(temp > CONFIG_MAX_DAC_CH2)
		temp = CONFIG_MAX_DAC_CH2;
	if(temp <= CONFIG_MIN_DAC_CH2)
		temp = CONFIG_MIN_DAC_CH2;
	dac8568_WriteDacRegister(0x02, temp);
}
void UPDAC3(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_3];
	if(temp > CONFIG_MAX_DAC_CH3)
		temp = CONFIG_MAX_DAC_CH3;
	if(temp <= CONFIG_MIN_DAC_CH3)
		temp = CONFIG_MIN_DAC_CH3;
	dac8568_WriteDacRegister(0x00, temp);
}
void UPDAC4(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_4];
	if(temp > CONFIG_MAX_DAC_CH4)
		temp = CONFIG_MAX_DAC_CH4;
	if(temp <= CONFIG_MIN_DAC_CH4)
		temp = CONFIG_MIN_DAC_CH4;
	dac8568_WriteDacRegister(0x01, temp);
}
void UPDAC5(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_5];
	if(temp > CONFIG_MAX_DAC_CH5)
		temp = CONFIG_MAX_DAC_CH5;
	if(temp <= CONFIG_MIN_DAC_CH5)
		temp = CONFIG_MIN_DAC_CH5;
	//dac8568_WriteDacRegister(0x01, temp);
}
void UPDAC6(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_6];
	if(temp > CONFIG_MAX_DAC_CH6)
		temp = CONFIG_MAX_DAC_CH6;
	if(temp <= CONFIG_MIN_DAC_CH6)
		temp = CONFIG_MIN_DAC_CH6;
	//dac8568_WriteDacRegister(0x01, temp);
}
void UPDAC7(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_7];
	if(temp > CONFIG_MAX_DAC_CH7)
		temp = CONFIG_MAX_DAC_CH7;
	if(temp <= CONFIG_MIN_DAC_CH7)
		temp = CONFIG_MIN_DAC_CH7;
	//dac8568_WriteDacRegister(0x01, temp);
}
void CLDAC(void){//立即清空全部DAC
	dac8568_WriteDacRegister(0x00, 0);
	dac8568_WriteDacRegister(0x01, 0);
	dac8568_WriteDacRegister(0x02, 0);
	dac8568_WriteDacRegister(0x03, 0);
	dac8568_WriteDacRegister(0x04, 0);
	dac8568_WriteDacRegister(0x05, 0);
	dac8568_WriteDacRegister(0x06, 0);
	dac8568_WriteDacRegister(0x07, 0);
}








