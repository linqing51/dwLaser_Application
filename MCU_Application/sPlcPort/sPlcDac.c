#include "sPlc.h"
/*****************************************************************************/
static void dac8568SpiWrite(uint32_t dat){//DAC8568 SPI写入
  uint8_t tmp, i;
	SET_DAC8568_SYNC(GPIO_PIN_SET);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_DAC8568_SCK(GPIO_PIN_SET);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_DAC8568_SYNC(GPIO_PIN_RESET);
	for(i = 0;i < 32;i ++){
		tmp = (uint8_t)(dat >> (31 - i)) & 0x01;
		SET_DAC8568_DOUT((GPIO_PinState)tmp);
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_DAC8568_SCK(GPIO_PIN_RESET);
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_DAC8568_SCK(GPIO_PIN_SET);
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_DAC8568_SYNC(GPIO_PIN_SET);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
}

static void dac8568_Init(void){//DAC8568初始化
	uint32_t tmp;
	//setCLR0(true);
	//setLDAC0(true);
	tmp = 0x07000000;//Software Reset
	dac8568SpiWrite(tmp);
	tmp = 0x08000001;//Write Sequence for Enabling Internal Reference (Static Mode)
	dac8568SpiWrite(tmp);
	//覆盖LDAC引脚
	tmp = 0x0600000F;
	dac8568SpiWrite(tmp);
	//覆盖CLR引脚
	tmp = 0x05000003;
	dac8568SpiWrite(tmp);
}

static void dac8568_InitNoReset(void){//DAC8568 无复位初始化
	uint32_t tmp;
	//setCLR0(true);
	//setLDAC0(true);
	tmp = 0x08000001;//Write Sequence for Enabling Internal Reference (Static Mode)
	dac8568SpiWrite(tmp);
	//覆盖LDAC引脚
	tmp = 0x0600000F;
	dac8568SpiWrite(tmp);
	//覆盖CLR引脚
	tmp = 0x05000003;
	dac8568SpiWrite(tmp);
}

static void dac8568_WriteDacRegister(uint8_t ch, uint16_t dat){//写入输入寄存器并更新输出
	uint32_t tmp;
	ch &= 0x0F;
	tmp = 0x03000000;
	tmp |= (uint32_t)((uint32_t)ch << 20);
	tmp |= (uint32_t)((uint32_t)dat << 4);
	dac8568SpiWrite(tmp);
}

void sPlcDacInit(void){//DAC初始化
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1); // 开启DAC输出
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2); // 开启DAC输出
	dac8568_Init();	
}
void UPDAC0(void){//立即从SPREG_DAC_0中更新DAC0
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_WriteDacRegister(0x0, temp);
}
void UPDAC1(void){//立即从SPREG_DAC_1中更新DAC0
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_1];
	dac8568_WriteDacRegister(0x01, temp);
}
void UPDAC2(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_2];
	dac8568_WriteDacRegister(0x2, temp);
}
void UPDAC3(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_3];
	dac8568_WriteDacRegister(0x03, temp);
}
void UPDAC4(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_4];
	dac8568_WriteDacRegister(0x04, temp);
}
void UPDAC5(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_5];
	dac8568_WriteDacRegister(0x05, temp);
}
void UPDAC6(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_6];
	dac8568_WriteDacRegister(0x06, temp);
}
void UPDAC7(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_7];
	dac8568_WriteDacRegister(0x07, temp);
}
void UPDAC8(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_8];
	if(temp > 0xFFF){
		temp = 0xFFF;
	}
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, temp); // 设置DAC输出值	
}
void UPDAC9(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_9];
	if(temp > 0xFFF){
		temp = 0xFFF;
	}
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_8B_R, temp); // 设置DAC输出值	
}
void UPDAC10(void){
}
void UPDAC11(void){
}
void UPDAC12(void){
}
void UPDAC13(void){
}
void UPDAC14(void){
}
void UPDAC15(void){
}
void UPDAC16(void){
	setRedLaserPwm(NVRAM0[SPREG_DAC_16]);
}
void UPDAC17(void){
	setGreenLaserPwm(NVRAM0[SPREG_DAC_17]);
}

void CLDAC(void){//立即清空全部DAC
	dac8568_WriteDacRegister(0x00, 0x0);
	dac8568_WriteDacRegister(0x01, 0x0);
	dac8568_WriteDacRegister(0x02, 0x0);
	dac8568_WriteDacRegister(0x03, 0x0);
	dac8568_WriteDacRegister(0x04, 0x0);
	dac8568_WriteDacRegister(0x05, 0x0);
	dac8568_WriteDacRegister(0x06, 0x0);
	dac8568_WriteDacRegister(0x07, 0x0);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 1); // 设置DAC输出值
}






