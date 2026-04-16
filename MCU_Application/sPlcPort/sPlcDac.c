#include "sPlc.h"
#include "boardConfig.h"
/*****************************************************************************/
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
__IO static void writeDac7311(uint16_t dat){
	uint8_t tmp, i;
	SET_DAC7311_CS(GPIO_PIN_RESET);//CS = 0
	dat = dat << 2;
	dat &= 0x3FFC;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	for(i = 0;i < 16;i ++){
		tmp = (uint8_t)(dat >> (15 - i)) & 0x01;
		SET_DAC7311_SDI((GPIO_PinState)tmp);//dat -> SDI
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_DAC7311_SCK(GPIO_PIN_SET);//SCK -> 1
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_DAC7311_SCK(GPIO_PIN_RESET);//SCK -> 0
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_DAC7311_CS(GPIO_PIN_SET);
}

void sPlcDacInit(void){//DAC初始化
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1); // 开启DAC输出
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2); // 开启DAC输出
	writeDac7311(0);
}
void UPDAC0(void){//立即从SPREG_DAC_0中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_0] & 0x0FFF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, temp); // 设置DAC输出值	
}
void UPDAC1(void){//立即从SPREG_DAC_1中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_1] & 0x0FFF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, temp); // 设置DAC输出值	
}
void UPDAC2(void){}
void UPDAC3(void){}
void UPDAC4(void){}
void UPDAC5(void){}
void UPDAC6(void){}
void UPDAC7(void){}
void UPDAC8(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_7] & 0x0FFF;
	writeDac7311(temp);
}
void UPDAC9(void){}
void UPDAC10(void){}
void UPDAC11(void){}
void UPDAC12(void){}
void UPDAC13(void){}
void UPDAC14(void){}
void UPDAC15(void){}
void UPDAC16(void){
	if(NVRAM0[SPREG_DAC_16] > CONFIG_DAC_MAXBIT_CH16){
		NVRAM0[SPREG_DAC_16] = CONFIG_DAC_MAXBIT_CH16;
	}
	setRedLaserPwm(NVRAM0[SPREG_DAC_16]);
}
void UPDAC17(void){


}

void CLDAC(void){//立即清空全部DAC
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 1); // 设置DAC输出值	
	writeDac7311(0);
}

#endif

