/*******************************************************************************************************/
//作者：林卿                                                                                          
//程序描述：SAE(东莞) 定制 双通道 5W 808nM 无头激光器控制程序
//版本    alpha ->Beta ->Release     Alpha阶段完成新功能 Beta阶段测试各组件功能  Release阶段原则上只进行必要维护
//0.0.1   2008.1.10     alpha0 移植UCOS2 2.85 到C8051F020 正常运行
//0.1.0   2008.4.30     alpha1 初次硬件仿真运行通过
//0.1.1   2008.5.01     alpha2 加入指示光控制，计时出光
//0.1.2   2008.5.03     alpha3 加入NTC温度电阻计算 改进了计时出光增强了实时性 不在依赖上位机计时出光 同时进一步
//                             摆脱前后台系统的束缚完全利用实时系统的信号传递机制进行任务通信和触发彻底解决系统实时性问题
//0.1.3   2008.5.04     alpha3 修正了温度采样程序中的若干问题，加入了显示温度的串口指令
//0.1.4   2008.5.04     alpha3 试图修正LTimer计数器的若干问题(计时为0时)
//0.1.5   2008.5.14     alpha3 修正TLC5617程序的若干问题，取消了加热功能，调节了若干参数
//0.1.6   2008.5.29     alpha3 串口响应加上回车字符，检测到报警信号将不发送出光响应 
//0.2.0   2008.7.11     Beta1  在UCOS上加入看门狗指示灯信号与狗合并,复位后通过串口发出RST信号
//0.2.1   2009.2.18     Beta1  增加C8051F020的内置DAC功能，5617控制激光器温度，020控制电流
//                             移除占空比调节功能，正式加入指示光功能，激光模块改为980nM 
//							   修改电流设置精度0.01A
//0.2.1a  2009.06.12    Beta1  计时器改为0.1s步进 0.1秒-10.0秒                                                       
//*******************************************************************************************************/
#include "mainApp.h"
/*UCOS2 tick 5mS*************************************************************/
#define TEMP_SAMP_FRQ      50                     //定义PID 采样周期 TEMP_SAMP_FRQ * TICK(5mS)  
#define ALARM_TEMP_LOW     0.0                    //定义低温报警下限
#define ALARM_TEMP_HIGH    40.0					  //定义高温报警上限
#define LTIMERCOE          20                      //定义出光计数器 计时常数  1 / TICK   步进 0.1s调
#define CH1TEMPERATURE     22.0                   //定义1通道恒定温度
#define CH2TEMPERATURE     22.0                   //定义2通道恒定温度
#define TEMPSTAB           4.0                    //定义温度稳态误差绝对值
#define LAGTEMPERATURE     10.0                   //温度迟滞比较器窗口大小避免在限定温度附近来回跳动增强稳定性
#define LASERPWMTIMER1     0xCA                   //定义激光脉宽调制器时基计数器TH1  
#define LASERITH           0.1                    //输出电流阀值
#define CH1MIXCUR          0.1					  //定义一通道最小电流
#define CH2MIXCUR          0.1					  //定义一通道最大电流
//
#define LASER_CHANNEL_1														0
#define LASER_CHANNEL_2														1
//制冷器使能
#define SET_TEC_PWM(b)														HAL_GPIO_WritePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin, b)
#define FLIP_TEC_PWM()														HAL_GPIO_TogglePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin)
#define GET_TEC_PWM()															HAL_GPIO_ReadPin(TEC_OUT_GPIO_Port, TEC_OUT_Pin)
//锁定指示灯
#define SET_POWER_LED(b)													HAL_GPIO_WritePin(POWER_LED_OUT_GPIO_Port, POWER_LED_OUT_Pin, b)
#define FLIP_POWER_LED()													HAL_GPIO_TogglePin(POWER_LED_OUT_GPIO_Port, POWER_LED_OUT_Pin)
#define GET_POWER_LED()														HAL_GPIO_ReadPin(POWER_LED_OUT_GPIO_Port, POWER_LED_OUT_Pin)
//报警指示灯
#define SET_ALARM_LED(b)													HAL_GPIO_WritePin(ALARM_LED_OUT_GPIO_Port, ALARM_LED_OUT_Pin, b)
#define FLIP_ALARM_LED()													HAL_GPIO_TogglePin(ALARM_LED_OUT_GPIO_Port, ALARM_LED_OUT_Pin)
#define GET_ALARM_LED()														HAL_GPIO_ReadPin(ALARM_LED_OUT_GPIO_Port, ALARM_LED_OUT_Pin)
//通道1激光发射指示
#define SET_LASER1_LED(b)													HAL_GPIO_WritePin(LASER0_LED_OUT_GPIO_Port, LASER0_LED_OUT_Pin, b)
#define FLIP_LASER1_LED()													HAL_GPIO_TogglePin(LASER0_LED_OUT_GPIO_Port, LASER0_LED_OUT_Pin)
#define GET_LASER1_LED()													HAL_GPIO_ReadPin(LASER0_LED_OUT_GPIO_Port, LASER0_LED_OUT_Pin)
//通道2激光发射指示
#define SET_LASER2_LED(b)													HAL_GPIO_WritePin(LASER1_LED_OUT_GPIO_Port, LASER1_LED_OUT_Pin, b)
#define FLIP_LASER2_LED()													HAL_GPIO_TogglePin(LASER1_LED_OUT_GPIO_Port, LASER1_LED_OUT_Pin)
#define GET_LASER2_LED()													HAL_GPIO_ReadPin(LASER1_LED_OUT_GPIO_Port, LASER1_LED_OUT_Pin)
//板载心跳LED
#define SET_TICK_LED(b)														HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, b)
#define FLIP_TICK_LED()														HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define GET_TICK_LED()														HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
//板载错误LED
#define SET_ERR_LED(b)														HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, b)
#define FLIP_ERR_LED(b)														HAL_GPIO_TogglePin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define GET_ERR_LED()															HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
//通道1指示光
#define SET_LASER1_AIM(b)													HAL_GPIO_WritePin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin, b)
#define FLIP_LASER1_AIM()													HAL_GPIO_TogglePin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin)
#define GET_LASER1_AIM()													HAL_GPIO_ReadPin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin)
//通道2指示光
#define SET_LASER2_AIM(b)													HAL_GPIO_WritePin(LASER2_AIM_GPIO_Port, LASER2_AIM_Pin, b)
#define FLIP_LASER2_AIM()													HAL_GPIO_TogglePin(LASER2_AIM_GPIO_Port, LASER2_AIM_Pin)
#define GET_LASER2_AIM()													HAL_GPIO_ReadPin(LASER2_AIM_GPIO_Port, LASER2_AIM_Pin)
//联锁
#define GET_INTERLOCK()														HAL_GPIO_ReadPin(INTERLOCK_IN_GPIO_Port, INTERLOCK_IN_Pin)
//急停
#define GET_ESTOP()																HAL_GPIO_ReadPin(ESTOP_IN_GPIO_Port, ESTOP_IN_Pin)
//通道1外控触发						
#define GET_LASER1_TRG()													HAL_GPIO_ReadPin(LASER0_ON_IN_GPIO_Port, LASER0_ON_IN_Pin)
//通道2外控触发
#define GET_LASER2_TRG()													HAL_GPIO_ReadPin(LASER1_ON_IN_GPIO_Port, LASER1_ON_IN_Pin)
//DC-DC变换器风扇
#define SET_FAN5V(b)															HAL_GPIO_WritePin(FAN5V_OUT_GPIO_Port, FAN5V_OUT_Pin, b)
#define FLIP_FAN5V()															HAL_GPIO_TogglePin(FAN5V_OUT_GPIO_Port, FAN5V_OUT_Pin)
#define GET_FAN5V()																HAL_GPIO_ReadPin(FAN5V_OUT_GPIO_Port, FAN5V_OUT_Pin)
//DC-DC变换器使能
#define SET_LASER_PWM(b)															HAL_GPIO_WritePin(LASER1_AIM_GPIO_Port, LASER1_AIM_Pin, b)
#define FLIP_LASER_PWM()															HAL_GPIO_TogglePin(FAN5V_OUT_GPIO_Port, FAN5V_OUT_Pin)
#define GET_LASER_PWM()															HAL_GPIO_ReadPin(LASER1_ON_IN_GPIO_Port, LASER1_ON_IN_Pin)
//
softTimer_t softTimer;
cmdQueue_t cmdQueue;
laserConfig_t laserConfig;


