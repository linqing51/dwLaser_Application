#include "deviceConfig.h"
/*****************************************************************************/
deviceConfig_t deviceConfig;
deviceLogInfo_t deviceLogInfo;
uint32_t	UniqueId[3];//���������к� 
/*****************************************************************************/
uint16_t cpuGetFlashSize(void){//��ȡ��������������
   return *(volatile uint16_t*)(0x1FFF7A22);
}

void readStm32UniqueID(void){//��ȡ������Ψһ���к�        
    UniqueId[0] = *(volatile uint32_t*)(0x1FFF7A10);
    UniqueId[1] = *(volatile uint32_t*)(0x1FFF7A14);
    UniqueId[2] = *(volatile uint32_t*)(0x1FFF7A18);
}




