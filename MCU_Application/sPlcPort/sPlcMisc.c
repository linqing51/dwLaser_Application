#include "sPlc.h"
#include "boardConfig.h"
#include "appConfig.h"
#include "usbh_core.h"
/*****************************************************************************/
static int16_t FanSpeed = -1;
/*****************************************************************************/
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
	uint32_t crc32_eprom_cfg, crc32_cfg;
	epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//从EPROM载入设备配置
	epromReadDword(CONFIG_EPROM_CFG_CRC, &crc32_eprom_cfg);
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	if(crc32_eprom_cfg != crc32_cfg){//校验码错误使用默认配置
		printf("%s,%d,%s:load device config crc fail!!!\n",__FILE__, __LINE__, __func__);
		printf("%s,%d,%s:using default device config!\n",__FILE__, __LINE__, __func__);
		
#if defined(MODLE_M1470_640_10_15_02_D200_22_G5W_PK)//1470 V1
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 28;
		deviceConfig.calibrationPwr0[2] = 48;
		deviceConfig.calibrationPwr0[3] = 68;
		deviceConfig.calibrationPwr0[4] = 87;
		deviceConfig.calibrationPwr0[5] = 105;
		deviceConfig.calibrationPwr0[6] = 120;
		deviceConfig.calibrationPwr0[7] = 133;
		deviceConfig.calibrationPwr0[8] = 144;
		deviceConfig.calibrationPwr0[9] = 153;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;		
#endif	
#if defined(MODLE_M1470_980_640_10_15_35_05_D200_22_G5W_PK) //1470-980 V1
		//1470nm
		deviceConfig.calibrationPwr0[0] = 6;
		deviceConfig.calibrationPwr0[1] = 21;
		deviceConfig.calibrationPwr0[2] = 36;
		deviceConfig.calibrationPwr0[3] = 52;
		deviceConfig.calibrationPwr0[4] = 68;
		deviceConfig.calibrationPwr0[5] = 85;
		deviceConfig.calibrationPwr0[6] = 99;
		deviceConfig.calibrationPwr0[7] = 113;
		deviceConfig.calibrationPwr0[8] = 125;
		deviceConfig.calibrationPwr0[9] = 150;
		//980nm
		deviceConfig.calibrationPwr1[0] = 9;
		deviceConfig.calibrationPwr1[1] = 27;
		deviceConfig.calibrationPwr1[2] = 45;
		deviceConfig.calibrationPwr1[3] = 62;
		deviceConfig.calibrationPwr1[4] = 79;
		deviceConfig.calibrationPwr1[5] = 96;
		deviceConfig.calibrationPwr1[6] = 112;
		deviceConfig.calibrationPwr1[7] = 127;
		deviceConfig.calibrationPwr1[8] = 140;
		deviceConfig.calibrationPwr1[9] = 150;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
#endif

#if defined(MODLE_M1470_980_640_10_15_15_02_D200_22_G5W_PK)//1470-980-650 V2
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 28;
		deviceConfig.calibrationPwr0[2] = 48;
		deviceConfig.calibrationPwr0[3] = 68;
		deviceConfig.calibrationPwr0[4] = 87;
		deviceConfig.calibrationPwr0[5] = 105;
		deviceConfig.calibrationPwr0[6] = 120;
		deviceConfig.calibrationPwr0[7] = 133;
		deviceConfig.calibrationPwr0[8] = 144;
		deviceConfig.calibrationPwr0[9] = 153;
	
		deviceConfig.calibrationPwr1[0] = 9;
		deviceConfig.calibrationPwr1[1] = 28;
		deviceConfig.calibrationPwr1[2] = 48;
		deviceConfig.calibrationPwr1[3] = 68;
		deviceConfig.calibrationPwr1[4] = 87;
		deviceConfig.calibrationPwr1[5] = 105;
		deviceConfig.calibrationPwr1[6] = 120;
		deviceConfig.calibrationPwr1[7] = 133;
		deviceConfig.calibrationPwr1[8] = 144;
		deviceConfig.calibrationPwr1[9] = 153;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
#endif

#if defined(MODLE_M1470_980_640_10_15_35_05_D200_22_G5W_PK)
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 28;
		deviceConfig.calibrationPwr0[2] = 48;
		deviceConfig.calibrationPwr0[3] = 68;
		deviceConfig.calibrationPwr0[4] = 87;
		deviceConfig.calibrationPwr0[5] = 105;
		deviceConfig.calibrationPwr0[6] = 120;
		deviceConfig.calibrationPwr0[7] = 133;
		deviceConfig.calibrationPwr0[8] = 144;
		deviceConfig.calibrationPwr0[9] = 153;
	
		deviceConfig.calibrationPwr1[0] = 9;
		deviceConfig.calibrationPwr1[1] = 28;
		deviceConfig.calibrationPwr1[2] = 48;
		deviceConfig.calibrationPwr1[3] = 68;
		deviceConfig.calibrationPwr1[4] = 87;
		deviceConfig.calibrationPwr1[5] = 105;
		deviceConfig.calibrationPwr1[6] = 120;
		deviceConfig.calibrationPwr1[7] = 133;
		deviceConfig.calibrationPwr1[8] = 144;
		deviceConfig.calibrationPwr1[9] = 153;
#endif

#if defined(MODLE_M12_1920_10_400S)
		deviceConfig.calibrationPwr0[0] = 6;
		deviceConfig.calibrationPwr0[1] = 20;
		deviceConfig.calibrationPwr0[2] = 32;
		deviceConfig.calibrationPwr0[3] = 45;
		deviceConfig.calibrationPwr0[4] = 56;
		deviceConfig.calibrationPwr0[5] = 66;
		deviceConfig.calibrationPwr0[6] = 72;
		deviceConfig.calibrationPwr0[7] = 81;
		deviceConfig.calibrationPwr0[8] = 87;
		deviceConfig.calibrationPwr0[9] = 100;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
#endif		

		deviceConfig.mfg_year = 2025;
		deviceConfig.mfg_month = 10;
		deviceConfig.mfg_day = 26;
			
		sprintf(deviceConfig.serialNumber, "XXXX-XXXX");
		deviceConfig.greenLedDc = CONFIG_GREEN_LED_DEFAULT_DC;
		deviceConfig.redLedDc = CONFIG_RED_LED_DEFAULT_DC;
		deviceConfig.blueLedDc = CONFIG_BLUE_LED_DEFAULT_DC;
		deviceConfig.redAimGain = CONFIG_LASER_RAIM_DEFAULT_GAIN;
		deviceConfig.fiberDetect = CONFIG_FIBER_PD_THRESHOLD;
		deviceConfig.normalOpenInterLock = 1;//默认常开联锁 
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