//UART5
extern UART_HandleTypeDef huart6;
uint8_t uart6_rxDat;
//
void startRcvCmd(cmdQueue_t *p){//接收指令
	p->flagRcvDone = 0;
	p->flagRcving = 0;
	p->rcvNum = 0;
	memset(p->rcvBuf, 0x0, sizeof(p->rcvBuf));
	HAL_UART_Receive_IT(&huart6, &uart6_rxDat, 1);
}
void startSendCmd(cmdQueue_t *p){//发送命令
	p->flagSendDone = 0;
	p->flagSending = 1;
	HAL_UART_Transmit_IT(&huart6, p->sendBuf, p->sendNum);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	cmdQueue_t *p = &cmdQueue;
	if(huart == &huart6){
		p->flagSending = 0;
		p->flagSendDone = 1;		
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	cmdQueue_t *p = &cmdQueue;
	if(huart == &huart6){
		if((uart6_rxDat == 'A') || (uart6_rxDat == 'V') || (uart6_rxDat == 'L') || (uart6_rxDat == 'T') || (uart6_rxDat == 'G') || (uart6_rxDat == 'R')){ //接收到A,V,L,T,G指令
			memset(p->rcvBuf, 0x00, 256);
			p->pRcvWriteIndex = p->rcvBuf;
			p->flagRcving = 1;
			p->flagRcvDone = 0;
			p->rcvNum = 0;
			HAL_UART_Receive_IT(&huart6, &uart6_rxDat, 1);
		}
		else if(uart6_rxDat == 'E'){ //接收到E 结束队列
			*(p->pRcvWriteIndex) = uart6_rxDat;  
			p->rcvNum ++;
			p->pRcvWriteIndex = p->rcvBuf;
			p->flagRcvDone = 1;
			p->flagRcving = 0;
		}      
		if(p->flagRcving){ 
			*(p->pRcvWriteIndex) = uart6_rxDat;      
      if(p->pRcvWriteIndex == (p->rcvBuf + 256 - 1)){
				p->pRcvWriteIndex = p->rcvBuf;  
      }
      else{
				p->pRcvWriteIndex ++;
      }
			p->rcvNum ++;
			HAL_UART_Receive_IT(&huart6, &uart6_rxDat, 1);
		}
	}
}


/**********************************************g*******************************************/
//串口指令处理程序                                                                      **/
//A指令设置电流与占空比      				A061B010C050D060E                                   **/
//通道1 电流6.1A占空比10% 通道2 电流5.0A占空比60%                                       **/
//L指令发射关闭激光设置      L00E   / L01E                                              **/
//                        关闭激光  /打开激光                                            */
//V指令锁定设置              V00E   / V01E                                               */
//锁定不接受任何参数改变      锁    / 解锁                                               */
//T指令设定出关时间         T010E                          / T000E                       */
//                         shot指令收到后出光10秒后自动关闭/时间等于000时一直出光        */
//G指令打开引导光          G10E/G11E/G20E/G21E/                                          */
//00:关闭通道1指示光/01:开启通道1指示光/10:关闭通道2指示光/11:开启通道2指示光            */
//R指令返回各通道温控参数                                                                */
//R00E                                                                                   */
/*****************************************************************************************/                                         
void processCmd(cmdQueue_t *p, laserConfig_t* s){//自由协议命令处理 
	int16_t temp16;
	uint16_t utmp16;
	if(p->flagRcvDone){//接收完成
		if(p->rcvBuf[0] == 'A'){//检测到A指令且不再锁定态调节设置
			//检测到调节 A 命令
			
			//设置通道1电流
			temp16 = ( p->rcvBuf[1] - 0x30 ) * 100 + ( p->rcvBuf[2] - 0x30 ) * 10 + ( p->rcvBuf[3] - 0x30 );
			if(temp16 >= 1000){
				temp16 = 1000;
			}
			if(temp16 < 0){
				temp16 = 0;
			}
			s->writeLaserCur[LASER_CHANNEL_1] = temp16;
			//设定通道2电流
			temp16 = (p->rcvBuf[9] - 0x30) * 100 + ( p->rcvBuf[10] - 0x30 ) * 10 + ( p->rcvBuf[11] - 0x30 );
			if(temp16 >= 1000){ 
				temp16 = 1000; 
			}
			if(temp16 < 0){
				temp16 = 0;
			}	
			s->writeLaserCur[LASER_CHANNEL_2] = temp16;
			//设置通道1占空比
			temp16 = (p->rcvBuf[5] - 0x30) * 100 + (p->rcvBuf[6] - 0x30) * 10 + (p->rcvBuf[7] - 0x30);
			//限定PWM 占空比在0-100%
			if(temp16 < 0 ){
				temp16 = 0;
			}
			if(temp16 >= 100){
				temp16 = 100;
			}
			s->writeLaserPwm[LASER_CHANNEL_1] = 0;//设定CH1 占空比
			//执行NULL
			
			//设置通道2占空比 	
			temp16 = (p->rcvBuf[13] - 0x30) * 100 + (p->rcvBuf[14] - 0x30) * 10 + (p->rcvBuf[15] - 0x30);
			//限定PWM 占空比在0-100%
			if(temp16 < 0 ){
				temp16 = 0;
			}
			if(temp16 >= 100){
				temp16 = 100;
			}
			s->writeLaserPwm[LASER_CHANNEL_2] = 0;//设定CH1 占空比
			//执行NULL
			//返回响应
			memset(p->sendBuf, 0x00, 256);
			p->sendBuf[0] = 'C';
			p->sendBuf[1] = 'A';
			p->sendBuf[2] = 13; //回车
			p->sendNum = 3;
			startSendCmd(p);
		}
		if(p->rcvBuf[0] == 'L'){//激光发射指令
			//执行V 命令
			temp16 =  (p->rcvBuf[1] - 0x30 ) + (p->rcvBuf[2] - 0x30 );
			if(temp16){//wtemp == 1 StartShot=1 出光触发置高准备出光
				if(s->writeLaserCur[LASER_CHANNEL_1] > 0){
					utmp16 = (uint16_t)((float)s->writeLaserCur[LASER_CHANNEL_1] / 1000 * 65535);
					dac8568WriteReg(0, utmp16);
				}
				else{
					dac8568WriteReg(0, 0);
				}
				
				if(s->writeLaserCur[LASER_CHANNEL_2] > 0){
					utmp16 = (uint16_t)((float)s->writeLaserCur[LASER_CHANNEL_2] / 1000 * 65535);
					dac8568WriteReg(1, utmp16);
				}
				else{
					dac8568WriteReg(1, 0);
				}
				SET_LASER_PWM(GPIO_PIN_SET);	//打开激光
				if(s->writeLaserOnTime > 0){//启动计时器
					softTimer.counter = 0;
					softTimer.mate = s->writeLaserOnTime;
					softTimer.start = 1;//启动计时器
				}
			}
			else {//wtemp == 0 立即关闭出光
				dac8568WriteReg(0, 0);
				dac8568WriteReg(1, 0);
				SET_LASER_PWM(GPIO_PIN_RESET);//关闭激光
			}
			memset(p->sendBuf, 0x00, sizeof(p->sendBuf));
			p->sendBuf[0] = 'L';
			p->sendBuf[1]	= 'A';
			p->sendBuf[2] = 13; //回车
			p->sendNum = 3;
			startSendCmd(p); 	       
		}
		if(p->rcvBuf[0] == 'G'){//Command G Aimingcnt 指示光控制
			temp16 = ( p->rcvBuf[1] - 0x30 * 10 ) + ( p->rcvBuf[2] - 0x30 );
			switch(temp16){
				case 10:{//通道1关闭指示光
					s->writeLaserAim[LASER_CHANNEL_1] = 0;
					SET_LASER1_AIM(GPIO_PIN_RESET);
					break;
				}
				case 11:{//通道1打开指示光
					s->writeLaserAim[LASER_CHANNEL_1] = 1;
					SET_LASER1_AIM(GPIO_PIN_SET);
					break;
				}
				case 20:{//通道2关闭指示光
					s->writeLaserAim[LASER_CHANNEL_2] = 0;
					SET_LASER2_AIM(GPIO_PIN_RESET);
					break;
				}
				case 21:{//通道2打开指示光
					s->writeLaserAim[LASER_CHANNEL_2] = 1;
					SET_LASER2_AIM(GPIO_PIN_SET);
					break;
				}
				default:break;
			}
			memset(p->sendBuf, 0x00, 256);
			p->sendBuf[0] = 'G';
			p->sendBuf[1] = 'A';
			p->sendBuf[2] = 13; //回车
			p->sendNum = 3;
			startSendCmd(p);
		}
		if(p->rcvBuf[0] == 'T'){//Command T  指示设置出光时间
			//将串口时间指令送入Runouttime全局变量
  		temp16 = ((p->rcvBuf[1] - 0x30) * 100) + ((p->rcvBuf[2] - 0x30) * 10) + (p->rcvBuf[3] - 0x30);
  		if(temp16 <= 0){
				temp16 = 0;
			}
  		if(temp16 >= 999){
				temp16 = 999;//限制时间在[0,999]
			}
  		s->writeLaserOnTime = temp16 * 100;//计算ms值
  		/*回执响应*/
			memset(p->sendBuf, 0x00, 256);
			p->sendBuf[0] = 'G';
			p->sendBuf[1] = 'A';
			p->sendBuf[2] = 13; //回车
			p->sendNum = 3;
			startSendCmd(p);
		}
		if(p->rcvBuf[0] == 'R'){//Command R  返回激光器参数 实际工作电流 + PD + 温度
		 	memset(p->sendBuf, 0x00, 256);
			//memset(SendBuf,0x00,SerialRCV);
			//sprintf(SendBuf,"T1:%3.1f P1:%3.2f T2:%3.1f P2:%3.2f\n",CH1_TEMP,CH1_DOUT,CH2_TEMP,CH2_DOUT);
			//sprintf(SendBuf,"RQ");
     //StarSendUart0();
		}
		p->flagRcvDone = 0;
		HAL_UART_Receive_IT(&huart6, &uart6_rxDat, 1);//重启串口指令接收
	}
	if(softTimer.counter > softTimer.mate){//计时器溢出
		softTimer.start = 0;
		dac8568WriteReg(0, 0);
		dac8568WriteReg(1, 0);
		SET_LASER_PWM(GPIO_PIN_RESET);//关闭激光
	}
}


void mainApp(void){
	cmdQueue_t *p = &cmdQueue;
	p->sendBuf[0] = 'R';
	p->sendBuf[1] = 'S';
	p->sendBuf[2] = 'T';
	p->sendBuf[3] = 13;
	p->sendNum = 4;
	startSendCmd(p);
	startRcvCmd(&cmdQueue);
	while(1){
		processCmd(&cmdQueue, &laserConfig);
	}
}
