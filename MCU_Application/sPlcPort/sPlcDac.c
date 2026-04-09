#include "sPlc.h"
#include "boardConfig.h"
/*****************************************************************************/
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP)
__IO static void writeDac7311(uint16_t dat){
	uint8_t tmp, i;
	SET_EDAC7_CS(GPIO_PIN_RESET);//CS = 0
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
		SET_EDAC7_SDI((GPIO_PinState)tmp);//dat -> SDI
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_EDAC7_SCK(GPIO_PIN_SET);//SCK -> 1
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		SET_EDAC7_SCK(GPIO_PIN_RESET);//SCK -> 0
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
	SET_EDAC7_CS(GPIO_PIN_SET);
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
#define POWER_DOWN_INTERNAL_REFERENCE 					0
#define POWER_UP 																1
#define DAC8568_RESET 													2
typedef enum {//通道定义
    DAC8568_CH_A = 0x0,  // 通道A
    DAC8568_CH_B = 0x1,  // 通道B
    DAC8568_CH_C = 0x2,  // 通道C
    DAC8568_CH_D = 0x3,  // 通道D
    DAC8568_CH_E = 0x4,  // 通道E
    DAC8568_CH_F = 0x5,  // 通道F
    DAC8568_CH_G = 0x6,  // 通道G
    DAC8568_CH_H = 0x7,  // 通道H
    DAC8568_CH_ALL = 0xF // 所有通道
} DAC8568_ChannelDef;

typedef enum {//命令定义
    DAC8568_CMD_WRITE_INPUT_REG      = 0x0,  // 写入输入寄存器（无更新）
    DAC8568_CMD_UPDATE_DAC_REG       = 0x1,  // 更新DAC寄存器（从输入寄存器）
    DAC8568_CMD_WRITE_INPUT_REG_UPDATE_ALL = 0x2,  // 写入输入寄存器并更新所有DAC
    DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH  = 0x3,  // 写入输入寄存器并更新指定DAC
    DAC8568_CMD_POWER_DOWN_UP        = 0x4,  // 掉电/上电控制
    DAC8568_CMD_HW_LDAC_MASK         = 0x5,  // 硬件LDAC屏蔽控制
    DAC8568_CMD_SW_RESET             = 0x6,  // 软件复位
    DAC8568_CMD_SW_LDAC              = 0x7,  // 软件LDAC
    DAC8568_CMD_READ_BACK            = 0x8   // 读回寄存器（仅输入寄存器）
} DAC8568_CmdDef;

static void softSpiWrite(uint32_t dat){//DAC8568 SPI写入
	uint8_t tmp, i;
	DAC8568_SYNC_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	DAC8568_SCK_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	DAC8568_SYNC_LOW;
	for(i = 0;i < 32;i ++){
		tmp = (uint8_t)(dat >> (31 - i)) & 0x01;
		if (tmp == 0x01)
		   DAC8568_DIN_HIGH;
		else
			 DAC8568_DIN_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	DAC8568_SCK_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	DAC8568_SCK_HIGH;
	}
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	DAC8568_SYNC_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
}

static void dac8568_Init(void){//DAC8568初始化
	uint32_t tmp;
	tmp = 0x07000000;//Software Reset
	softSpiWrite(tmp);
	tmp = 0x08000001;//Write Sequence for Enabling Internal Reference (Static Mode)
	softSpiWrite(tmp);
	//覆盖LDAC引脚
	tmp = 0x0600000F;
	softSpiWrite(tmp);
	//覆盖CLR引脚
	tmp = 0x05000003;
	softSpiWrite(tmp);
}

static void dac8568_InitNoReset(void){//DAC8568初始化
	uint32_t tmp;
	tmp = 0x08000001;//Write Sequence for Enabling Internal Reference (Static Mode)
	softSpiWrite(tmp);
	//覆盖LDAC引脚
	tmp = 0x0600000F;
	softSpiWrite(tmp);
	//覆盖CLR引脚
	tmp = 0x05000003;
	softSpiWrite(tmp);
}

static void dac8568_WriteDacRegister(uint8_t ch, uint16_t dat){//写入输入寄存器并更新输出
	uint32_t tmp;
	ch &= 0x0F;
	tmp = 0x03000000;
	tmp |= (uint32_t)((uint32_t)ch << 20);
	tmp |= (uint32_t)((uint32_t)dat << 4);
	softSpiWrite(tmp);
}

static void dac8568_Send32BitData(DAC8568_CmdDef cmd, DAC8568_ChannelDef ch, uint16_t data){//////////组装32bit数据并通过模拟SPI发送
    uint32_t tx_data = 0;
    // 组装32bit数据
    tx_data |= (0x0 << 28);          // 前4bit：0
    tx_data |= ((uint32_t)cmd << 24); // 4bit命令
    tx_data |= ((uint32_t)ch << 20);  // 4bit地址
    tx_data |= ((uint32_t)data << 4); // 16bit数据
    tx_data |= 0x0;                  // 后4bit：0
    
    // 开始发送数据
    DAC8568_SYNC_LOW;  // 拉低SYNC，选通DAC
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	
    // 分4个字节发送32bit数据（高位先行）
    softSpiWrite((tx_data >> 24) & 0xFF); // 第1字节：0 + cmd
    softSpiWrite((tx_data >> 16) & 0xFF); // 第2字节：addr + data高8位
    softSpiWrite((tx_data >> 8) & 0xFF);  // 第3字节：data低8位
    softSpiWrite(tx_data & 0xFF);         // 第4字节：0
    
    DAC8568_SYNC_HIGH; // 拉高SYNC，结束发送
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
}

static void dac8568_SendCommand(uint8_t command){
	switch(command){
		case POWER_DOWN_INTERNAL_REFERENCE:{
			DAC8568_SYNC_LOW;  // 拉低SYNC，选通DAC
			__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			softSpiWrite(0x09); //发送DB31-DB24位
			softSpiWrite(0x0c); //发送DB23-DB16位
			softSpiWrite(0); //发送DB15-DB8位
			softSpiWrite(0x00); //发送DB7-DB0位
			DAC8568_SYNC_HIGH; // 拉高SYNC，结束发送
			__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			break;
		}
		//通过将相应位设置为“1”，为DAC A、B、C、D、E、F、G、H通电
		case POWER_UP:{
			DAC8568_SYNC_LOW;  // 拉低SYNC，选通DAC
			softDelayUs(1);
			softSpiWrite(0x04); //发送DB31-DB24位
			softSpiWrite(0); //发送DB23-DB16位
			softSpiWrite(0); //发送DB15-DB8位
			softSpiWrite(0xff); //发送DB7-DB0位
			DAC8568_SYNC_HIGH; // 拉高SYNC，结束发送
			softDelayUs(1);
			break;
		}
		//重启
		case DAC8568_RESET:{
			DAC8568_SYNC_LOW;  // 拉低SYNC，选通DAC
			softDelayUs(1);
			softSpiWrite(0x07); //发送DB31-DB24位
			softSpiWrite(0); //发送DB23-DB16位
			softSpiWrite(0); //发送DB15-DB8位
			softSpiWrite(0); //发送DB7-DB0位
			DAC8568_SYNC_HIGH; // 拉高SYNC，结束发送
			softDelayUs(1);
			break;
		};
	}
}

static void dac8568_SoftReset(void){//软件复位DAC8568
	// 发送软件复位命令，地址位无意义，数据位填0
	dac8568_Send32BitData(DAC8568_CMD_SW_RESET, DAC8568_CH_ALL, 0x0000);
	HAL_Delay(1);//保持低电平至少100ns（延时1ms确保稳定）
}

void sPlcDacInit(void){//DAC初始化
	dac8568_SoftReset();
	dac8568_Init();	
}
void UPDAC0(void){//立即从SPREG_DAC_0中更新DAC0
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH, DAC8568_CH_A, temp);
}
void UPDAC1(void){//立即从SPREG_DAC_1中更新DAC0
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH, DAC8568_CH_B, temp);
}
void UPDAC2(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH, DAC8568_CH_C, temp);
}
void UPDAC3(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH, DAC8568_CH_D, temp);
}
void UPDAC4(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH, DAC8568_CH_E, temp);
}
void UPDAC5(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH, DAC8568_CH_F, temp);
}
void UPDAC6(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH, DAC8568_CH_G, temp);
}
void UPDAC7(void){
	uint16_t temp;
	temp = (uint16_t)NVRAM0[SPREG_DAC_0];
	dac8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_CH, DAC8568_CH_H, temp);
}
void UPDAC8(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_8];
	if(temp > 0xFFF){
		temp = 0xFFF;
	}
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_8B_R, 0xFF); // 设置DAC输出值	
}
void UPDAC9(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_9];
	if(temp > 0xFFF){
		temp = 0xFFF;
	}
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_8B_R, 0xFF); // 设置DAC输出值	
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
}

void CLDAC(void){//立即清空全部DAC
	dac8568_Send32BitData(DAC8568_CMD_WRITE_INPUT_REG_UPDATE_ALL, DAC8568_CH_ALL, 0x0);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 1); // 设置DAC输出值
}

#endif





