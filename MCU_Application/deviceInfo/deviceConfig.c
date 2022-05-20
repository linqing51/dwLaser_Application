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




