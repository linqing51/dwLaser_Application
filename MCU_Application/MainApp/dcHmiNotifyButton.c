#include "dcHmiNotifyButton.h"
/*****************************************************************************/
//按钮控件通知当按钮状态改变(或调用GetControlValue)时，执行此函数
//screen_id 画面ID;control_id 控件ID;state 按钮状态：0弹起，1按下
void NotifyButton(uint16_t screen_id, uint16_t control_id, uint8_t state){ 
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	//PASSCODE 密码输入页面
	switch(screen_id){
		case GDDC_PAGE_PASSCODE:{//等待密码输入
			dispBuf[4] = 0;
			switch(control_id){
				case GDDC_PAGE_PASSCODE_KEY_NUM1:{//按键1
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
				case GDDC_PAGE_PASSCODE_KEY_NUM2:{//按键2
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
				case GDDC_PAGE_PASSCODE_KEY_NUM3:{//按键3
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
				case GDDC_PAGE_PASSCODE_KEY_NUM4:{//按键4
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
				case GDDC_PAGE_PASSCODE_KEY_NUM5:{//按键5
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
				case GDDC_PAGE_PASSCODE_KEY_NUM6:{//按键6
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
				case GDDC_PAGE_PASSCODE_KEY_NUM7:{//按键7
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
				case GDDC_PAGE_PASSCODE_KEY_NUM8:{//按键8
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
				case GDDC_PAGE_PASSCODE_KEY_NUM9:{//按键9
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
				case GDDC_PAGE_PASSCODE_KEY_NUM0:{//按键0
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
				case GDDC_PAGE_PASSCODE_KEY_CANCEL:{//按键CANCEL
					CLR(EM_DC_NEW_PASSCODE0);//清空已输入密码
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_BACKSPACE:{//按键BACKSPACE
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
				case GDDC_PAGE_PASSCODE_KEY_CHANGEPASSCODE:{//按键CHANGEPASSCODE
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
					CLR(EM_DC_NEW_PASSCODE0);//清空已输入密码
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					dispBuf[4] = 0x0;
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));
					break;
				}
				case GDDC_PAGE_PASSCODE_KEY_ENTER:{//按键ENTER
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
					CLR(EM_DC_NEW_PASSCODE0);//清空已输入密码
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引 
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
		case GDDC_PAGE_NEW_PASSCODE:{//新密码输入页面
			dispBuf[4] = 0x0;
			switch(control_id){
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM1:{//按键1
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
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM2:{//按键2	
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
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM3:{//按键3
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
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM4:{//按键4
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
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM5:{//按键5
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
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM6:{//按键6
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
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM7:{//按键7
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
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM8:{//按键8
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
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM9:{//按键9
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
				case GDDC_PAGE_NEWPASSCODE_KEY_NUM0:{//按键0
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
					CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引 
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
						CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引 
						CLR(EM_DC_NEW_PASSCODE0);
						CLR(EM_DC_NEW_PASSCODE1);
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_INPUT;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
						SetScreen(NVRAM0[EM_DC_PAGE]);
					}
					else{
						CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引 
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
				case GDDC_PAGE_NEWPASSCODE_KEY_BACK:{//放弃新密码修改
					CLR(EM_DC_NEW_PASSCODE0);
					CLR(EM_DC_NEW_PASSCODE1);
					CLR(EM_DC_PASSCODE_INDEX);//清空密码显示位索引 
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
		case GDDC_PAGE_STANDBY_CW:{//主界面STANDBY CW
			switch(control_id){
				case GDDC_PAGE_STANDBY_KEY_AIM_BRG_ADD:{
					if(state){
						SSET(R_STANDBY_KEY_AIM_BRG_ADD_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_AIM_BRG_DEC:{
					if(state){
						SSET(R_STANDBY_KEY_AIM_BRG_DEC_DOWN);
					}
					break;					
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_ADD:{
					if(state){
						SSET(R_STANDBY_KEY_POWER_ADD_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_DEC:{
					if(state){
						SSET(R_STANDBY_KEY_POWER_DEC_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST:{//选择上一个方案
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_LAST_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//选择下一个方案
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_NEXT_DOWN);
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
						SSET(R_STANDBY_KEY_MODE_SP_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){
						SSET(R_STANDBY_KEY_MODE_MP_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SSET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//按键SCHEME
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
						SSET(R_STANDBY_KEY_POWER_ADD_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_DEC:{
					if(state){
						SSET(R_STANDBY_KEY_POWER_DEC_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD:{	
					if(state){//DOWN
						SSET(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
					}
					else{
						SSET(R_STANDBY_KEY_POSWIDTH_ADD_UP);
					}
					break;
				}
 				case GDDC_PAGE_STANDBY_KEY_POSWIDTH_DEC:{
					if(state){//DOWN
						SSET(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);	
					}
					else{
						SSET(R_STANDBY_KEY_POSWIDTH_DEC_UP);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST:{//选择上一个方案
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_LAST_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//选择下一个方案
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_NEXT_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_STANDBY:{
					if(state){
						//禁止STANDBY触摸
						SSET(R_STANDBY_KEY_STNADBY_DOWN);
					}
					else{
						SSET(R_STANDBY_KEY_STNADBY_UP);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_CW:{
					if(state){
						SSET(R_STANDBY_KEY_MODE_CW_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					break;
				}	
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){	
						SSET(R_STANDBY_KEY_MODE_MP_DOWN);
					}
					break;
				}

				case GDDC_PAGE_STANDBY_KEY_ENTER_OPTION:{
					if(state){
						SSET(R_STANDBY_KEY_ENTER_OPTION_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//按键SCHEME
					if(state){
						SSET(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_STANDBY_MP:{//主界面STANDBY MP
			switch(control_id){				
				case GDDC_PAGE_STANDBY_KEY_AIM_BRG_ADD:{
					if(state){
						SSET(R_STANDBY_KEY_AIM_BRG_ADD_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_AIM_BRG_DEC:{
					if(state){
						SSET(R_STANDBY_KEY_AIM_BRG_DEC_DOWN);
					}
					break;					
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_ADD:{
					if(state){
						SSET(R_STANDBY_KEY_POWER_ADD_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_DEC:{
					if(state){
						SSET(R_STANDBY_KEY_POWER_DEC_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD:{	
					if(state){//DOWN
						SSET(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
					}
					else{
						SSET(R_STANDBY_KEY_POSWIDTH_ADD_UP);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POSWIDTH_DEC:{
					if(state){//DOWN
						SSET(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
					}
					else{
						SSET(R_STANDBY_KEY_POSWIDTH_DEC_UP);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD:{
					if(state){//DOWN
						SSET(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
					}
					else{
						SSET(R_STANDBY_KEY_NEGWIDTH_ADD_UP);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_NEGWIDTH_DEC:{
					if(state){//DOWN
						SSET(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
					}
					else{
						SSET(R_STANDBY_KEY_NEGWIDTH_DEC_UP);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE:{
					if(state){					
						SSET(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_LAST:{//选择上一个方案
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_LAST_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT:{//选择下一个方案
					if(state){
						SSET(R_STANDBY_KEY_SCHEME_NEXT_DOWN);
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
						SSET(R_STANDBY_KEY_MODE_CW_DOWN);
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_SP:{
					if(state){
						SSET(R_STANDBY_KEY_MODE_SP_DOWN);
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
				case GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME:{//按键SCHEME
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
					}
					else{//UP
						SSET(R_READY_KEY_ACOUSTIC_ENERGY_ADD_UP);
					}
					break;
				}
				case GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_DEC:{
					if(state){//DOWN
						SSET(R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN);
					}
					else{//UP
						SSET(R_READY_KEY_ACOUSTIC_ENERGY_DEC_UP);
					}
					break;
				}
				case GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_ADD:{
					if(state){//DOWN
						SSET(R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN);
					}
					else{//UP
						SSET(R_READY_KEY_ACOUSTIC_TIME_ADD_UP);
					}
					break;
				}
				case GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_DEC:{
					if(state){//DOWN
						SSET(R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN);
					}
					else{//UP
						SSET(R_READY_KEY_ACOUSTIC_TIME_DEC_UP);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_OPTION:{//选项页面
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
						SSET(R_OPTION_KEY_BEEM_VOLUME_ADD_DOWN);
					}
					break;					
				}
				case GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_DEC:{
					if(state){
						SSET(R_OPTION_KEY_BEEM_VOLUME_DEC_DOWN);
					}
					break;					
				}
				case GDDC_PAGE_OPTION_KEY_LCD_BRG_ADD:{
					if(state){
						SSET(R_OPTION_KEY_LCD_BRG_ADD_DOWN);
					}
					break;
				}
				case GDDC_PAGE_OPTION_KEY_LCD_BRG_DEC:{
					if(state){
						SSET(R_OPTION_KEY_LCD_BRG_DEC_DOWN);
					}
					break;					
				}
				case GDDC_PAGE_OPTION_KEY_ENTER_INFORMATION:{//信息
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
				case GDDC_PAGE_OPTION_KEY_RESTORE:{//恢复默认值
					if(state){
						SSET(R_OPTION_KEY_RESTORE_DOWN);
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
						SSET(R_SCHEME_KEY_SCHEME_SELECT_0_DOWN);
					}
					break;
				}	
				case GDDC_PAGE_SCHEME_KEY_SELECT_1:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_1_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_2:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_2_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_3:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_3_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_4:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_4_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_5:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_5_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_6:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_6_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_7:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_7_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_8:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_8_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_9:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_9_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_10:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_10_DOWN);
					}						
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_11:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_11_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_12:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_12_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_13:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_13_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_14:{	
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_14_DOWN);
					}				
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_15:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_15_DOWN);
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
						SSET(R_SCHEME_KEY_SCHEME_SELECT_16_DOWN);
					}
					break;
				}	
				case GDDC_PAGE_SCHEME_KEY_SELECT_1:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_17_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_2:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_18_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_3:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_19_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_4:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_20_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_5:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_21_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_6:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_22_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_7:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_23_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_8:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_24_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_9:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_25_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_10:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_26_DOWN);
					}						
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_11:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_27_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_12:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_28_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_13:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_29_DOWN);
					}					
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_14:{	
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_30_DOWN);
					}				
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_SELECT_15:{
					if(state){
						SSET(R_SCHEME_KEY_SCHEME_SELECT_31_DOWN);
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
				case GDDC_PAGE_DISGNOSIS_KEY_CLEAR_EPROM:{//清空EPROM
					if(state){
						SSET(R_CLEAR_EPROM);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_SAVE_EPROM:{//储存EPROM
					if(state){
						SSET(R_SAVE_EPROM);
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





