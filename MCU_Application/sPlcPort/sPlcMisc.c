#include "sPlc.h"
#include "boardConfig.h"
#include "appConfig.h"
#include "usbh_core.h"
/*****************************************************************************/
#define OFFSET_OF(type, member)  ((uint32_t)&(((type *)0)->member))
extern deviceConfig_t deviceConfig;
static int16_t FanSpeed = -1;
/*****************************************************************************/
/**
 * @brief 通用结构体成员偏移量计算函数
 * @param type_size  结构体总大小（用 sizeof(结构体) 传入）
 * @param member_ptr 结构体成员的地址
 * @return 成员相对于结构体起始地址的偏移量
 */
size_t get_offset(size_t type_size, void *member_ptr) {
    // 利用 0 地址结构体指针计算偏移
    return (size_t)member_ptr;
}




void delayMs(uint32_t delayMs){//SPLC 阻塞延时
	vTaskDelay(delayMs);
}

void setFanSpeed(int16_t speed){//设置风扇转速
	if(FanSpeed != speed){
		if(speed > CONFIG_FAN_MAX_DC){
			speed = CONFIG_FAN_MAX_DC;
		}
		if(speed < CONFIG_FAN_MIN_DC){
			speed = CONFIG_FAN_MIN_DC;
		}
		__HAL_TIM_SET_COMPARE(&CONFIG_FAN0_TIM_HANDLE, CONFIG_FAN0_PWM_CHANNEL, speed);
		if(speed != 0){
			HAL_TIM_PWM_Start(&CONFIG_FAN0_TIM_HANDLE, CONFIG_FAN0_PWM_CHANNEL);//打开TIM
		}
		else{
			HAL_TIM_PWM_Stop(&CONFIG_FAN0_TIM_HANDLE, CONFIG_FAN0_PWM_CHANNEL);//关闭TIM
		}

		if(speed <= 0){
			SET_FAN0_OFF;
		}
		else if(speed >0 && speed < 100){
			SET_FAN0_ON;
			SET_FAN0_TIM_PWM(speed);
		}
		else if(speed >= 100){
			SET_FAN0_ON;
			SET_FAN0_TIM_PWM(100);
		}
		FanSpeed = speed;
		printf("%s,%d,%s:set fan:%d\n",__FILE__, __LINE__, __func__, speed);	
	}
}