#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_TRI_A0) || defined(MODEL_PVGLS_TRI_COMBINE_A0) || defined(MODEL_PVGLS_15W_1470_A1)
static void writeMcp4821_0(uint16_t dat){//MCP4821 SPI写入
	uint8_t tmp, i;
	SET_EDAC0_CS(GPIO_PIN_RESET);//CS = 0
	dat &= 0x0FFF;
	dat |= MCP4821_NSHDN_MASK;//OUTPUT ENABLE
	dat |= MCP4821_NGA_MASK;//VREF=2.048V
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	for(i = 0;i < 16;i ++){
		tmp = (uint8_t)(dat >> (15 - i)) & 0x01;
		SET_EDAC0_SDI((GPIO_PinState)tmp);//dat -> SDI
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_EDAC0_SCK(GPIO_PIN_SET);//SCK -> 1
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_EDAC0_SCK(GPIO_PIN_RESET);//SCK -> 0
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_EDAC0_CS(GPIO_PIN_SET);
}

static void writeMcp4821_1(uint16_t dat){//MCP4821 SPI写入
	uint8_t tmp, i;
	SET_EDAC1_CS(GPIO_PIN_RESET);//CS = 0
	dat &= 0x0FFF;
	dat |= MCP4821_NSHDN_MASK;//OUTPUT ENABLE
	dat |= MCP4821_NGA_MASK;//VREF=2.048V
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	for(i = 0;i < 16;i ++){
		tmp = (uint8_t)(dat >> (15 - i)) & 0x01;
		SET_EDAC1_SDI((GPIO_PinState)tmp);//dat -> SDI
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_EDAC1_SCK(GPIO_PIN_SET);//SCK -> 1
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_EDAC1_SCK(GPIO_PIN_RESET);//SCK -> 0
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_EDAC1_CS(GPIO_PIN_SET);
}

static void writeMcp4821_2(uint16_t dat){//MCP4821 SPI写入
	uint8_t tmp, i;
	SET_EDAC2_CS(GPIO_PIN_RESET);//CS = 0
	dat &= 0x0FFF;
	dat |= MCP4821_NSHDN_MASK;//OUTPUT ENABLE
	dat |= MCP4821_NGA_MASK;//VREF=2.048V
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	for(i = 0;i < 16;i ++){
		tmp = (uint8_t)(dat >> (15 - i)) & 0x01;
		SET_EDAC2_SDI((GPIO_PinState)tmp);//dat -> SDI
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_EDAC2_SCK(GPIO_PIN_SET);//SCK -> 1
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_EDAC2_SCK(GPIO_PIN_RESET);//SCK -> 0
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_EDAC2_CS(GPIO_PIN_SET);
}

void sPlcDacInit(void){//DAC初始化
	SET_EDAC0_CS(GPIO_PIN_SET);SET_EDAC1_CS(GPIO_PIN_SET);SET_EDAC2_CS(GPIO_PIN_SET);SET_EDAC3_CS(GPIO_PIN_SET);//SPI CS=1
	SET_EDAC0_SCK(GPIO_PIN_RESET);SET_EDAC1_SCK(GPIO_PIN_RESET);SET_EDAC2_SCK(GPIO_PIN_RESET);SET_EDAC3_SCK(GPIO_PIN_RESET); //SPI CLK = 0
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	writeMcp4821_0(0);
	writeMcp4821_1(0);
	writeMcp4821_2(0);
#if defined(MODEL_PVGLS_G5_TRI_A1) || defined(MODEL_PVGLS_G9_TRI_A1)

#endif
	printf("%s,%d,%s:init dac vref=2048mV\n",__FILE__, __LINE__, __func__);
	printf("%s,%d,%s:init dac done!\n",__FILE__, __LINE__, __func__);
}

void UPDAC0(void){//立即从SPREG_DAC_0中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_0] & 0x0FFF;
	writeMcp4821_0(temp);
	printf("%s,%d,%s:update dac0=%d\n",__FILE__, __LINE__, __func__, temp);
}
void UPDAC1(void){//立即从SPREG_DAC_1更新DAC1
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_1] & 0x0FFF;
	writeMcp4821_1(temp);
	writeMcp4821_2(temp);
	printf("%s,%d,%s:update dac1=%d\n",__FILE__, __LINE__, __func__, temp);
}

void CLDAC(void){//立即清空全部DAC
	writeMcp4821_0(0);
	writeMcp4821_1(0);
	writeMcp4821_2(0);
	printf("%s,%d,%s:clear all dac!\n",__FILE__, __LINE__, __func__);
}

#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
static void writeHGC5615(uint16_t dat){//HGC5616 模拟SPI写入
	uint16_t tmp, i, wdat;
	dat = dat & 0x3FF;
	SET_HGC5615_CS(GPIO_PIN_SET);//CS = 1
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_HGC5615_CS(GPIO_PIN_RESET);//CS = 0
	wdat = 0x0;
	wdat += dat;
	wdat = wdat << 2;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	for(i = 0;i < 16;i ++){
		tmp = (uint8_t)(wdat >> (15 - i)) & 0x01;
		SET_HGC5615_SDI((GPIO_PinState)tmp);//dat -> SDI
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_HGC5615_SCK(GPIO_PIN_SET);//SCK -> 1
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_HGC5615_SCK(GPIO_PIN_RESET);//SCK -> 0
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_HGC5615_CS(GPIO_PIN_SET);
}

void sPlcDacInit(void){//DAC初始化
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1); // 开启DAC输出
	writeHGC5615(0);
}
void UPDAC0(void){//立即从SPREG_DAC_0中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_0] & 0x0FFF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, temp); // 设置DAC输出值	
}
void UPDAC1(void){//立即从SPREG_DAC_1中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_1] & 0x0FFF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, temp); // 设置DAC输出值	
}

void UPDAC7(void){//立即从SPREG_DAC_0中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_7] & 0x0FFF;
	writeHGC5615(temp);
}
void CLDAC(void){//立即清空全部DAC
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 1); // 设置DAC输出值	
	writeHGC5615(0);
}
#endif

#if defined(LYPE_MCU_1V0_20260106)
static void dac8568_WriteDacRegister(uint8_t ch, uint16_t dat);
static void dac8568SpiWrite(uint32_t dat){//DAC8568 SPI写入
  volatile	uint8_t tmp, i;
	SET_DAC8568_SYNC(GPIO_PIN_SET);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_DAC8568_SCK(GPIO_PIN_SET);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_DAC8568_SYNC(GPIO_PIN_RESET);
	for(i = 0;i < 32;i ++){
		tmp = (uint8_t)(dat >> (31 - i)) & 0x01;
		SET_DAC8568_DOUT((GPIO_PinState)tmp);
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_DAC8568_SCK(GPIO_PIN_RESET);
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_DAC8568_SCK(GPIO_PIN_SET);
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	SET_DAC8568_SYNC(GPIO_PIN_SET);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
}

void dac8568_Init(void){//DAC8568初始化
	uint32_t tmp;
	SET_DAC8568_CLR(GPIO_PIN_SET);
	SET_DAC8568_LDAC(GPIO_PIN_RESET);
	//setCLR0(true);
	//setLDAC0(true);
	tmp = 0x07000000;//Software Reset
	dac8568SpiWrite(tmp);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	tmp = 0x08000001;//Write Sequence for Enabling Internal Reference (Static Mode)
	dac8568SpiWrite(tmp);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//覆盖LDAC引脚
	tmp = 0x0600000F;
	dac8568SpiWrite(tmp);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//覆盖CLR引脚
	tmp = 0x05000003;
	dac8568SpiWrite(tmp);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();

}
void dac8568_InitNoReset(void){//DAC8568 无复位初始化
	uint32_t tmp;
	//setCLR0(true);
	//setLDAC0(true);
	tmp = 0x08000001;//Write Sequence for Enabling Internal Reference (Static Mode)
	dac8568SpiWrite(tmp);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//覆盖LDAC引脚
	tmp = 0x0600000F;
	dac8568SpiWrite(tmp);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//覆盖CLR引脚
	tmp = 0x05000003;
	dac8568SpiWrite(tmp);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
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
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_WriteDacRegister(0x01, temp);
}
void UPDAC2(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_WriteDacRegister(0x2, temp);
}
void UPDAC3(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_WriteDacRegister(0x03, temp);
}
void UPDAC4(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_WriteDacRegister(0x04, temp);
}
void UPDAC5(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_WriteDacRegister(0x05, temp);
}
void UPDAC6(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_WriteDacRegister(0x06, temp);
}
void UPDAC7(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
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
	SET_DAC8568_CLR(GPIO_PIN_RESET);
	dac8568_WriteDacRegister(0x00, 0x0);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	dac8568_WriteDacRegister(0x01, 0x0);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	dac8568_WriteDacRegister(0x02, 0x0);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	dac8568_WriteDacRegister(0x03, 0x0);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	dac8568_WriteDacRegister(0x04, 0x0);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	dac8568_WriteDacRegister(0x05, 0x0);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	dac8568_WriteDacRegister(0x06, 0x0);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	dac8568_WriteDacRegister(0x07, 0x0);
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();	
	SET_DAC8568_CLR(GPIO_PIN_SET);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 1); // 设置DAC输出值
}

#endif





