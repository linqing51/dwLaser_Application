#include "dcHmiNotifyButton.h"
/*****************************************************************************/
//��ť�ؼ�֪ͨ����ť״̬�ı�(�����GetControlValue)ʱ��ִ�д˺���
//screen_id ����ID;control_id �ؼ�ID;state ��ť״̬��0����1����
void NotifyButton(uint16_t screen_id, uint16_t control_id, uint8_t state){ 
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	//PASSCODE ��������ҳ��
	switch(screen_id){
		case GDDC_PAGE_PASSCODE:{//�ȴ���������
			dispBuf[4] = 0;
			switch(control_id){
				case GDDC_PAGE_PASSCODE_KEY_NUM1:{//����1
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0031;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3100;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0031;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3100;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM2:{//����2
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0032;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3200;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0032;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3200;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM3:{//����3
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0033;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3300;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0033;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3300;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					dispBuf[4] = 0x0;
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));				
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM4:{//����4
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0034;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3400;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0034;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3400;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM5:{//����5
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0035;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3500;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0035;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3500;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM6:{//����6
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0036;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3600;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0036;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3600;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM7:{//����7
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0037;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3700;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0037;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3700;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM8:{//����8
						if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0038;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3800;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0038;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3800;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM9:{//����9
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0039;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3900;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0039;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3900;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					dispBuf[4] = 0x0;
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_NUM0:{//����0
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0030;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3000;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0030;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3000;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_CANCEL:{//����CANCEL
					CLR(EM_DC_NEW_PASSCODE0);//�������������
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ����
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_BACKSPACE:{//����BACKSPACE
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 4){
						NVRAM0[EM_DC_NEW_PASSCODE1] &= 0x00FF;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x3;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] &= 0xFF00;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE0] &= 0x00FF;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x1;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] &= 0xFF00;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x0;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
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
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					dispBuf[4] = 0x0;
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_ENTER:{//����ENTER
					if((NVRAM0[EM_DC_NEW_PASSCODE0] == NVRAM0[EM_DC_DEFAULT_PASSCODE0]) && (NVRAM0[EM_DC_NEW_PASSCODE1] == NVRAM0[EM_DC_DEFAULT_PASSCODE1])){
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
						SSET(R_ENGINEER_MODE);
						standbyDebugInfoVisiable(true);	
					}else if((NVRAM0[EM_DC_NEW_PASSCODE0] == NVRAM0[DM_DC_OLD_PASSCODE0]) && (NVRAM0[EM_DC_NEW_PASSCODE1] == NVRAM0[DM_DC_OLD_PASSCODE1])){
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
						RRES(R_ENGINEER_MODE);
						standbyDebugInfoVisiable(false);	
					}
					else{
						break;
					}
					CLR(EM_DC_NEW_PASSCODE0);//�������������
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ���� 
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					dispBuf[4] = 0x0;
					SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXTDISPLAY, (uint8_t*)(dispBuf));
					updateStandbyDisplay();
					standbyPageTouchEnable(true);
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_NEW_PASSCODE:{//����������ҳ��
			dispBuf[4] = 0x0;
			switch(control_id){
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM1:{//����1
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0031;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3100;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0031;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3100;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM2:{//����2	
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0032;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3200;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0032;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3200;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM3:{//����3
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0033;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3300;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0033;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3300;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM4:{//����4
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0034;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3400;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0034;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3400;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM5:{//����5
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0035;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3500;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0035;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3500;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM6:{//����6
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0036;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3600;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0036;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3600;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM7:{//����7
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0037;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3700;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0037;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3700;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM8:{//����8
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0038;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3800;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0038;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3800;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM9:{//����9
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0039;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3900;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0039;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3900;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;	
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM0:{//����0
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 0){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x0030;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 1;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] |= 0x3000;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x0030;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 3;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] |= 0x3000;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 4;
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_CANCEL:{
					CLR(EM_DC_NEW_PASSCODE0);
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ���� 
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;	
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_BACKSPACE:{
					if(NVRAM0[EM_DC_PASSCODE_INDEX] == 4){
						NVRAM0[EM_DC_NEW_PASSCODE1] &= 0x00FF;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x3;
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 3){
						NVRAM0[EM_DC_NEW_PASSCODE1] &= 0xFF00;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x2;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 2){
						NVRAM0[EM_DC_NEW_PASSCODE0] &= 0x00FF;	
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x1;	
					}
					else if(NVRAM0[EM_DC_PASSCODE_INDEX] == 1){
						NVRAM0[EM_DC_NEW_PASSCODE0] &= 0xFF00;
						NVRAM0[EM_DC_PASSCODE_INDEX] = 0x0;	
					}
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_SAVE:{
					if((NVRAM0[EM_DC_PASSCODE_INDEX] >= 4) && (NVRAM0[EM_DC_NEW_PASSCODE0] != 0x0000) && (NVRAM0[EM_DC_NEW_PASSCODE0] != 0x0000)){
						NVRAM0[DM_DC_OLD_PASSCODE0] = NVRAM0[EM_DC_NEW_PASSCODE0];
						NVRAM0[DM_DC_OLD_PASSCODE1] = NVRAM0[EM_DC_NEW_PASSCODE1];
						NVSAVE();
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
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_NEWPASSCODE_KEY_BACK:{//�����������޸�
					CLR(EM_DC_NEW_PASSCODE0);
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//���������ʾλ���� 
					NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_INPUT;
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					SetScreen(NVRAM0[EM_DC_PAGE]);
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_STANDBY_CW:{//������STANDBY CW
			switch(control_id){
				case GDDC_PAGE_STANDBY_KEY_AIM_BRG_ADD:{
					if(state){
						if(NVRAM0[DM_AIM_BRG] < CONFIG_AIM_MAX_DC){
							NVRAM0[DM_AIM_BRG] += 1;//+1
							SetTextInt32(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//���½�����
							SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//���½�����
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_AIM_BRG_DEC:{
					if(state){
						if(NVRAM0[DM_AIM_BRG] > 0){
							NVRAM0[DM_AIM_BRG] -= 1;//-1	
							SetTextInt32(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//���½�����
							SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//���½�����
						}
					}
					break;					
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASERPOWER_CH0){
							NVRAM0[EM_LASER_POWER_CH0]++;
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
							updatePowerDisplay();
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));						
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASERPOWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
							updatePowerDisplay();						
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
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
						SSET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SP;
						updateStandbyDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
						updateStandbyDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SSET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//����SCHEME
					if(state){
						SSET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}	
		case GDDC_PAGE_STANDBY_SP:{
			switch(control_id){
				case GDDC_PAGE_STANDBY_KEY_POWER_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASERPOWER_CH0){
							ADDS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];	
							updatePowerDisplay();
							SetProgressValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));						
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASERPOWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
							updatePowerDisplay();
							SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD:{	
					if(state){//DOWN
						SSET(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_SP_POSWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_SP_POSWIDTH], CONFIG_MAX_LASER_POSWIDTH);
						updatePosWidthDisplay();
					}
					else{
						RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
 				case GDDC_PAGE_STANDBY_KEY_POSWIDTH_DEC:{
					if(state){//DOWN
						SSET(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);	
						NVRAM0[EM_LASER_SP_POSWIDTH] = keyRuleDec(NVRAM0[EM_LASER_SP_POSWIDTH], CONFIG_MIN_LASER_POSWIDTH);
						updatePosWidthDisplay();
					}
					else{
						RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
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
						SSET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					else{
						SSET(R_STANDBY_KEY_STNADBY_UP);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
						updateStandbyDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					break;
				}	
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){	
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
						updateStandbyDisplay();
					}
					break;
				}

				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SSET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//����SCHEME
					if(state){
						SSET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_STANDBY_MP:{//������STANDBY MP
			switch(control_id){				
				case GDDC_PAGE_STANDBY_KEY_AIM_BRG_ADD:{
					if(state){
						if(NVRAM0[DM_AIM_BRG] < CONFIG_AIM_MAX_DC){
							NVRAM0[DM_AIM_BRG] += 1;//+1
							SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//���½�����
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_AIM_BRG_DEC:{
					if(state){
						if(NVRAM0[DM_AIM_BRG] > 0){
							NVRAM0[DM_AIM_BRG] -= 1;//-1	
							SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//���½�����
						}
					}
					break;					
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASERPOWER_CH0){
							ADDS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
							updatePowerDisplay();
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));						
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_DEC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASERPOWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
							updatePowerDisplay();
							SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD:{	
					if(state){//DOWN
						SSET(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_MP_POSWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_MP_POSWIDTH], CONFIG_MAX_LASER_POSWIDTH);
						updatePosWidthDisplay();
					}
					else{
						RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POSWIDTH_DEC:{
					if(state){//DOWN
						SSET(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						NVRAM0[EM_LASER_MP_POSWIDTH] = keyRuleDec(NVRAM0[EM_LASER_MP_POSWIDTH], CONFIG_MIN_LASER_POSWIDTH);
						updatePosWidthDisplay();
					}
					else{
						RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);	
						T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD:{
					if(state){//DOWN
						SSET(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						NVRAM0[EM_LASER_MP_NEGWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_MP_NEGWIDTH], CONFIG_MAX_LASER_NEGWIDTH);
						updateNegWidthDisplay();
					}
					else{
						RRES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_NEGWIDTH_DEC:{
					if(state){//DOWN
						SSET(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						NVRAM0[EM_LASER_MP_NEGWIDTH] = keyRuleDec(NVRAM0[EM_LASER_MP_NEGWIDTH], CONFIG_MIN_LASER_NEGWIDTH);
						updateNegWidthDisplay();
					}
					else{
						RRES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
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
						SSET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
						updateStandbyDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_SP;
						updateStandbyDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					break;
				}	
				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SSET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//����SCHEME
					if(state){
						SSET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_READY:{
			switch(control_id){
				case GDDC_PAGE_READY_KEY_READY:{
					if(!state){
						SSET(R_STANDBY_KEY_STNADBY_UP);
					}
					break;
				}				
				case GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_ADD:{
					if(state){//DOWN
						SSET(R_READY_KEY_ACOUSTIC_ENERGY_ADD_DOWN);
						addAcousticEnergy();
						updateAcousticDisplay();
					}
					else{//UP
						RRES(R_READY_KEY_ACOUSTIC_ENERGY_ADD_DOWN);
						T10MS(T10MS_ACOUSTIC_ENERGY_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_DEC:{
					if(state){//DOWN
						SSET(R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN);
						decAcousticEnergy();
						updateAcousticDisplay();
					}
					else{//UP
						RRES(R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN);
						T10MS(T10MS_ACOUSTIC_ENERGY_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_ADD:{
					if(state){//DOWN
						SSET(R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN);
						addAcousticTime();
						updateAcousticDisplay();
					}
					else{//UP
						RRES(R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN);
						T10MS(T10MS_ACOUSTIC_TIME_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					break;
				}
				case GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_DEC:{
					if(state){//DOWN
						SSET(R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN);
						decAcousticTime();
						updateAcousticDisplay();
					}
					else{//UP
						RRES(R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN);
						T10MS(T10MS_ACOUSTIC_TIME_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
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
						SSET(MR_BEEP_TONE);
					}
					else{
						RRES(MR_BEEP_TONE);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_ADD:{
					if(state){
						if(NVRAM0[DM_BEEM_VOLUME] < CONFIG_BEEM_MAX_VOLUME){
							NVRAM0[DM_BEEM_VOLUME] += 1;
							NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
							SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
							SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//���½�����
						}
					}
					break;					
				}
				case GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_DEC:{
					if(state){
						if(NVRAM0[DM_BEEM_VOLUME] > 0){
							NVRAM0[DM_BEEM_VOLUME] -= 1;
							NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
							SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
							SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//���½�����
						}
					}
					break;					
				}
				case GDDC_PAGE_OPTION_KEY_LCD_BRG_ADD:{
					if(state){
						if(NVRAM0[DM_LCD_BRG] < CONFIG_LCD_MAX_DC){
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
						if(NVRAM0[DM_LCD_BRG] > CONFIG_LCD_MIN_DC){
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
						SSET(R_OPTION_KEY_ENTER_INFORMATION_DOWN);
					}
					break;							
				}
				case GDDC_PAGE_OPTION_KEY_ENTER_OK:{//OK
					if(state){
						SSET(R_OPTION_KEY_ENTER_OK_DOWN);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON:{
					if(state){
						SSET(MR_FOOSWITCH_HAND_SWITCH);
					}
					else{
						RRES(MR_FOOSWITCH_HAND_SWITCH);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER:{
					if(state){
						SSET(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_RESTORE:{//�ָ�Ĭ��ֵ
					if(state){
						optionKeyEnable(false);//��������
						loadDefault();
						lockPreScheme();
						NVFSAVE();//ǿ�Ƹ���NVRAM
						updateOptionDisplay();//����Option��ʾ
						SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));//���±�������
						optionKeyEnable(true);//��������
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_INFORMATION:{
			switch(control_id){
				case GDDC_PAGE_INFO_KEY_ENTER_OK:{
					if(state){
						SSET(R_INFORMATION_KEY_OK_DOWN);
					}
					else{
						SSET(R_INFORMATION_KEY_OK_UP);
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
						SSET(R_SCHEME_KEY_RENAME_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_OK:{
					if(state){
						SSET(R_SCHEME_KEY_OK_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_CANCEL:{
					if(state){
						SSET(R_SCHEME_KEY_CANCEL_DOWN);
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
						SSET(R_SCHEME_KEY_NEXT_SCHEME);
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
						SSET(R_SCHEME_KEY_RENAME_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_OK:{
					if(state){
						SSET(R_SCHEME_KEY_OK_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_CANCEL:{
					if(state){
						SSET(R_SCHEME_KEY_CANCEL_DOWN);
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
						SSET(R_SCHEME_KEY_LAST_SCHEME);
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
						SSET(R_DIAGNOSIS_OK_DOWN);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FOOTSWITCH:{
					if(state){
						SSET(R_DISABLE_FOOTSWITCH);
					}
					else{
						RRES(R_DISABLE_FOOTSWITCH);
					}
					break;
				}					
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_TEMPERATURE:{
					if(state){
						SSET(R_DISABLE_TEMPERATURE);
					}
					else{
						RRES(R_DISABLE_TEMPERATURE);
					}
					break;
				}					
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_ESTOP:{
					if(state){
						SSET(R_DISABLE_ESTOP);
					}
					else{
						RRES(R_DISABLE_ESTOP);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_INTERLOCK:{
					if(state){
						SSET(R_DISABLE_INTERLOCK);
					}
					else{
						RRES(R_DISABLE_INTERLOCK);
					}
					break;
				}					
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_RFID:{
					if(state){
						SSET(R_DISABLE_RFID);
					}
					else{
						RRES(R_DISABLE_RFID);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FIBER_PROBE:{
					if(state){
						SSET(R_DISABLE_FIBER_PROBE);
					}
					else{
						RRES(R_DISABLE_FIBER_PROBE);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FAN_CONTRAL:{
					if(state){
						SSET(R_DISABLE_FAN_SPEED);
					}
					else{
						RRES(R_DISABLE_FAN_SPEED);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_CALIBRATION_MODE:{
					if(state){
						SSET(R_CALIBRATION_MODE);
					}
					else{
						RRES(R_CALIBRATION_MODE);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_CLEAR_EPROM:{//���EPROM
					if(state){
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
						SSET(R_CLEAR_EPROM);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_CLEAR_CRC:{//��չ̼�CRC
					if(state){
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
						SSET(R_CLEAR_CRC);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_SAVE_EPROM:{//����EPROM
					if(state){
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
						SSET(R_SAVE_EPROM);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ:{//����BOOTLOAD����
					if(state){
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
						SSET(R_UPDATE_BOOTLOAD_REQ);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES:{//����U��BOOTLOAD�ļ�CRCֵ
					if(state){
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
						SSET(R_UPDATE_BOOTLOAD_YES);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO:{
					if(state){
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
						SSET(R_UPDATE_BOOTLOAD_NO);
					}
				}
				default:break;
			}
		}				
		case GDDC_PAGE_RENAME:{
				switch(control_id){
				case GDDC_PAGE_RENAME_KEY_EXIT:{
					if(state){
						SSET(R_RENAME_KEY_EXIT_DOWN);
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





