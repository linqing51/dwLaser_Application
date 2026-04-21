#include "dcHmiApp.h"
#include "usbh_hid.h"
/*****************************************************************************/
extern ApplicationTypeDef Appli_state;
/*****************************************************************************/
void wfswLoop(USBH_HandleTypeDef *phost){//无线脚踏轮询
	HID_KEYBD_Info_TypeDef *k_pinfo;
  char c;
	if(Appli_state == APPLICATION_READY){//判断适配器是否插入
		if(isLegalUsbDev(phost)){		
			if(LDB(SPCOIL_WFSWITCH_PLUG)){
				printf("%s,%d,%s:wireless footswich plug......\n",__FILE__, __LINE__, __func__);
				SSET(SPCOIL_WFSWITCH_PLUG);
			}
			k_pinfo = USBH_HID_GetKeybdInfo(phost); 	
			if(k_pinfo != NULL){
				c = USBH_HID_GetASCIICode(k_pinfo);
				if(c == '1'){//凯昆脚踏默认为数字1
					printf("%s,%d,%s:wireless footswich press......\n",__FILE__, __LINE__, __func__);
					SSET(SPCOIL_WFSWITCH_NO);
				}
				if(c == 0x0){
					printf("%s,%d,%s:wireless footswich release......\n",__FILE__, __LINE__, __func__);		
					RRES(SPCOIL_WFSWITCH_NO);
				}		
			}
		}
		else{
#if CONFIG_DEBUG_WSW == 1
			printf("%s,%d,%s:inlega footswitch usb device......!\n",__FILE__, __LINE__, __func__);
#endif
		}
	}
	else{
		if(LD(SPCOIL_WFSWITCH_PLUG)){
			RRES(SPCOIL_WFSWITCH_PLUG);
			RRES(SPCOIL_WFSWITCH_NO);
			printf("%s,%d,%s:wireless footswich unplug......\n",__FILE__, __LINE__, __func__);
		}	
	}
}




