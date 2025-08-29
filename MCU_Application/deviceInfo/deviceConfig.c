#include "sPlc.h"
#include "boardConfig.h"
#include "deviceConfig.h"
/*****************************************************************************/
deviceConfig_t deviceConfig;
deviceLogInfo_t deviceLogInfo;
uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
uint16_t cpuGetFlashSize(void){//获取处理器程序容量
   return *(volatile uint16_t*)(0x1FFF7A22);
}

void readStm32UniqueID(void){//获取处理器唯一序列号        
    UniqueId[0] = *(volatile uint32_t*)(0x1FFF7A10);
    UniqueId[1] = *(volatile uint32_t*)(0x1FFF7A14);
    UniqueId[2] = *(volatile uint32_t*)(0x1FFF7A18);
}

void loadDeviceConfig(void){//从EPROM载入配置文件
	uint32_t crc32_eprom_cfg, crc32_cfg;
	epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//从EPROM载入设备配置
	epromReadDword(CONFIG_EPROM_CFG_CRC, &crc32_eprom_cfg);
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	if(crc32_eprom_cfg != crc32_cfg){//校验码错误使用默认配置
		printf("%s,%d,%s:load device config crc fail!!!\n",__FILE__, __LINE__, __func__);
		printf("%s,%d,%s:using default device config!\n",__FILE__, __LINE__, __func__);
#if defined(APP_CONFIG_WAVE_1470_650)
		//大族模块默认功率表 1470
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
		//大族模块默认功率表 980
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

#if defined(APP_CONFIG_WAVE_1940_650)
		//吉光模块默认功率表 1940
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
		deviceConfig.mfg_month = 6;
		deviceConfig.mfg_day = 8;
			
		sprintf(deviceConfig.serialNumber, "XXXX-XXXX");
		deviceConfig.greenLedDc = CONFIG_GREEN_LED_DEFAULT_DC;
		deviceConfig.redLedDc = CONFIG_RED_LED_DEFAULT_DC;
		deviceConfig.blueLedDc = CONFIG_BLUE_LED_DEFAULT_DC;
		deviceConfig.aimGain = CONFIG_AIM_DEFAULT_GAIN;
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

