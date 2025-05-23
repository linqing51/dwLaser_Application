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
					else if((NVRAM0[EM_DC_NEW_PASSCODE0] == CONFIG_HMI_ADMIN_PASSWORD0) && (NVRAM0[EM_DC_NEW_PASSCODE1] == CONFIG_HMI_ADMIN_PASSWORD1)){
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
					if((NVRAM0[EM_DC_NEW_PASSCODE0] == CONFIG_HMI_ADMIN_PASSWORD0) && (NVRAM0[EM_DC_NEW_PASSCODE1] == CONFIG_HMI_ADMIN_PASSWORD1)){
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
					SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0, "1940nm");
					SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1, "");
					SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, "635nm");
					SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_SELECT_CH1, false);
					SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1, false);
					SetTextValue(screen_id, GDDC_PAGE_PASSCODE_TEXTDISPLAY, (uint8_t*)(dispBuf));
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//切换待机页面						
					SetScreen(NVRAM0[EM_DC_PAGE]);					
					updateStandbyDisplay();
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
					*(int16_t*)(dispBuf + 0) = NVRAM0[EM_DC_NEW_PASSCODE0];
					*(int16_t*)(dispBuf + 2) = NVRAM0[EM_DC_NEW_PASSCODE1];
					SetTextValue(screen_id, 15, (uint8_t*)(dispBuf));		
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
					SetScreen(NVRAM0[EM_DC_PAGE]);
					break;
				}
				default:break;
			}
			break;
		}		
		case GDDC_PAGE_STANDBY:{//主界面STANDBY CW
			switch(control_id){
				case GDDC_PAGE_STANDBY_KEY_POWER_SEL_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){//选中1470nm
							if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASER_POWER_CH0){
								ADDS1(EM_LASER_POWER_CH0);
							}
						}
						if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){//选中980nm
							if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASER_POWER_CH1){
								ADDS1(EM_LASER_POWER_CH1);							
							}
						}
						if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_RED){//选中635nm
							if(NVRAM0[EM_LASER_POWER_635] < CONFIG_MAX_LASER_POWER_RED){
								ADDS1(EM_LASER_POWER_635);								
							}
						}
						NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_635];
						updateStandbyDisplay();
					}					
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_SEL_INC:{
					if(state){

						if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){//选中1470nm
							if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASER_POWER_CH0){
								DECS1(EM_LASER_POWER_CH0);
							}
						}

						if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){//选中980nm
							if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASER_POWER_CH1){
								DECS1(EM_LASER_POWER_CH1);							
							}
						}
						if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_RED){//选中635nm
							if(NVRAM0[EM_LASER_POWER_635] > CONFIG_MIN_LASER_POWER_RED){
								DECS1(EM_LASER_POWER_635);								
							}
						}						
						NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_635];
						updateStandbyDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH0:{
					if(state){
						NVRAM0[EM_LASER_CHANNEL_SELECT] = LASER_CHANNEL_CH0;
						updateStandbyDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SELECT_CH1:{
					if(state){
						NVRAM0[EM_LASER_CHANNEL_SELECT] = LASER_CHANNEL_CH1;
						updateStandbyDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_SELECT_RED:{
					if(state){
						NVRAM0[EM_LASER_CHANNEL_SELECT] = LASER_CHANNEL_RED;
						updateStandbyDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] < CONFIG_MAX_LASER_POWER_CH0){
							ADDS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_635];
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH0_INC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH0] > CONFIG_MIN_LASER_POWER_CH0){
							DECS1(EM_LASER_POWER_CH0);
							NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_635];
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] < CONFIG_MAX_LASER_POWER_CH1){
							ADDS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_635];
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_CH1_INC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_CH1] > CONFIG_MIN_LASER_POWER_CH1){
							DECS1(EM_LASER_POWER_CH1);
							NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_635];
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_RED_ADD:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_635] < CONFIG_MAX_LASER_POWER_RED){
							ADDS1(EM_LASER_POWER_635);
							NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_635];
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_RED_INC:{
					if(state){
						if(NVRAM0[EM_LASER_POWER_635] > CONFIG_MIN_LASER_POWER_RED){
							DECS1(EM_LASER_POWER_635);
							NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1] + NVRAM0[EM_LASER_POWER_635];
							updateStandbyDisplay();
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_AIM_ADD:{
					if(state){
						if(NVRAM0[DM_AIM_BRG] < CONFIG_MAX_LASER_POWER_AIM){
							ADDS1(DM_AIM_BRG);
							updateStandbyDisplay();					
						}
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_POWER_AIM_INC:{
					if(state){
						if(NVRAM0[DM_AIM_BRG] > CONFIG_MIN_LASER_POWER_AIM){
							DECS1(DM_AIM_BRG);
							updateStandbyDisplay();
						}
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
				case GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC:{
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
				case GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC:{
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
						if (NVRAM0[DM_SCHEME_CLASSIFY] == SCHEME_CUSTIOM){
							updateCustomScheme(NVRAM0[DM_SCHEME_INDEX]);//EM->FD
							FDSAV_ONE(NVRAM0[DM_SCHEME_INDEX]);//FDRAM->EPROM
						}
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
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
						//隐藏MP模式按键
						updateExtralDisplay();
					}
					break;
				}
				case GDDC_PAGE_STANDBY_KEY_MODE_MP:{
					if(state){
						NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_MP;
						//显示MP模式按键
						updatePosWidthDisplay();
						updateNegWidthDisplay();
						updateExtralDisplay();
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
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME;
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_DUAL;
						SetScreen(NVRAM0[EM_DC_PAGE]);
						
						//memcpy((char*)FDRAM1, (char*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));		
						//NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_CUSTIOM;
						//NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						//NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;	
						//SetScreen(NVRAM0[EM_DC_PAGE]);				
						//updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						//seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);							
#endif
#if defined(MODEL_PVGLS_TRI_A0)				
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_TRI;
						SetScreen(NVRAM0[EM_DC_PAGE]);
#endif
#if defined(MODEL_PVGLS_10W_1940_A1)		
					memcpy((char*)FDRAM1, (char*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));						
					NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_CUSTIOM;											
					NVRAM0[EM_SCHEME_NUM_TMP] = 0;
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;	
					SetScreen(NVRAM0[EM_DC_PAGE]);						
					updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
#endif
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
				case GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_INC:{
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
				case GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_INC:{
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
				case GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_INC:{
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
				case GDDC_PAGE_OPTION_KEY_LCD_BRG_INC:{
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
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
						//loadScheme();
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//切换待机页面
						SetScreen(NVRAM0[EM_DC_PAGE]);//切换待机页面
						updateStandbyDisplay();
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
				default:break;
			}
			break;
		}
		case GDDC_PAGE_RESTORE:{
			switch(control_id){
				case GDDC_PAGE_RESTORE_KEY_YES:{
					if(state){
						restoreDefault();
						NVFSAVE();//强制更新NVRAM
						FDSAV();
						//updateOptionDisplay();//更新Option显示
						//SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));//更新背光亮度
						//NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
						//SetScreen(NVRAM0[EM_DC_PAGE]);
						REBOOT();
					}
					break;
				}
				default:break;
			}
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
		case GDDC_PAGE_SCHEME_CLASSIFY_TRI:{
			switch(control_id){
				case  GDDC_PAGE_SCHMEM_CLASSIFY_KEY_PHLEBOLOGY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_PHLEBOLOGY;
						NVRAM0[EM_SCHEME_NUM_TMP] = 0; 
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}					
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_PROCTOLOGY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_PROCTOLOGY;
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;						
						SetScreen(NVRAM0[EM_DC_PAGE]);
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_GTNECOLOGY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_GYNECOLOGY;	
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_ENT:{
					if(state){	
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_ENT;
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;	
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}			
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_NEUROSURGERY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_NEUROSURGERY;
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}				
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_DERAMATOLOGY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_DERMATOLOGY;			
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_LIPOSUCTION:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_LIPOSUCTION;
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_DENTISTRY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_DENTISTRY;	
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_THERAPY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHMEM_THERAPY;	
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_CUSTOM:{
					if(state){		
						memcpy((char*)FDRAM1, (char*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));						
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_CUSTIOM;											
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;	
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_RETURN:{	
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;
						SetScreen(NVRAM0[EM_DC_PAGE]);
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
						updateStandbyDisplay();					
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_SCHEME_CLASSIFY_DUAL:{
			switch(control_id){
				case  GDDC_PAGE_SCHMEM_CLASSIFY_KEY_PHLEBOLOGY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_PHLEBOLOGY;
						NVRAM0[EM_SCHEME_NUM_TMP] = 0; 
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}					
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_PROCTOLOGY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_PROCTOLOGY;
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;						
						SetScreen(NVRAM0[EM_DC_PAGE]);
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_GTNECOLOGY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_GYNECOLOGY;	
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}		
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_NEUROSURGERY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_NEUROSURGERY;
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}				
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_LIPOSUCTION:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_LIPOSUCTION;
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_THERAPY:{
					if(state){
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHMEM_THERAPY;	
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_CUSTOM:{
					if(state){		
						memcpy((char*)FDRAM1, (char*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));						
						NVRAM0[EM_SCHEME_CLASSIFY_TMP] = SCHEME_CUSTIOM;											
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;	
						SetScreen(NVRAM0[EM_DC_PAGE]);						
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						seletcSchemeNum(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
					}
					break;
				}
				case GDDC_PAGE_SCHMEM_CLASSIFY_KEY_RETURN:{	
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;
						SetScreen(NVRAM0[EM_DC_PAGE]);
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
						updateStandbyDisplay();					
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_SCHEME_DETAIL:{
			switch(control_id){
				case GDDC_PAGE_SCHEME_KEY_RENAME:{
					if(state){
						SSET(R_SCHEME_KEY_RENAME_DOWN);
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_OK:{
					if(state){
						if(NVRAM0[EM_SCHEME_CLASSIFY_TMP] == SCHEME_CUSTIOM){
							memcpy((char*)FDRAM0, (char*)FDRAM1, (CONFIG_FDRAM_SIZE * 2));
						}							
						NVRAM0[DM_SCHEME_INDEX] = NVRAM0[EM_SCHEME_NUM_TMP];//选定方案生效
						NVRAM0[DM_SCHEME_CLASSIFY] = NVRAM0[EM_SCHEME_CLASSIFY_TMP];
						loadSelectScheme(NVRAM0[DM_SCHEME_CLASSIFY], NVRAM0[DM_SCHEME_INDEX]);
						NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;
						SetScreen(NVRAM0[EM_DC_PAGE]);
						updateStandbyDisplay();	
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_CANCEL:{
					if(state){
#if defined(MODEL_PVGLS_TRI_A0)						
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_TRI;
						SetScreen(NVRAM0[EM_DC_PAGE]);
#endif
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_CLASSIFY_DUAL;
						SetScreen(NVRAM0[EM_DC_PAGE]);
#endif
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
						NVRAM0[EM_SCHEME_NUM_TMP] = 16;
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_SELECT_0, 1);
						updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);						
					}
					break;
				}
				case GDDC_PAGE_SCHEME_KEY_LAST_PAGE:{
					if(state){
						NVRAM0[EM_SCHEME_NUM_TMP] = 0;
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
						SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_SELECT_0, 1);	
						updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
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
				case GDDC_PAGE_DISGNOSIS_KEY_CLEAR_CRC:{//清空固件CRC
					if(state){
						SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
						SSET(R_CLEAR_CRC);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_SAVE_EPROM:{//储存EPROM
					if(state){
						SSET(R_SAVE_EPROM);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ:{//更新BOOTLOAD请求
					if(state){
						SSET(R_UPDATE_BOOTLOAD_REQ);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES:{//计算U盘BOOTLOAD文件CRC值
					if(state){
						SSET(R_UPDATE_BOOTLOAD_YES);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO:{
					if(state){
						SSET(R_UPDATE_BOOTLOAD_NO);
					}
					break;
				}
				case GDDC_PAGE_DISGNOSIS_KEY_OPEN_ILOCK:{
					if(state){
						deviceConfig.normalOpenInterLock = 0;//按下设置为联锁常闭
					}
					else{
						deviceConfig.normalOpenInterLock = 1;//弹起设置为连锁常开
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





