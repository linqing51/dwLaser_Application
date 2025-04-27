#include "sPlc.h"
/*****************************************************************************/
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

static void hgc5615(uint16_t dat){//HGC5616 模拟SPI写入
	uint16_t tmp, i, wdat;
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
	hgc5615(temp);
}
void CLDAC(void){//立即清空全部DAC
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 1); // 设置DAC输出值	
}
#endif

#if defined(MODEL_PVGLS_7W_1940_A0)

#endif




