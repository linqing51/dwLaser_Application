//自由协议程序
#include "sPlc.h"
/*****************************************************************************/
#define CMD_GET_LASER_TEMPERATURE											1
#define CMD_GET_LASER_CH1_LD													2
#define CMD_GET_LASER_CH2_LD													3
#define CMD_GET_LASER_CH1_PD													4
#define CMD_GET_LASER_CH2_PD													5
#define CMD_GET_TEC_CH1_CURRENT												6
#define CMD_GET_TEC_CH2_CURRENT												7
#define CMD_GET_LASER_CH1_POWESET											8
#define CMD_GET_LASER_CH2_POWESET											9
#define CMD_GET_LASER_ONTIME													10
#define CMD_GET_LASER_STATUS													11
/*****************************************************************************/
extern UART_HandleTypeDef huart6;
extern uint8_t uart6_rxDat;
ringBuff_t fpRingBuff_Rx;//自由协议接收缓冲
freeProtocol_t freeProtocol;
/*****************************************************************************/
static void startSendCmd(void){
	freeProtocol.txDone = 0;
	freeProtocol.txRuning = 1;
	HAL_UART_Transmit_IT(&huart6, freeProtocol.cmdBufTx, freeProtocol.txIndex);
}
void sPlcFreeProtocolInit(void){//自由协议初始化
	freeProtocol.rxDone = 0;
	freeProtocol.rxIndex = 0;
	freeProtocol.rxRuning = 0;
	freeProtocol.txDone = 0;
	freeProtocol.txIndex = 0;
	freeProtocol.txRuning = 0;
	memset(freeProtocol.cmdBufRx, 0x00, FP_RX_SIZE);
	memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
	HAL_UART_Receive_IT(&huart6, &uart6_rxDat, 1);
}
void sPlcFreeProtocolProcess(void){//自由协议命令处理 
	int16_t temp16;
	uint8_t rdat;
	char cbuf[8];
	while(1){
		if(sPlcRingBuffPop(&fpRingBuff_Rx, &rdat)){//有数据
			if((rdat == 'A') || 
				 (rdat == 'V') || 
			   (rdat == 'L') || 
			   (rdat == 'T') || 
				 (rdat == 'G') ||
				 (rdat == 'R') ||
				 (rdat == '$')){//接收到起始字符
				memset(freeProtocol.cmdBufRx, 0x00, CONFIG_FREEPROTOCOL_SIZE);
				freeProtocol.rxIndex = 0;
				freeProtocol.rxRuning = true;
				freeProtocol.rxDone = false;
				freeProtocol.cmdBufRx[freeProtocol.rxIndex] = rdat;
				freeProtocol.rxIndex ++;
				SSET(Y_ULINK_LED);
				break;
			}
			if((rdat == 'E') ||
				 (rdat == '#')){//接收到结束字符
				freeProtocol.rxRuning = false;
				freeProtocol.rxDone = true;
				freeProtocol.cmdBufRx[freeProtocol.rxIndex] = rdat;
				RRES(Y_ULINK_LED);
				break;
			}
			if(freeProtocol.rxRuning){
				if(freeProtocol.rxIndex < (CONFIG_FREEPROTOCOL_SIZE - 1)){//缓冲区未溢出
					freeProtocol.cmdBufRx[freeProtocol.rxIndex] = rdat;
					freeProtocol.rxIndex ++;
				}
				else{//超出缓冲区
					freeProtocol.rxIndex = 0;
					freeProtocol.rxDone = false;
					freeProtocol.rxRuning = false;
				}
				break;
			}
		}
		if(freeProtocol.rxDone){//自由协议接收完成
			if(freeProtocol.cmdBufRx[0] == 'A'){//检测到A指令且不再锁定态调节设置
				if(LDB(R_PARA_LOCK)){
					memset(cbuf, 0x0, 8);
					//设置通道1电流比例
					cbuf[0] = freeProtocol.cmdBufRx[1];
					cbuf[1] = freeProtocol.cmdBufRx[2];
					cbuf[2] = freeProtocol.cmdBufRx[3];
					temp16 = atoi(cbuf);
					if(temp16 >= 1000){
						temp16 = 1000;
					}
					if(temp16 < 0){
						temp16 = 0;
					}
					NVRAM0[EM_LASER_POWER_CH0] = temp16;
					//设定通道2电流比例
					cbuf[0] = freeProtocol.cmdBufRx[9];
					cbuf[1] = freeProtocol.cmdBufRx[10];
					cbuf[2] = freeProtocol.cmdBufRx[11];
					temp16 = atoi(cbuf);
					if(temp16 >= 1000){ 
						temp16 = 1000; 
					}
					if(temp16 < 0){
						temp16 = 0;
					}
					NVRAM0[EM_LASER_POWER_CH1] = temp16;
					//设置通道1占空比
					cbuf[0] = freeProtocol.cmdBufRx[5];
					cbuf[1] = freeProtocol.cmdBufRx[6];
					cbuf[2] = freeProtocol.cmdBufRx[7];
					temp16 = atoi(cbuf);
					//限定PWM 占空比在0-100%
					if(temp16 < 0 ){
						temp16 = 0;
					}
					if(temp16 >= 100){
						temp16 = 100;
					}
					NVRAM0[EM_LASER_PWM_CH0] = 0;//设定通道1 占空比
					//设置通道2占空比 	
					cbuf[0] = freeProtocol.cmdBufRx[13];
					cbuf[1] = freeProtocol.cmdBufRx[14];
					cbuf[2] = freeProtocol.cmdBufRx[15];
					temp16 = atoi(cbuf);
					//限定PWM 占空比在0-100%
					if(temp16 < 0 ){
						temp16 = 0;
					}
					if(temp16 >= 100){
						temp16 = 100;
					}
					NVRAM0[EM_LASER_PWM_CH1] = 0;//设定通道2 占空比
					//返回响应
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'C';
					freeProtocol.cmdBufTx[1] = 'A';
					freeProtocol.cmdBufTx[2] = 13; //回车
					freeProtocol.txIndex = 3;
				}
				else{//异常响应
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'C';
					freeProtocol.cmdBufTx[1] = 'F';
					freeProtocol.cmdBufTx[2] = 13; //回车
					freeProtocol.txIndex = 3;					
				}
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'L'){//激光发射指令
				if(LDB(X_EXT_ENABLE)){//内控模式
					if(freeProtocol.cmdBufRx[1] == '0' && freeProtocol.cmdBufRx[2] == '1'){
						SSET(R_LASER_START);//打开激光
					}
					if(freeProtocol.cmdBufRx[1] == '0' && freeProtocol.cmdBufRx[2] == '0'){
						SSET(R_LASER_STOP);//关闭激光
					}
					//发送返回值
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'L';
					freeProtocol.cmdBufTx[1] = 'A';
					freeProtocol.cmdBufTx[2] = 13; //回车
					freeProtocol.txIndex = 3;
				}
				else{//异常响应
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'L';
					freeProtocol.cmdBufTx[1] = 'F';
					freeProtocol.cmdBufTx[2] = 13; //回车
					freeProtocol.txIndex = 3;
				}
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'G'){//指示光控制
				if(freeProtocol.cmdBufRx[1] == '1' && freeProtocol.cmdBufRx[2] == '0'){
					RRES(R_AIM_ENABLE_CH0);
				}
				if(freeProtocol.cmdBufRx[1] == '1' && freeProtocol.cmdBufRx[2] == '1'){
					SSET(R_AIM_ENABLE_CH0);
				}
				if(freeProtocol.cmdBufRx[1] == '2' && freeProtocol.cmdBufRx[2] == '0'){
					RRES(R_AIM_ENABLE_CH1);
				}
				if(freeProtocol.cmdBufRx[1] == '2' && freeProtocol.cmdBufRx[2] == '1'){
					SSET(R_AIM_ENABLE_CH1);
				}
				//发送返回值
				memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
				freeProtocol.cmdBufTx[0] = 'G';
				freeProtocol.cmdBufTx[1] = 'A';
				freeProtocol.cmdBufTx[2] = 13; //回车
				freeProtocol.txIndex = 3;
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'T'){//指示设置出光时间
				//将串口时间指令送入Runouttime全局变量
				if(LDB(R_PARA_LOCK)){
					temp16 = atoi((const char*)&freeProtocol.cmdBufRx[1]);
					if(temp16 <= 0){
						temp16 = 0;
					}
					if(temp16 >= 999){
						temp16 = 999;//限制时间在[0,999]
					}
					NVRAM0[EM_LASER_POSWIDTH] = temp16;//计算ms值			
					//响应
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'T';
					freeProtocol.cmdBufTx[1] = 'A';
					freeProtocol.cmdBufTx[2] = 13; //回车
					freeProtocol.txIndex = 3;
				}
				else{//异常响应
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'T';
					freeProtocol.cmdBufTx[1] = 'F';
					freeProtocol.cmdBufTx[2] = 13; //回车
					freeProtocol.txIndex = 3;
				}
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'V'){//锁定参数
				if(freeProtocol.cmdBufRx[1] == '0' && freeProtocol.cmdBufRx[2] == '0'){//00
					RRES(R_PARA_LOCK);
				}
				if(freeProtocol.cmdBufRx[1] == '0' && freeProtocol.cmdBufRx[2] == '1'){//01
					SSET(R_PARA_LOCK);
				}
				memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
				freeProtocol.cmdBufTx[0] = 'V';
				freeProtocol.cmdBufTx[1] = 'A';
				freeProtocol.cmdBufTx[2] = 13; //回车
				freeProtocol.txIndex = 3;
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'R'){//读取内部信息(废弃)
				memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
				freeProtocol.cmdBufTx[0] = 'R';
				freeProtocol.cmdBufTx[1] = 'A';
				freeProtocol.cmdBufTx[2] = 13; //回车
				freeProtocol.txIndex = 3;
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == '$'){//扩展新指令
				memset(cbuf, 0x0, 8);
				cbuf[0] = freeProtocol.cmdBufRx[1];
				cbuf[1] = freeProtocol.cmdBufRx[2];
				temp16 = atoi(cbuf);
				switch(temp16){
					case CMD_GET_LASER_TEMPERATURE:{//获取激光器温度 CMD=01
						memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
						sprintf((char*)freeProtocol.cmdBufTx, "$0105%d#%d", NVRAM0[EM_LASER_TEMP], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH1_LD:{//获取激光器通道1电流 LD1 CMD=02
						sprintf((char*)freeProtocol.cmdBufTx, "$0205%d#%d", NVRAM0[EM_LASER_CURRENT_CH0], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH2_LD:{//获取激光器通道2电流 LD2 CMD=03
						sprintf((char*)freeProtocol.cmdBufTx, "$0305%d#%d", NVRAM0[EM_LASER_CURRENT_CH1], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH1_PD:{//获取激光器通道1功率 PD1 CMD=04
						sprintf((char*)freeProtocol.cmdBufTx, "$0405%d#%d", NVRAM0[EM_LASER_PD_CH0], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH2_PD:{//获取激光器通道2功率 PD2 CMD=05
						sprintf((char*)freeProtocol.cmdBufTx, "$0505%d#%d", NVRAM0[EM_LASER_PD_CH0], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_TEC_CH1_CURRENT:{//获取制冷通道1电流 CMD=06
						sprintf((char*)freeProtocol.cmdBufTx, "$0605%d#%d", NVRAM0[EM_LASER_CURRENT_CH2], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_TEC_CH2_CURRENT:{//获取制冷通道2电流 CMD=07
						sprintf((char*)freeProtocol.cmdBufTx, "$0705%d#%d", NVRAM0[EM_LASER_CURRENT_CH3], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}					
					case CMD_GET_LASER_CH1_POWESET:{//获取激光器通道1功率设置 CMD=08
						sprintf((char*)freeProtocol.cmdBufTx, "$0805%d#%d", NVRAM0[EM_LASER_POWER_CH0], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH2_POWESET:{//获取激光器通道2功率设置 CMD=09
						sprintf((char*)freeProtocol.cmdBufTx, "$0905%d#%d", NVRAM0[EM_LASER_POWER_CH1], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_ONTIME:{//获取激光发射时间 CMD=10
						sprintf((char*)freeProtocol.cmdBufTx, "$1005%d#%d", NVRAM0[EM_LASER_POSWIDTH], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_STATUS:{//获取激光发射状态 CMD=11
						temp16 = 0;
						memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
						freeProtocol.cmdBufTx[0] = '$';
						freeProtocol.cmdBufTx[1] = '1';
						freeProtocol.cmdBufTx[2] = '1';
						//报警状态
						if(LD(R_ALRAM)){
							freeProtocol.cmdBufTx[3] = '1';
						}
						else{
							freeProtocol.cmdBufTx[3] = '0';
						}
						//通道2激光状态
						if(LD(Y_LASER2_LED)){
							freeProtocol.cmdBufTx[5] = '1';
						}
						else{
							freeProtocol.cmdBufTx[5] = '0';
						}
						//通道1激光状态
						if(LD(Y_LASER1_LED)){
							freeProtocol.cmdBufTx[6] = '1';
						}
						else{
							freeProtocol.cmdBufTx[6] = '0';
						}
						//通道2指示光状态
						if(LD(R_AIM_ENABLE_CH1)){
							freeProtocol.cmdBufTx[7] = '1';
						}
						else{
							freeProtocol.cmdBufTx[7] = '0';
						}
						//通道1指示光状态
						if(LD(R_AIM_ENABLE_CH1)){
							freeProtocol.cmdBufTx[8] = '1';
						}
						else{
							freeProtocol.cmdBufTx[8] = '0';
						}
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					default:break;
				}
			}
			freeProtocol.rxDone = 0;
		}
		break;
	}
}


