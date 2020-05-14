#include "dcHmiNotifyButton.h"
//��ť�ؼ�֪ͨ����ť״̬�ı�(�����GetControlValue)ʱ��ִ�д˺���
//screen_id ����ID;control_id �ؼ�ID;state ��ť״̬��0����1����
void NotifyButton(uint16_t screen_id, uint16_t control_id, uint8_t state){ 
	//PASSCODE ��������ҳ��
	switch(screen_id){
		case GDDC_PAGE_PASSCODE:{//�ȴ���������
			switch(control_id){
				case GDDC_PAGE_PASSCODE_KEY_NUM1:{//����1
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3100;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0031;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3100;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0031;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(screen_id, 15, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM2:{//����2
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3200;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0032;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3200;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0032;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(screen_id, 15, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM3:{//����3
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3300;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0033;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3300;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0033;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					SetTextValue(screen_id, 15, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));					
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM4:{//����4
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3400;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0034;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3400;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0034;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));	
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM5:{//����5
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3500;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0035;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3500;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0035;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM6:{//����6
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3600;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0036;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3600;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0036;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));		
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM7:{//����7
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3700;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0037;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3700;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0037;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM8:{//����8
						if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3800;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0038;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3800;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0038;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM9:{//����9
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3900;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0039;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3900;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0039;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM0:{//����0
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3000;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0030;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3000;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0030;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_CANCEL:{//����CANCEL
					CLR(EM_DC_NEW_PASSCODE0);//�������������
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ����
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_BACKSPACE:{//����BACKSPACE
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 4){
						NVRAM0[EM_DC_NEW_PASSCODE1] &= 0xFF00;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x3;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] &= 0x00FF;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE0] &= 0xFF00;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x1;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] &= 0x00FF;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x0;	
					}
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_CHANGEPASSCODE:{//����CHANGEPASSCODE
					if((NVRAM0[EM_DC_NEW_PASSCODE0] == NVRAM0[DM_DC_OLD_PASSCODE0]) && (NVRAM0[EM_DC_NEW_PASSCODE1] == NVRAM0[DM_DC_OLD_PASSCODE1])){
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_NEW0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_NEW_PASSCODE;
						SetScreen(NVRAM0[EM_DC_PAGE]);	
					}
					else if((NVRAM0[EM_DC_NEW_PASSCODE0] == NVRAM0[EM_DC_DEFAULT_PASSCODE0]) && (NVRAM0[EM_DC_NEW_PASSCODE1] == NVRAM0[EM_DC_DEFAULT_PASSCODE1])){
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_NEW0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_NEW_PASSCODE;
						SetScreen(NVRAM0[EM_DC_PAGE]);
					}
					CLR(EM_DC_NEW_PASSCODE0);//�������������
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ����
					SetTextValue(screen_id, 15 , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_ENTER:{//����ENTER
					if((NVRAM0[EM_DC_NEW_PASSCODE0] == NVRAM0[EM_DC_DEFAULT_PASSCODE0]) && (NVRAM0[EM_DC_NEW_PASSCODE1] == NVRAM0[EM_DC_DEFAULT_PASSCODE1])){
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
						SET(R_ENGINEER_MODE);
						updateStandbyDisplay();
						standbyTouchEnable(true);
						standbyDebugInfoVisiable(true);						
					}else if((NVRAM0[EM_DC_NEW_PASSCODE0] == NVRAM0[DM_DC_OLD_PASSCODE0]) && (NVRAM0[EM_DC_NEW_PASSCODE1] == NVRAM0[DM_DC_OLD_PASSCODE1])){
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
						RES(R_ENGINEER_MODE);
						updateStandbyDisplay();
						standbyTouchEnable(true);
						standbyDebugInfoVisiable(false);
					}		

					CLR(EM_DC_NEW_PASSCODE0);//�������������
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ���� 
					SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_NEW_PASSCODE:{//����������ҳ��
			switch(control_id){
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM1:{//����1
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3100;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0031;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3100;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0031;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM2:{//����2	
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3200;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0032;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3200;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0032;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM3:{//����3
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3300;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0033;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3300;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0033;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM4:{//����4
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3400;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0034;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3400;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0034;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM5:{//����5
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3500;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0035;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3500;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0035;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM6:{//����6
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3600;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0036;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3600;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0036;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM7:{//����7
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3700;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0037;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3700;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0037;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM8:{//����8
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3800;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0038;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3800;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0038;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM9:{//����9
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3900;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0039;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3900;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0039;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));	
					break;	
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM0:{//����0
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3000;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0030;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3000;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0030;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_CANCEL:{
					CLR(EM_DC_NEW_PASSCODE0);
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ���� 
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;	
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_BACKSPACE:{
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 4){
						NVRAM0[EM_DC_NEW_PASSCODE1] &= 0xFF00;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x3;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] &= 0x00FF;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE0] &= 0xFF00;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x1;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] &= 0x00FF;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x0;	
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_SAVE:{
					if((NVRAM0[EM_DC_PASSCODE_INDEX] >= 4) && (NVRAM0[EM_DC_NEW_PASSCODE0] != 0x0000) && (NVRAM0[EM_DC_NEW_PASSCODE0] != 0x0000)){
						NVRAM0[DM_DC_OLD_PASSCODE0] = NVRAM0[EM_DC_NEW_PASSCODE0];
						NVRAM0[DM_DC_OLD_PASSCODE1] = NVRAM0[EM_DC_NEW_PASSCODE1];
						NVSAV();
						CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ���� 
						CLR(EM_DC_NEW_PASSCODE0);
						CLR(EM_DC_NEW_PASSCODE1);
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_INPUT;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
						SetScreen(NVRAM0[EM_DC_PAGE]);
					}
					else{
						CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ���� 
						CLR(EM_DC_NEW_PASSCODE0);
						CLR(EM_DC_NEW_PASSCODE1);
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_NEW0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_NEW_PASSCODE;
					}
					SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_BACK:{//�����������޸�
					CLR(EM_DC_NEW_PASSCODE0);
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ���� 
					NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_INPUT;
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
					SetTextValue(screen_id, GDDC_PAGE_NEWPASSCODE_KEY_BACK , (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
					SetScreen(NVRAM0[EM_DC_PAGE]);
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_STANDBY_CW:{//������STANDBY CW
			switch(control_id){				
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASERPOWER_CH0){
							NVRAM0[EM_LASER_POWER_CH0]++;
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_CW);
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));						
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASERPOWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_CW);						
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
						}
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASERPOWER_CH1){
							ADDS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_CW);
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASERPOWER_CH1){
							DECS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_CW);
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] > 0){
							DECS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] < (CONFIG_HMI_SCHEME_NUM - 1)){
							ADDS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_STANDBY:{
					if(state){
						SET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					else{
						SET(R_STANDBY_KEY_STNADBY_UP);
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH0:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH1:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH1;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_BOTH:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_ALL;
					}
					break;
				}
#endif
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_GP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_GP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SIGNAL;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_DERMA:{	
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_DERMA;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_RESET:{
					if(state){
						LaserRelease_TotalTime = 0;
						LaserRelease_TotalEnergy = 0;
						updateReleaseTimeEnergy();
					}
					break;
				}	
				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//����SCHEME
					if(state){
						SET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_STANDBY_SP:{//������STANDBY SP
			switch(control_id){
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASERPOWER_CH0){
							ADDS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];	
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_SP);
							SetProgressValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));						
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASERPOWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_SP);
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
						}
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASERPOWER_CH1){
							ADDS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_SP);
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASERPOWER_CH1){
							DECS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_SP);
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
				case GDDC_PAGE_STANDBY_SP_KEY_POSWIDTH_ADD:{	
					if(state){//DOWN
						SET(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_SP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_SP_POSWIDTH]);
						updatePosWidthDisplay(LASER_MODE_SP);
					}
					else{
						RES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
 				case GDDC_PAGE_STANDBY_SP_KEY_POSWIDTH_DEC:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);	
						NVRAM0[EM_LASER_SP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_SP_POSWIDTH]);
						updatePosWidthDisplay(LASER_MODE_SP);
					}
					else{
						RES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] > 0){
							DECS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] < (CONFIG_HMI_SCHEME_NUM - 1)){
							ADDS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_STANDBY:{
					if(state){
						//��ֹSTANDBY����
						SET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					else{
						SET(R_STANDBY_KEY_STNADBY_UP);
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH0:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH1:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH1;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_BOTH:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_ALL;
					}
					break;
				}
#endif				
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_GP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_GP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SIGNAL;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_DERMA:{	
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_DERMA;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_RESET:{
					if(state){
						LaserRelease_TotalTime = 0;
						LaserRelease_TotalEnergy = 0;
						updateReleaseTimeEnergy();
					}
					break;
				}	
				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//����SCHEME
					if(state){
						SET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_STANDBY_MP:{//������STANDBY MP
			switch(control_id){				
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASERPOWER_CH0){
							ADDS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_MP);
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));						
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASERPOWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_MP);
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
						}
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASERPOWER_CH1){
							ADDS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_MP);
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASERPOWER_CH1){
							DECS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_MP);						
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
				case GDDC_PAGE_STANDBY_MP_KEY_POSWIDTH_ADD:{	
					if(state){//DOWN
						SET(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_MP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_MP_POSWIDTH]);
						updatePosWidthDisplay(LASER_MODE_MP);
					}
					else{
						RES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_MP_KEY_POSWIDTH_DEC:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						NVRAM0[EM_LASER_MP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_MP_POSWIDTH]);
						updatePosWidthDisplay(LASER_MODE_MP);
					}
					else{
						RES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);	
						T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_MP_KEY_NEGWIDTH_ADD:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_MP_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_MP_NEGWIDTH]);
						updateNegWidthDisplay(LASER_MODE_MP);
					}
					else{
						RES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_MP_KEY_NEGWIDTH_DEC:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						NVRAM0[EM_LASER_MP_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_MP_NEGWIDTH]);
						updateNegWidthDisplay(LASER_MODE_MP);
					}
					else{
						RES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] > 0){
							DECS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] < (CONFIG_HMI_SCHEME_NUM - 1)){
							ADDS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_STANDBY:{
					if(state){
						SET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					else{
						SET(R_STANDBY_KEY_STNADBY_UP);
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH0:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH1:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH1;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_BOTH:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_ALL;
					}
					break;
				}	
#endif
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_GP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_GP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SIGNAL;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_DERMA:{	
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_DERMA;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_RESET:{
					if(state){
						LaserRelease_TotalTime = 0;
						LaserRelease_TotalEnergy = 0;
						updateReleaseTimeEnergy();
					}
					break;
				}	
				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//����SCHEME
					if(state){
						SET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_STANDBY_GP:{//������STANDBY GP
			switch(control_id){				
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASERPOWER_CH0){
							ADDS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_GP);
							SetProgressValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));						
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASERPOWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_GP);						
							SetProgressValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
						}
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASERPOWER_CH1){
							ADDS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_GP);
							SetProgressValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASERPOWER_CH1){
							DECS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_GP);
							SetProgressValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
				case GDDC_PAGE_STANDBY_GP_KEY_POSWIDTH_ADD:{	
					if(state){//DOWN
						SET(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_GP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_GP_POSWIDTH]);
						updatePosWidthDisplay(LASER_MODE_GP);
					}
					else{
						RES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_GP_KEY_POSWIDTH_DEC:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						NVRAM0[EM_LASER_GP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_GP_POSWIDTH]);
						updatePosWidthDisplay(LASER_MODE_GP);
					}
					else{
						RES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_GP_KEY_NEGWIDTH_ADD:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_GP_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_GP_NEGWIDTH]);
						updateNegWidthDisplay(LASER_MODE_GP);
					}
					else{
						RES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_GP_KEY_NEGWIDTH_DEC:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						NVRAM0[EM_LASER_GP_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_GP_NEGWIDTH]);
						updateNegWidthDisplay(LASER_MODE_GP);
					}
					else{
						RES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_GP_KEY_TIMES_ADD:{
					if(state){
						SET(R_STANDBY_KEY_TIMES_ADD_DOWN);
						if(NVRAM0[EM_LASER_GP_TIMES] < CONFIG_MAX_LASER_TIMES){
							NVRAM0[EM_LASER_GP_TIMES] ++;
						}
						else{
							NVRAM0[EM_LASER_GP_TIMES] = CONFIG_MAX_LASER_TIMES;
						}
						updateTimesDisplay();
					}
					else{
						RES(R_STANDBY_KEY_TIMES_ADD_DOWN);
						T10MS(T10MS_TIMES_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_GP_KEY_TIMES_DEC:{
					if(state){
						SET(R_STANDBY_KEY_TIMES_DEC_DOWN);
						if(NVRAM0[EM_LASER_GP_TIMES] > CONFIG_MIN_LASER_TIMES){
							NVRAM0[EM_LASER_GP_TIMES] -= 1;//-1
						}
						else{
							NVRAM0[EM_LASER_GP_TIMES]  = CONFIG_MIN_LASER_TIMES;
						}
						updateTimesDisplay();
					}
					else{
						RES(R_STANDBY_KEY_TIMES_DEC_DOWN);
						T10MS(T10MS_TIMES_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_GP_KEY_GROUP_OFF_ADD:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_GROUP_OFF_ADD_DOWN);
						NVRAM0[EM_LASER_GP_GROUP_OFF] = pulseWidthAdd(NVRAM0[EM_LASER_GP_GROUP_OFF]);
						updateGroupOffDisplay();
					}
					else{
						RES(R_STANDBY_KEY_GROUP_OFF_ADD_DOWN);
						T10MS(T10MS_GROUP_OFF_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_GP_KEY_GROUP_OFF_DEC:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_GROUP_OFF_DEC_DOWN);
						NVRAM0[EM_LASER_GP_GROUP_OFF] = pulseWidthDec(NVRAM0[EM_LASER_GP_GROUP_OFF]);
						updateGroupOffDisplay();
					}
					else{
						RES(R_STANDBY_KEY_GROUP_OFF_DEC_DOWN);
						T10MS(T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] > 0){
							DECS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] < (CONFIG_HMI_SCHEME_NUM - 1)){
							ADDS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_STANDBY:{
					if(state){
						SET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					else{
						SET(R_STANDBY_KEY_STNADBY_UP);
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH0:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1				
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH1:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH1;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_BOTH:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_ALL;
					}
					break;
				}	
#endif
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_GP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_GP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SIGNAL;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_DERMA:{	
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_DERMA;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_RESET:{
					if(state){
						LaserRelease_TotalTime = 0;
						LaserRelease_TotalEnergy = 0;
						updateReleaseTimeEnergy();
					}
					break;
				}	
				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//����SCHEME
					if(state){
						SET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_STANDBY_SIGNAL:{//������STANDBY EVLA SIGNAL
			switch(control_id){				
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASERPOWER_CH0){
							ADDS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_SIGNAL);
							SetProgressValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));						
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASERPOWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_SIGNAL);	
							SetProgressValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
						}
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASERPOWER_CH1){
							ADDS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_SIGNAL);
							SetProgressValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASERPOWER_CH1){
							DECS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_SIGNAL);
							SetProgressValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
				case GDDC_PAGE_STANDBY_SIGNAL_KEY_ENERGY_INTERVAL_ADD:{
					if(state){	
						if(NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] < CONFIG_MAX_LASER_ENERGY_INTERVAL){
							NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] += CONFIG_STEP_LASER_ENERGY_INTERVAL;
						}
						SetTextInt32(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_SIGNAL_TEXTDISPLAY_ENERGY_INTERVAL ,NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL], 1, 0);	
					}
					break;
				}
				case GDDC_PAGE_STANDBY_SIGNAL_KEY_ENERGY_INTERVAL_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] > CONFIG_MIN_LASER_ENERGY_INTERVAL){
							NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL] -= CONFIG_STEP_LASER_ENERGY_INTERVAL;
						}
						SetTextInt32(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_SIGNAL_TEXTDISPLAY_ENERGY_INTERVAL ,NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL], 1, 0);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST :{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] > 0){
							DECS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] < (CONFIG_HMI_SCHEME_NUM - 1)){
							ADDS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_STANDBY:{
					if(state){
						SET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					else{
						SET(R_STANDBY_KEY_STNADBY_UP);
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH0:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH1:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH1;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_BOTH:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_ALL;
					}
					break;
				}	
#endif
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_GP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_GP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SIGNAL;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_DERMA:{	
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_DERMA;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_RESET:{
					if(state){
						LaserRelease_TotalTime = 0;
						LaserRelease_TotalEnergy = 0;
						updateReleaseTimeEnergy();
					}
					break;
				}	
				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//����SCHEME
					if(state){
						SET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_STANDBY_DERMA:{//������STNADBY DERMA
			switch(control_id){	
				case GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_0MM5:{
					if(state){
						NVRAM0[EM_LASER_DERMA_SPOT_SIZE] = DERMA_SPOT_SIZE_0MM5;
						updateEnergyDensity();
					}
					break;
				}			
				case GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_1MM0:{
					if(state){					
						NVRAM0[EM_LASER_DERMA_SPOT_SIZE] = DERMA_SPOT_SIZE_1MM0;
						updateEnergyDensity();
					}
					break;
				}	
				case GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_2MM0:{
					if(state){
						NVRAM0[EM_LASER_DERMA_SPOT_SIZE] = DERMA_SPOT_SIZE_2MM0;
						updateEnergyDensity();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_3MM0:{
					if(state){
						NVRAM0[EM_LASER_DERMA_SPOT_SIZE] = DERMA_SPOT_SIZE_3MM0;
						updateEnergyDensity();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_DERMA_KEY_POSWIDTH_ADD:{	
					if(state){//DOWN
						SET(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_DERMA_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_DERMA_POSWIDTH]);
						updatePosWidthDisplay(LASER_MODE_DERMA);
					}
					else{
						RES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_DERMA_KEY_POSWIDTH_DEC:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						NVRAM0[EM_LASER_DERMA_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_DERMA_POSWIDTH]);//-1
						updatePosWidthDisplay(LASER_MODE_DERMA);
					}
					else{
						RES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_DERMA_KEY_NEGWIDTH_ADD:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_DERMA_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
						updateNegWidthDisplay(LASER_MODE_DERMA);
					}
					else{
						RES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_DERMA_KEY_NEGWIDTH_DEC:{
					if(state){//DOWN
						SET(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						NVRAM0[EM_LASER_DERMA_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
						updateNegWidthDisplay(LASER_MODE_DERMA);
					}
					else{
						RES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASERPOWER_CH0){
							ADDS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];					
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_DERMA);
							SetProgressValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));						
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASERPOWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_DERMA);
							SetProgressValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
						}
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASERPOWER_CH1){
							ADDS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH1, LASER_MODE_DERMA);
							SetProgressValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASERPOWER_CH1){
							DECS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
							updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_DERMA);
							SetProgressValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
						}
					}
					break;
				}
#endif
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST :{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] > 0){
							DECS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//ѡ����һ������
					if(state){
						if(NVRAM0[DM_SCHEME_NUM] < (CONFIG_HMI_SCHEME_NUM - 1)){
							ADDS1(DM_SCHEME_NUM);//+1
							loadScheme();//DM->EM
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_STANDBY:{
					if(state){
						SET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					else{
						SET(R_STANDBY_KEY_STNADBY_UP);
					}
					break;
				}
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH0:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH1:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH1;
					}
					break;
				}
#endif
#if CONFIG_USING_DUAL_WAVE == 1
				case GDDC_PAGE_STANDBY_KEY_SELECT_BOTH:{
					if(state){
						NVRAM0[EM_LASER_SELECT] = LASER_SELECT_ALL;
					}
					break;
				}
#endif				
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_GP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_GP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SP;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SIGNAL;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_DERMA:{	
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_DERMA;
						updateStandbyDisplay();
						standbyTouchEnable(true);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_RESET:{
					if(state){
						LaserRelease_TotalTime = 0;
						LaserRelease_TotalEnergy = 0;
						updateReleaseTimeEnergy();
					}
					break;
				}	
				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//����SCHEME
					if(state){
						SET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_OPTION:{//ѡ��ҳ��
			switch(control_id){
				case GDDC_PAGE_OPTION_KEY_TONE:{
					if(state){
						SET(MR_BEEM_TONE);
					}
					else{
						RES(MR_BEEM_TONE);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_AIM_BRG_ADD:{
					if(state){
						if(NVRAM0[DM_AIM_BRG] < CONFIG_MAX_AIM_BRG){
							NVRAM0[DM_AIM_BRG] += 1;//+1
							SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//���½�����
						}
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_AIM_BRG_DEC:{
					if(state){
						if(NVRAM0[DM_AIM_BRG] > CONFIG_MIN_AIM_BRG){
							NVRAM0[DM_AIM_BRG] -= 1;//-1	
							SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//���½�����
						}
					}
					break;					
				}
				case GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_ADD:{
					if(state){
						if(NVRAM0[DM_BEEM_VOLUME] < CONFIG_MAX_BEEM_VOLUME){
							NVRAM0[DM_BEEM_VOLUME] += 1;
							SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
							SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//���½�����
						}
					}
					break;					
				}
				case GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_DEC:{
					if(state){
						if(NVRAM0[DM_BEEM_VOLUME] > CONFIG_MIN_BEEM_VOLUME){
							NVRAM0[DM_BEEM_VOLUME] -= 1;
							SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
							SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//���½�����
						}
					}
					break;					
				}
				case GDDC_PAGE_OPTION_KEY_LCD_BRG_ADD:{
					if(state){
						if(NVRAM0[DM_LCD_BRG] < CONFIG_MAX_LCD_BRG){
							NVRAM0[DM_LCD_BRG] += 1;
							SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG , NVRAM0[DM_LCD_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);
							SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
						}
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_LCD_BRG_DEC:{
					if(state){
						if(NVRAM0[DM_LCD_BRG] > CONFIG_MIN_LCD_BRG){
							NVRAM0[DM_LCD_BRG] -= 1;
							SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG , NVRAM0[DM_LCD_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);
							SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
						}
					}
					break;					
				}
				case GDDC_PAGE_OPTION_KEY_ENTER_INFORMATION:{//��Ϣ
					if(state){
						SET(R_OPTION_KEY_ENTER_INFORMATION_DOWN);
					}
					break;							
				}
				case GDDC_PAGE_OPTION_KEY_ENTER_CORRECTION:{//����У��
					if(state){
						SET(R_OPTION_KEY_ENTER_CORRECTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_ENTER_OK:{//OK
					if(state){
						SET(R_OPTION_KEY_ENTER_OK_DOWN);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON:{
					if(state){
						SET(MR_FOOSWITCH_HAND_SWITCH);
					}
					else{
						RES(MR_FOOSWITCH_HAND_SWITCH);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER:{
					if(state){
						SET(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_RESTORE:{//�ָ�Ĭ��ֵ
					if(state){
						optionKeyEnable(false);//��������
						loadDefault();
						updateOptionDisplay();//����Option��ʾ
						SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));//���±�������
						optionKeyEnable(true);//��˵����
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_INFORMATION:{
			switch(control_id){
				case GDDC_PAGE_INFORMATION_KEY_ENTER_OK:{
					if(state){
						SET(R_INFORMATION_KEY_OK_DOWN);
					}
					else{
						SET(R_INFORMATION_KEY_OK_UP);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_SCHEME_0:{
			switch(control_id){
				case GDDC_PAGE_SCHEME_KEY_RENAME:{
					if(state){
						SET(R_SCHEME_KEY_RENAME_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_OK:{
					if(state){
						SET(R_SCHEME_KEY_OK_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_CANCEL:{
					if(state){
						SET(R_SCHEME_KEY_CANCEL_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_0:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 0){
							NVRAM0[EM_SCHEME_NUM_TMP] = 0;
							updateSchemeInfo(0);
						}
					}
					break;
				}	
				case GDDC_PAGE_SCHEME_KEY_SELECT_1:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 1){
							NVRAM0[EM_SCHEME_NUM_TMP] = 1;
							updateSchemeInfo(1);
						}
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_2:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 2){
							NVRAM0[EM_SCHEME_NUM_TMP] = 2;
							updateSchemeInfo(2);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_3:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 3){
							NVRAM0[EM_SCHEME_NUM_TMP] = 3;
							updateSchemeInfo(3);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_4:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 4){
							NVRAM0[EM_SCHEME_NUM_TMP] = 4;
							updateSchemeInfo(4);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_5:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 5){
							NVRAM0[EM_SCHEME_NUM_TMP] = 5;
							updateSchemeInfo(5);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_6:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 6){
							NVRAM0[EM_SCHEME_NUM_TMP] = 6;
							updateSchemeInfo(6);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_7:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 7){
							NVRAM0[EM_SCHEME_NUM_TMP] = 7;
							updateSchemeInfo(7);
						}
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_8:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 8){
							NVRAM0[EM_SCHEME_NUM_TMP] = 8;
							updateSchemeInfo(8);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_9:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 9){
							NVRAM0[EM_SCHEME_NUM_TMP] = 9;
							updateSchemeInfo(9);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_10:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 10){
							NVRAM0[EM_SCHEME_NUM_TMP] = 10;
							updateSchemeInfo(10);
						}
					}						
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_11:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 11){
							NVRAM0[EM_SCHEME_NUM_TMP] = 11;
							updateSchemeInfo(11);
						}
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_12:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 12){
							NVRAM0[EM_SCHEME_NUM_TMP] = 12;
							updateSchemeInfo(12);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_13:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 13){
							NVRAM0[EM_SCHEME_NUM_TMP] = 13;
							updateSchemeInfo(13);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_14:{	
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 14){
							NVRAM0[EM_SCHEME_NUM_TMP] = 14;
							updateSchemeInfo(14);
						}
					}				
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_15:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 15){
							NVRAM0[EM_SCHEME_NUM_TMP] = 15;
							updateSchemeInfo(15);
						}
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_NEXT_PAGE:{
					if(state){
						SET(R_SCHEME_KEY_NEXT_SCHEME);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_SCHEME_1:{
			switch(control_id){
				case GDDC_PAGE_SCHEME_KEY_RENAME:{
					if(state){
						SET(R_SCHEME_KEY_RENAME_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_OK:{
					if(state){
						SET(R_SCHEME_KEY_OK_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_CANCEL:{
					if(state){
						SET(R_SCHEME_KEY_CANCEL_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_0:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 16){
							NVRAM0[EM_SCHEME_NUM_TMP] = 16;
							updateSchemeInfo(16);
						}
					}
					break;
				}	
				case GDDC_PAGE_SCHEME_KEY_SELECT_1:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 17){
							NVRAM0[EM_SCHEME_NUM_TMP] = 17;
							updateSchemeInfo(17);
						}
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_2:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 18){
							NVRAM0[EM_SCHEME_NUM_TMP] = 18;
							updateSchemeInfo(18);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_3:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 19){
							NVRAM0[EM_SCHEME_NUM_TMP] = 19;
							updateSchemeInfo(19);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_4:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 20){
							NVRAM0[EM_SCHEME_NUM_TMP] = 20;
							updateSchemeInfo(20);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_5:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 21){
							NVRAM0[EM_SCHEME_NUM_TMP] = 21;
							updateSchemeInfo(21);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_6:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 22){
							NVRAM0[EM_SCHEME_NUM_TMP] = 22;
							updateSchemeInfo(22);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_7:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 23){
							NVRAM0[EM_SCHEME_NUM_TMP] = 23;
							updateSchemeInfo(23);
						}
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_8:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 24){
							NVRAM0[EM_SCHEME_NUM_TMP] = 24;
							updateSchemeInfo(24);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_9:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 25){
							NVRAM0[EM_SCHEME_NUM_TMP] = 25;
							updateSchemeInfo(25);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_10:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 26){
							NVRAM0[EM_SCHEME_NUM_TMP] = 26;
							updateSchemeInfo(26);
						}
					}						
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_11:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 27){
							NVRAM0[EM_SCHEME_NUM_TMP] = 27;
							updateSchemeInfo(27);
						}
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_12:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 28){
							NVRAM0[EM_SCHEME_NUM_TMP] = 28;
							updateSchemeInfo(28);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_13:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 29){
							NVRAM0[EM_SCHEME_NUM_TMP] = 29;
							updateSchemeInfo(29);
						}
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_14:{	
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 30){
							NVRAM0[EM_SCHEME_NUM_TMP] = 30;
							updateSchemeInfo(30);
						}
					}				
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_15:{
					if(state){
						if(NVRAM0[EM_SCHEME_NUM_TMP] != 31){
							NVRAM0[EM_SCHEME_NUM_TMP] = 31;
							updateSchemeInfo(31);
						}
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_LAST_PAGE:{
					if(state){
						SET(R_SCHEME_KEY_LAST_SCHEME);
					}
					break;
				}
				default:break;
			}
			break;
		}				
		case GDDC_PAGE_DIAGNOSIS:{
			switch(control_id){
				case GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK:{
					if(state){
						SET(R_DIAGNOSIS_OK_DOWN);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_RFID:{
					if(state){
						SET(R_DISABLE_RFID);
					}
					else{
						RES(R_DISABLE_RFID);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FIBER_PROBE:{
					if(state){
						SET(R_DISABLE_FIBER_PROBE);
					}
					else{
						RES(R_DISABLE_FIBER_PROBE);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FAN_CONTRAL:{
					if(state){
						SET(R_DISABLE_FAN_SPEED);
					}
					else{
						RES(R_DISABLE_FAN_SPEED);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_CLEAR_EPROM:{
					if(state){
						SET(R_CLEAR_EPROM);
					}
					break;
				}
				default:break;
			}
		}				
		case GDDC_PAGE_RENAME:{
				switch(control_id){
				case GDDC_PAGE_RENAME_KEY_EXIT:{
					if(state){
						SET(R_RENAME_KEY_EXIT_DOWN);
					}
					break;
				}
				default:break;
			}			
			break;
		}
		default:break;
	}
}