void loadDeviceConfig(void){//从EPROM载入配置文件
	uint32_t crc32_eprom_cfg, crc32_cfg, i;
	epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//从EPROM载入设备配置
	epromReadDword(CONFIG_EPROM_CFG_CRC, &crc32_eprom_cfg);
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	if(crc32_eprom_cfg != crc32_cfg){//校验码错误使用默认配置
		printf("%s,%d,%s:load device config crc fail!!!\n",__FILE__, __LINE__, __func__);
		printf("%s,%d,%s:using default device config!\n",__FILE__, __LINE__, __func__);
		
#if defined(MODLE_M1470_640_10_15_02_D200_22_G5W_PK)//1470 V1
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 15;
		deviceConfig.calibrationPwr0[2] = 21;
		deviceConfig.calibrationPwr0[3] = 28;
		deviceConfig.calibrationPwr0[4] = 38;
		deviceConfig.calibrationPwr0[5] = 48;
		deviceConfig.calibrationPwr0[6] = 58;
		deviceConfig.calibrationPwr0[7] = 68;
		deviceConfig.calibrationPwr0[8] = 77;
		deviceConfig.calibrationPwr0[9] = 87;
		deviceConfig.calibrationPwr0[10] = 96;
		deviceConfig.calibrationPwr0[11] = 105;
		deviceConfig.calibrationPwr0[12] = 114;
		deviceConfig.calibrationPwr0[13] = 120;
		deviceConfig.calibrationPwr0[14] = 126;
		deviceConfig.calibrationPwr0[15] = 133;
		deviceConfig.calibrationPwr0[16] = 138;
		deviceConfig.calibrationPwr0[17] = 144;
		deviceConfig.calibrationPwr0[18] = 149;
		deviceConfig.calibrationPwr0[19] = 153;

		for(i = 0;i <= 19;i ++){//清空其他波长
			deviceConfig.calibrationPwr1[i] = i;
			deviceConfig.calibrationPwr2[i] = i;
			deviceConfig.calibrationPwr3[i] = i;
			deviceConfig.calibrationPwr4[i] = i;
			deviceConfig.calibrationPwr5[i] = i;
			deviceConfig.calibrationPwr6[i] = i;
			deviceConfig.calibrationPwr7[i] = i;
		}
		
#endif

#if defined(MODLE_M1470_980_640_10_15_35_05_D200_22_G5W_PK) //1470-980 V1
		//1470nm
		deviceConfig.calibrationPwr0[0] = 6;
		deviceConfig.calibrationPwr0[1] = 11; 
		deviceConfig.calibrationPwr0[2] = 16;
		deviceConfig.calibrationPwr0[3] = 21;
		deviceConfig.calibrationPwr0[4] = 29;
		deviceConfig.calibrationPwr0[5] = 36;
		deviceConfig.calibrationPwr0[6] = 44;
		deviceConfig.calibrationPwr0[7] = 52;
		deviceConfig.calibrationPwr0[8] = 60;
		deviceConfig.calibrationPwr0[9] = 68;
		deviceConfig.calibrationPwr0[10] = 77;
		deviceConfig.calibrationPwr0[11] = 85;
		deviceConfig.calibrationPwr0[12] = 92;
		deviceConfig.calibrationPwr0[13] = 99;
		deviceConfig.calibrationPwr0[14] = 106;
		deviceConfig.calibrationPwr0[15] = 113;
		deviceConfig.calibrationPwr0[16] = 119;
		deviceConfig.calibrationPwr0[17] = 125;
		deviceConfig.calibrationPwr0[18] = 138;
		deviceConfig.calibrationPwr0[19] = 150;
		//980nm
		deviceConfig.calibrationPwr1[0] = 9;
		deviceConfig.calibrationPwr1[0] = 15;
		deviceConfig.calibrationPwr1[0] = 21;
		deviceConfig.calibrationPwr1[3] = 27;
		deviceConfig.calibrationPwr1[0] = 36;
		deviceConfig.calibrationPwr1[5] = 45;
		deviceConfig.calibrationPwr1[0] = 54;
		deviceConfig.calibrationPwr1[7] = 62;
		deviceConfig.calibrationPwr1[0] = 71;
		deviceConfig.calibrationPwr1[9] = 79;
		deviceConfig.calibrationPwr1[0] = 88;
		deviceConfig.calibrationPwr1[11] = 96;
		deviceConfig.calibrationPwr1[0] = 104;
		deviceConfig.calibrationPwr1[13] = 112;
		deviceConfig.calibrationPwr1[0] = 120;
		deviceConfig.calibrationPwr1[15] = 127;
		deviceConfig.calibrationPwr1[0] = 134;
		deviceConfig.calibrationPwr1[17] = 140;
		deviceConfig.calibrationPwr1[0] = 145;
		deviceConfig.calibrationPwr1[19] = 150;

		for(i = 0;i <= 19;i ++){//清空其他波长
			//deviceConfig.calibrationPwr1[i] = i;
			deviceConfig.calibrationPwr2[i] = i;
			deviceConfig.calibrationPwr3[i] = i;
			deviceConfig.calibrationPwr4[i] = i;
			deviceConfig.calibrationPwr5[i] = i;
			deviceConfig.calibrationPwr6[i] = i;
			deviceConfig.calibrationPwr7[i] = i;
		}
#endif

#if defined(MODLE_M1470_980_640_10_15_15_02_D200_22_G5W_PK)//1470-980-650 V2
		//1470
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 19;
		deviceConfig.calibrationPwr0[2] = 22;
		deviceConfig.calibrationPwr0[3] = 28;
		deviceConfig.calibrationPwr0[4] = 38;
		deviceConfig.calibrationPwr0[5] = 48;
		deviceConfig.calibrationPwr0[6] = 58;
		deviceConfig.calibrationPwr0[7] = 68;
		deviceConfig.calibrationPwr0[8] = 77;
		deviceConfig.calibrationPwr0[9] = 87;
		deviceConfig.calibrationPwr0[10] = 96;
		deviceConfig.calibrationPwr0[11] = 105;
		deviceConfig.calibrationPwr0[12] = 113;
		deviceConfig.calibrationPwr0[13] = 120;
		deviceConfig.calibrationPwr0[14] = 127;
		deviceConfig.calibrationPwr0[15] = 133;
		deviceConfig.calibrationPwr0[16] = 139;
		deviceConfig.calibrationPwr0[17] = 144;
		deviceConfig.calibrationPwr0[18] = 148;
		deviceConfig.calibrationPwr0[19] = 153;
		//980
		deviceConfig.calibrationPwr1[0] = 9;
		deviceConfig.calibrationPwr1[1] = 15;
		deviceConfig.calibrationPwr1[2] = 22;
		deviceConfig.calibrationPwr1[3] = 28;
		deviceConfig.calibrationPwr1[4] = 38;
		deviceConfig.calibrationPwr1[5] = 48;
		deviceConfig.calibrationPwr1[6] = 58;
		deviceConfig.calibrationPwr1[7] = 68;
		deviceConfig.calibrationPwr1[8] =	77;
		deviceConfig.calibrationPwr1[9] = 87;
		deviceConfig.calibrationPwr1[10] =96;
		deviceConfig.calibrationPwr1[11] = 105;
		deviceConfig.calibrationPwr1[12] = 113;
		deviceConfig.calibrationPwr1[13] = 120;
		deviceConfig.calibrationPwr1[14] = 126;
		deviceConfig.calibrationPwr1[15] = 133;
		deviceConfig.calibrationPwr1[16] = 139;
		deviceConfig.calibrationPwr1[17] = 144;
		deviceConfig.calibrationPwr1[18] = 149;
		deviceConfig.calibrationPwr1[19] = 153;
		
		for(i = 0;i <= 19;i ++){//清空其他波长
			//deviceConfig.calibrationPwr1[i] = i;
			deviceConfig.calibrationPwr2[i] = i;
			deviceConfig.calibrationPwr3[i] = i;
			deviceConfig.calibrationPwr4[i] = i;
			deviceConfig.calibrationPwr5[i] = i;
			deviceConfig.calibrationPwr6[i] = i;
			deviceConfig.calibrationPwr7[i] = i;
		}
#endif

#if defined(MODLE_M1470_980_640_10_15_35_05_D200_22_G5W_PK)
		//1470
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 15;
		deviceConfig.calibrationPwr0[2] = 21;
		deviceConfig.calibrationPwr0[3] = 28;
		deviceConfig.calibrationPwr0[4] = 38;
		deviceConfig.calibrationPwr0[5] = 48;
		deviceConfig.calibrationPwr0[6] = 58;
		deviceConfig.calibrationPwr0[7] = 68;
		deviceConfig.calibrationPwr0[8] = 77;
		deviceConfig.calibrationPwr0[9] = 87;
		deviceConfig.calibrationPwr0[10] = 96;
		deviceConfig.calibrationPwr0[11] = 105;
		deviceConfig.calibrationPwr0[12] = 113;
		deviceConfig.calibrationPwr0[13] = 120;
		deviceConfig.calibrationPwr0[14] = 127;
		deviceConfig.calibrationPwr0[15] = 133;
		deviceConfig.calibrationPwr0[16] = 139;
		deviceConfig.calibrationPwr0[17] = 144;
		deviceConfig.calibrationPwr0[18] = 149;
		deviceConfig.calibrationPwr0[19] = 153;
		
		//980
		deviceConfig.calibrationPwr1[0] = 9;
		deviceConfig.calibrationPwr1[1] = 15;
		deviceConfig.calibrationPwr1[2] = 22;
		deviceConfig.calibrationPwr1[3] = 28;
		deviceConfig.calibrationPwr1[4] = 38;
		deviceConfig.calibrationPwr1[5] = 48;
		deviceConfig.calibrationPwr1[6] = 58;
		deviceConfig.calibrationPwr1[7] = 68;
		deviceConfig.calibrationPwr1[8] = 77;
		deviceConfig.calibrationPwr1[9] = 87;
		deviceConfig.calibrationPwr1[10] = 96;
		deviceConfig.calibrationPwr1[11] = 105;
		deviceConfig.calibrationPwr1[12] = 113;
		deviceConfig.calibrationPwr1[13] = 120;
		deviceConfig.calibrationPwr1[14] = 126;
		deviceConfig.calibrationPwr1[15] = 133;
		deviceConfig.calibrationPwr1[16] = 138;
		deviceConfig.calibrationPwr1[17] = 144;
		deviceConfig.calibrationPwr1[18] = 149;
		deviceConfig.calibrationPwr1[19] = 153;

		for(i = 0;i <= 19;i ++){//清空其他波长
			//deviceConfig.calibrationPwr1[i] = i;
			deviceConfig.calibrationPwr2[i] = i;
			deviceConfig.calibrationPwr3[i] = i;
			deviceConfig.calibrationPwr4[i] = i;
			deviceConfig.calibrationPwr5[i] = i;
			deviceConfig.calibrationPwr6[i] = i;
			deviceConfig.calibrationPwr7[i] = i;
		}
#endif

#if defined(MODLE_M12_1920_10_400S)
		deviceConfig.calibrationPwr0[0] = 6;
		deviceConfig.calibrationPwr0[1] = 11;
		deviceConfig.calibrationPwr0[2] = 16;
		deviceConfig.calibrationPwr0[3] = 20;
		deviceConfig.calibrationPwr0[4] = 26;
		deviceConfig.calibrationPwr0[5] = 32;
		deviceConfig.calibrationPwr0[6] = 39;
		deviceConfig.calibrationPwr0[7] = 45;
		deviceConfig.calibrationPwr0[8] = 51;
		deviceConfig.calibrationPwr0[9] = 56;
		deviceConfig.calibrationPwr0[10] = 61;
		deviceConfig.calibrationPwr0[11] = 66;
		deviceConfig.calibrationPwr0[12] = 69;
		deviceConfig.calibrationPwr0[13] = 72;
		deviceConfig.calibrationPwr0[14] = 76;
		deviceConfig.calibrationPwr0[15] = 81;
		deviceConfig.calibrationPwr0[16] = 84;
		deviceConfig.calibrationPwr0[17] = 87;
		deviceConfig.calibrationPwr0[18] = 94;
		deviceConfig.calibrationPwr0[19] = 100;

		for(i = 0;i <= 19;i ++){//清空其他波长
			deviceConfig.calibrationPwr1[i] = i;
			deviceConfig.calibrationPwr2[i] = i;
			deviceConfig.calibrationPwr3[i] = i;
			deviceConfig.calibrationPwr4[i] = i;
			deviceConfig.calibrationPwr5[i] = i;
			deviceConfig.calibrationPwr6[i] = i;
			deviceConfig.calibrationPwr7[i] = i;
		}
#endif		

#if defined(MODLE_M1470_640_10_30_05_D200_22_G9_PK)
		//1470
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 15;
		deviceConfig.calibrationPwr0[2] = 21;
		deviceConfig.calibrationPwr0[3] = 28;
		deviceConfig.calibrationPwr0[4] = 38;
		deviceConfig.calibrationPwr0[5] = 48;
		deviceConfig.calibrationPwr0[6] = 58;
		deviceConfig.calibrationPwr0[7] = 68;
		deviceConfig.calibrationPwr0[8] = 77;
		deviceConfig.calibrationPwr0[9] = 87;
		deviceConfig.calibrationPwr0[10] = 96;
		deviceConfig.calibrationPwr0[11] = 105;
		deviceConfig.calibrationPwr0[12] = 113;
		deviceConfig.calibrationPwr0[13] = 120;
		deviceConfig.calibrationPwr0[14] = 127;
		deviceConfig.calibrationPwr0[15] = 133;
		deviceConfig.calibrationPwr0[16] = 139;
		deviceConfig.calibrationPwr0[17] = 144;
		deviceConfig.calibrationPwr0[18] = 149;
		deviceConfig.calibrationPwr0[19] = 153;

		for(i = 0;i <= 19;i ++){//清空其他波长
			deviceConfig.calibrationPwr1[i] = i;
			deviceConfig.calibrationPwr2[i] = i;
			deviceConfig.calibrationPwr3[i] = i;
			deviceConfig.calibrationPwr4[i] = i;
			deviceConfig.calibrationPwr5[i] = i;
			deviceConfig.calibrationPwr6[i] = i;
			deviceConfig.calibrationPwr7[i] = i;
		}
#endif

#if defined(MODLE_M450_980_200_60_D275_22_VI1_GP)
		//CH0-1470
		deviceConfig.calibrationPwr0[0] = 25;
		deviceConfig.calibrationPwr0[1] = 50;
		deviceConfig.calibrationPwr0[2] = 75;
		deviceConfig.calibrationPwr0[3] = 100;
		deviceConfig.calibrationPwr0[4] = 125;
		deviceConfig.calibrationPwr0[5] = 150;
		deviceConfig.calibrationPwr0[6] = 175;
		deviceConfig.calibrationPwr0[7] = 200;
		deviceConfig.calibrationPwr0[8] = 225;
		deviceConfig.calibrationPwr0[9] = 250;
		deviceConfig.calibrationPwr0[10] = 275;
		deviceConfig.calibrationPwr0[11] = 300;
		deviceConfig.calibrationPwr0[12] = 325;
		deviceConfig.calibrationPwr0[13] = 350;
		deviceConfig.calibrationPwr0[14] = 375;
		deviceConfig.calibrationPwr0[15] = 400;
		deviceConfig.calibrationPwr0[16] = 425;
		deviceConfig.calibrationPwr0[17] = 450;
		deviceConfig.calibrationPwr0[18] = 470;
		deviceConfig.calibrationPwr0[19] = 500;
		//CH1-1470
		deviceConfig.calibrationPwr1[0] = 25;
		deviceConfig.calibrationPwr1[1] = 50;
		deviceConfig.calibrationPwr1[2] = 75;
		deviceConfig.calibrationPwr1[3] = 100;
		deviceConfig.calibrationPwr1[4] = 125;
		deviceConfig.calibrationPwr1[5] = 150;
		deviceConfig.calibrationPwr1[6] = 175;
		deviceConfig.calibrationPwr1[7] = 200;
		deviceConfig.calibrationPwr1[8] = 225;
		deviceConfig.calibrationPwr1[9] = 250;
		deviceConfig.calibrationPwr1[10] = 275;
		deviceConfig.calibrationPwr1[11] = 300;
		deviceConfig.calibrationPwr1[12] = 325;
		deviceConfig.calibrationPwr1[13] = 350;
		deviceConfig.calibrationPwr1[14] = 375;
		deviceConfig.calibrationPwr1[15] = 400;
		deviceConfig.calibrationPwr1[16] = 425;
		deviceConfig.calibrationPwr1[17] = 450;
		deviceConfig.calibrationPwr1[18] = 470;
		deviceConfig.calibrationPwr1[19] = 500;	
		//CH2-1470
		deviceConfig.calibrationPwr2[0] = 25;
		deviceConfig.calibrationPwr2[1] = 50;
		deviceConfig.calibrationPwr2[2] = 75;
		deviceConfig.calibrationPwr2[3] = 100;
		deviceConfig.calibrationPwr2[4] = 125;
		deviceConfig.calibrationPwr2[5] = 150;
		deviceConfig.calibrationPwr2[6] = 175;
		deviceConfig.calibrationPwr2[7] = 200;
		deviceConfig.calibrationPwr2[8] = 225;
		deviceConfig.calibrationPwr2[9] = 250;
		deviceConfig.calibrationPwr2[10] = 275;
		deviceConfig.calibrationPwr2[11] = 300;
		deviceConfig.calibrationPwr2[12] = 325;
		deviceConfig.calibrationPwr2[13] = 350;
		deviceConfig.calibrationPwr2[14] = 375;
		deviceConfig.calibrationPwr2[15] = 400;
		deviceConfig.calibrationPwr2[16] = 425;
		deviceConfig.calibrationPwr2[17] = 450;
		deviceConfig.calibrationPwr2[18] = 470;
		deviceConfig.calibrationPwr2[19] = 500;
		//CH3-1470
		deviceConfig.calibrationPwr3[0] = 25;
		deviceConfig.calibrationPwr3[1] = 50;
		deviceConfig.calibrationPwr3[2] = 75;
		deviceConfig.calibrationPwr3[3] = 100;
		deviceConfig.calibrationPwr3[4] = 125;
		deviceConfig.calibrationPwr3[5] = 150;
		deviceConfig.calibrationPwr3[6] = 175;
		deviceConfig.calibrationPwr3[7] = 200;
		deviceConfig.calibrationPwr3[8] = 225;
		deviceConfig.calibrationPwr3[9] = 250;
		deviceConfig.calibrationPwr3[10] = 275;
		deviceConfig.calibrationPwr3[11] = 300;
		deviceConfig.calibrationPwr3[12] = 325;
		deviceConfig.calibrationPwr3[13] = 350;
		deviceConfig.calibrationPwr3[14] = 375;
		deviceConfig.calibrationPwr3[15] = 400;
		deviceConfig.calibrationPwr3[16] = 425;
		deviceConfig.calibrationPwr3[17] = 450;
		deviceConfig.calibrationPwr3[18] = 470;
		deviceConfig.calibrationPwr3[19] = 500;
		//CH4-980
		deviceConfig.calibrationPwr4[0] = 25;
		deviceConfig.calibrationPwr4[1] = 50;
		deviceConfig.calibrationPwr4[2] = 75;
		deviceConfig.calibrationPwr4[3] = 100;
		deviceConfig.calibrationPwr4[4] = 125;
		deviceConfig.calibrationPwr4[5] = 150;
		deviceConfig.calibrationPwr4[6] = 175;
		deviceConfig.calibrationPwr4[7] = 200;
		deviceConfig.calibrationPwr4[8] = 225;
		deviceConfig.calibrationPwr4[9] = 250;
		deviceConfig.calibrationPwr4[10] = 275;
		deviceConfig.calibrationPwr4[11] = 300;
		deviceConfig.calibrationPwr4[12] = 325;
		deviceConfig.calibrationPwr4[13] = 350;
		deviceConfig.calibrationPwr4[14] = 375;
		deviceConfig.calibrationPwr4[15] = 400;
		deviceConfig.calibrationPwr4[16] = 425;
		deviceConfig.calibrationPwr4[17] = 450;
		deviceConfig.calibrationPwr4[18] = 470;
		deviceConfig.calibrationPwr4[19] = 500;

		for(i = 0;i <= 19;i ++){//清空其他波长
			//deviceConfig.calibrationPwr1[i] = i;
			//deviceConfig.calibrationPwr2[i] = i;
			//deviceConfig.calibrationPwr3[i] = i;
			//deviceConfig.calibrationPwr4[i] = i;
			deviceConfig.calibrationPwr5[i] = i;
			deviceConfig.calibrationPwr6[i] = i;
			deviceConfig.calibrationPwr7[i] = i;
		}
#endif

		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
		deviceConfig.mfg_year = 2026;
		deviceConfig.mfg_month = 04;
		deviceConfig.mfg_day = 06;
			
		sprintf(deviceConfig.serialNumber, "XXXX-XXXX");
		deviceConfig.greenLedDc = CONFIG_GREEN_LED_DEFAULT_DC;
		deviceConfig.redLedDc = CONFIG_RED_LED_DEFAULT_DC;
		deviceConfig.blueLedDc = CONFIG_BLUE_LED_DEFAULT_DC;
		deviceConfig.redAimGain = CONFIG_LASER_RAIM_DEFAULT_GAIN;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
		deviceConfig.normalOpenInterLock = 1;//默认常开联锁 
		deviceConfig.laserDiodeA_Temp = CONFIG_LASER_A_DIODE_SET_TEMP;
		deviceConfig.laserDiodeB_Temp = CONFIG_LASER_B_DIODE_SET_TEMP;
		saveDeviceConfig();
	}
	else{
		printf("%s,%d,%s:load device config done...\n",__FILE__, __LINE__, __func__);
	}
}
void saveDeviceConfig(void){//将配置写入EPROM
	uint32_t crc32_cfg;
	epromWrite(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//写入EPROM	
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	epromWriteDword(CONFIG_EPROM_CFG_CRC, &crc32_cfg);//写入校验值
	printf("%s,%d,%s:save device config to eprom done...(CFG CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_cfg);
}
void saveCalibrationTable(uint8_t channel){//储存选定通道的功率校准表
	uint32_t crc32_cfg;
	uint8_t *memberAddr;//成员地址
	uint8_t *structAddr;//结构体地址
	uint32_t writeSize, epromWriteAddr;
	structAddr = (uint8_t*)&deviceConfig;
	switch(channel){
		case LASER_DAC_CHANNEL_CH0:{	
			memberAddr = (uint8_t*)deviceConfig.calibrationPwr0;
			writeSize = sizeof(deviceConfig.calibrationPwr0);
			break;
		}
		case LASER_DAC_CHANNEL_CH1:{
			memberAddr = (uint8_t*)deviceConfig.calibrationPwr1;
			writeSize = sizeof(deviceConfig.calibrationPwr1);
			break;
		}
		case LASER_DAC_CHANNEL_CH2:{
			memberAddr = (uint8_t*)deviceConfig.calibrationPwr2;
			writeSize = sizeof(deviceConfig.calibrationPwr2);
			break;
		}
		case LASER_DAC_CHANNEL_CH3:{
			memberAddr = (uint8_t*)deviceConfig.calibrationPwr3;
			writeSize = sizeof(deviceConfig.calibrationPwr3);
			break;
		}
		case LASER_DAC_CHANNEL_CH4:{
			memberAddr = (uint8_t*)deviceConfig.calibrationPwr4;
			writeSize = sizeof(deviceConfig.calibrationPwr4);
			break;
		}
		case LASER_DAC_CHANNEL_CH5:{
			memberAddr = (uint8_t*)deviceConfig.calibrationPwr5;
			writeSize = sizeof(deviceConfig.calibrationPwr5);
			break;
		}
		case LASER_DAC_CHANNEL_CH6:{
			memberAddr = (uint8_t*)deviceConfig.calibrationPwr6;
			writeSize = sizeof(deviceConfig.calibrationPwr6);
			break;
		}
		case LASER_DAC_CHANNEL_CH7:{
			memberAddr = (uint8_t*)deviceConfig.calibrationPwr7;
			writeSize = sizeof(deviceConfig.calibrationPwr7);
			break;
		}
		default:break;
	}
	epromWriteAddr = CONFIG_EPROM_CONFIG_START + structAddr - memberAddr;//计算EPROM
	epromWrite(epromWriteAddr, memberAddr, writeSize);//写入EPROM	
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	epromWriteDword(CONFIG_EPROM_CFG_CRC, &crc32_cfg);//写入校验值
	printf("%s,%d,%s:save laser channle:%d calibration table to eprom done...(CRC:0x%08X)\n",__FILE__, __LINE__, __func__, channel,crc32_cfg);
}


