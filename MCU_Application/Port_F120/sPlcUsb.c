#include "sPlcUsb.h"
/*****************************************************************************/
#if CONFIG_SPLC_USING_CH376 == 1
static void sPlcUsbDiskConnectPoll(void){//USB DISK������ѯ ����200mS	
	T10MS(T10MS_USBDISK_CONNECT_DELAY, true, 20);//������ʱ����ʱ
	if(LD(T_10MS_START * 16U + T10MS_USBDISK_CONNECT_DELAY)){
		if(CH376DiskConnect() == USB_INT_SUCCESS){//���U���Ƿ�����,�ȴ�U�̲���
			SET(SPCOIL_USBDISK_CONNECT_DONE);
		}
		else{
			RES(SPCOIL_USBDISK_CONNECT_DONE);
		}
		T10MS(T10MS_USBDISK_CONNECT_DELAY, false, 20);
	}
}
static void sPlcUsbDiskMountPoll(void){//USB DISK������ѯ ����100mS
	uint8_t i;
	for(i = 0;i < 5;i ++){
		T10MS(T10MS_USBDISK_MOUNT_DELAY, true, 10);//������ʱ����ʱ100mS
		if(LD(T_10MS_START * 16 + T10MS_USBDISK_MOUNT_DELAY)){
			if(CH376DiskMount() == USB_INT_SUCCESS){ 
				SET(SPCOIL_USBDISK_MOUNT_DONE);
			}
			else{
				RES(SPCOIL_USBDISK_MOUNT_DONE);
			}
			T10MS(T10MS_USBDISK_MOUNT_DELAY, false, 5);//������ʱ����ʱ100mS
		}
	}
}
static void sPlcUsbDiskRemove(void){//USB DISK��ȫ�Ƴ�
	uint8_t s;
	if(LD(SPCOIL_USBDISK_CONNECT_DONE) && LDB(SPCOIL_USBDISK_REMOVE_DOING)){
		RES(SPCOIL_USBDISK_REMOVE_DONE);
		SET(SPCOIL_USBDISK_REMOVE_DOING);
		s = CH376SendCmdDatWaitInt(CMD1H_SET_CONFIG, 0);//ȡ������,�ᵼ�ºܶ�U�̵�LED����
		RES(SPCOIL_USBDISK_REMOVE_DOING);
	}
	T10MS(T10MS_USBDISK_REMOVE_DELAY, true, 50);//������ʱ����ʱ100mS
	if(LD(T_10MS_START * 16 + T10MS_USBDISK_REMOVE_DELAY)){
		if(s == USB_INT_SUCCESS){
			SET(SPCOIL_USBDISK_REMOVE_DONE);
			RES(SPCOIL_USBDISK_CONNECT_DONE);
			RES(SPCOIL_USBDISK_MOUNT_DONE);
		}
		else{
			RES(SPCOIL_USBDISK_REMOVE_DONE);
		}
		RES(SPCOIL_USBDISK_REMOVE_DOING);
		RES(SPCOIL_USBDISK_REMOVE_REQ);
		T10MS(T10MS_USBDISK_REMOVE_DELAY, false, 50);//������ʱ����ʱ100mS
	}
}
	
void sPlcUsbPoll(void){//USB ������ѯ
	if(LD(SPCOIL_USBHOST_CONNECT_REQ)){
		sPlcUsbDiskConnectPoll();
	}
	if(LD(SPCOIL_USBDISK_MOUNT_REQ)){
		sPlcUsbDiskMountPoll();
	}
	if(LD(SPCOIL_USBDISK_REMOVE_REQ)){
		sPlcUsbDiskRemove();
	}
}	
#endif