//����Э�����
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
ringBuff_t fpRingBuff_Rx;//����Э����ջ���
freeProtocol_t freeProtocol;
/*****************************************************************************/
static void startSendCmd(void){
	freeProtocol.txDone = 0;
	freeProtocol.txRuning = 1;
	HAL_UART_Transmit_IT(&huart6, freeProtocol.cmdBufTx, freeProtocol.txIndex);
}
void sPlcFreeProtocolInit(void){//����Э���ʼ��
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
void sPlcFreeProtocolProcess(void){//����Э������� 
	int16_t temp16;
	uint8_t rdat;
	char cbuf[8];
	while(1){
		if(sPlcRingBuffPop(&fpRingBuff_Rx, &rdat)){//������
			if((rdat == 'A') || 
				 (rdat == 'V') || 
			   (rdat == 'L') || 
			   (rdat == 'T') || 
				 (rdat == 'G') ||
				 (rdat == 'R') ||
				 (rdat == '$')){//���յ���ʼ�ַ�
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
				 (rdat == '#')){//���յ������ַ�
				freeProtocol.rxRuning = false;
				freeProtocol.rxDone = true;
				freeProtocol.cmdBufRx[freeProtocol.rxIndex] = rdat;
				RRES(Y_ULINK_LED);
				break;
			}
			if(freeProtocol.rxRuning){
				if(freeProtocol.rxIndex < (CONFIG_FREEPROTOCOL_SIZE - 1)){//������δ���
					freeProtocol.cmdBufRx[freeProtocol.rxIndex] = rdat;
					freeProtocol.rxIndex ++;
				}
				else{//����������
					freeProtocol.rxIndex = 0;
					freeProtocol.rxDone = false;
					freeProtocol.rxRuning = false;
				}
				break;
			}
		}
		if(freeProtocol.rxDone){//����Э��������
			if(freeProtocol.cmdBufRx[0] == 'A'){//��⵽Aָ���Ҳ�������̬��������
				if(LDB(R_PARA_LOCK)){
					memset(cbuf, 0x0, 8);
					//����ͨ��1��������
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
					//�趨ͨ��2��������
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
					//����ͨ��1ռ�ձ�
					cbuf[0] = freeProtocol.cmdBufRx[5];
					cbuf[1] = freeProtocol.cmdBufRx[6];
					cbuf[2] = freeProtocol.cmdBufRx[7];
					temp16 = atoi(cbuf);
					//�޶�PWM ռ�ձ���0-100%
					if(temp16 < 0 ){
						temp16 = 0;
					}
					if(temp16 >= 100){
						temp16 = 100;
					}
					NVRAM0[EM_LASER_PWM_CH0] = 0;//�趨ͨ��1 ռ�ձ�
					//����ͨ��2ռ�ձ� 	
					cbuf[0] = freeProtocol.cmdBufRx[13];
					cbuf[1] = freeProtocol.cmdBufRx[14];
					cbuf[2] = freeProtocol.cmdBufRx[15];
					temp16 = atoi(cbuf);
					//�޶�PWM ռ�ձ���0-100%
					if(temp16 < 0 ){
						temp16 = 0;
					}
					if(temp16 >= 100){
						temp16 = 100;
					}
					NVRAM0[EM_LASER_PWM_CH1] = 0;//�趨ͨ��2 ռ�ձ�
					//������Ӧ
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'C';
					freeProtocol.cmdBufTx[1] = 'A';
					freeProtocol.cmdBufTx[2] = 13; //�س�
					freeProtocol.txIndex = 3;
				}
				else{//�쳣��Ӧ
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'C';
					freeProtocol.cmdBufTx[1] = 'F';
					freeProtocol.cmdBufTx[2] = 13; //�س�
					freeProtocol.txIndex = 3;					
				}
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'L'){//���ⷢ��ָ��
				if(LDB(X_EXT_ENABLE)){//�ڿ�ģʽ
					if(freeProtocol.cmdBufRx[1] == '0' && freeProtocol.cmdBufRx[2] == '1'){
						SSET(R_LASER_START);//�򿪼���
					}
					if(freeProtocol.cmdBufRx[1] == '0' && freeProtocol.cmdBufRx[2] == '0'){
						SSET(R_LASER_STOP);//�رռ���
					}
					//���ͷ���ֵ
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'L';
					freeProtocol.cmdBufTx[1] = 'A';
					freeProtocol.cmdBufTx[2] = 13; //�س�
					freeProtocol.txIndex = 3;
				}
				else{//�쳣��Ӧ
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'L';
					freeProtocol.cmdBufTx[1] = 'F';
					freeProtocol.cmdBufTx[2] = 13; //�س�
					freeProtocol.txIndex = 3;
				}
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'G'){//ָʾ�����
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
				//���ͷ���ֵ
				memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
				freeProtocol.cmdBufTx[0] = 'G';
				freeProtocol.cmdBufTx[1] = 'A';
				freeProtocol.cmdBufTx[2] = 13; //�س�
				freeProtocol.txIndex = 3;
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'T'){//ָʾ���ó���ʱ��
				//������ʱ��ָ������Runouttimeȫ�ֱ���
				if(LDB(R_PARA_LOCK)){
					temp16 = atoi((const char*)&freeProtocol.cmdBufRx[1]);
					if(temp16 <= 0){
						temp16 = 0;
					}
					if(temp16 >= 999){
						temp16 = 999;//����ʱ����[0,999]
					}
					NVRAM0[EM_LASER_POSWIDTH] = temp16;//����msֵ			
					//��Ӧ
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'T';
					freeProtocol.cmdBufTx[1] = 'A';
					freeProtocol.cmdBufTx[2] = 13; //�س�
					freeProtocol.txIndex = 3;
				}
				else{//�쳣��Ӧ
					memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
					freeProtocol.cmdBufTx[0] = 'T';
					freeProtocol.cmdBufTx[1] = 'F';
					freeProtocol.cmdBufTx[2] = 13; //�س�
					freeProtocol.txIndex = 3;
				}
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'V'){//��������
				if(freeProtocol.cmdBufRx[1] == '0' && freeProtocol.cmdBufRx[2] == '0'){//00
					RRES(R_PARA_LOCK);
				}
				if(freeProtocol.cmdBufRx[1] == '0' && freeProtocol.cmdBufRx[2] == '1'){//01
					SSET(R_PARA_LOCK);
				}
				memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
				freeProtocol.cmdBufTx[0] = 'V';
				freeProtocol.cmdBufTx[1] = 'A';
				freeProtocol.cmdBufTx[2] = 13; //�س�
				freeProtocol.txIndex = 3;
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == 'R'){//��ȡ�ڲ���Ϣ(����)
				memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
				freeProtocol.cmdBufTx[0] = 'R';
				freeProtocol.cmdBufTx[1] = 'A';
				freeProtocol.cmdBufTx[2] = 13; //�س�
				freeProtocol.txIndex = 3;
				startSendCmd();
			}
			if(freeProtocol.cmdBufRx[0] == '$'){//��չ��ָ��
				memset(cbuf, 0x0, 8);
				cbuf[0] = freeProtocol.cmdBufRx[1];
				cbuf[1] = freeProtocol.cmdBufRx[2];
				temp16 = atoi(cbuf);
				switch(temp16){
					case CMD_GET_LASER_TEMPERATURE:{//��ȡ�������¶� CMD=01
						memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
						sprintf((char*)freeProtocol.cmdBufTx, "$0105%d#%d", NVRAM0[EM_LASER_TEMP], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH1_LD:{//��ȡ������ͨ��1���� LD1 CMD=02
						sprintf((char*)freeProtocol.cmdBufTx, "$0205%d#%d", NVRAM0[EM_LASER_CURRENT_CH0], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH2_LD:{//��ȡ������ͨ��2���� LD2 CMD=03
						sprintf((char*)freeProtocol.cmdBufTx, "$0305%d#%d", NVRAM0[EM_LASER_CURRENT_CH1], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH1_PD:{//��ȡ������ͨ��1���� PD1 CMD=04
						sprintf((char*)freeProtocol.cmdBufTx, "$0405%d#%d", NVRAM0[EM_LASER_PD_CH0], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH2_PD:{//��ȡ������ͨ��2���� PD2 CMD=05
						sprintf((char*)freeProtocol.cmdBufTx, "$0505%d#%d", NVRAM0[EM_LASER_PD_CH0], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_TEC_CH1_CURRENT:{//��ȡ����ͨ��1���� CMD=06
						sprintf((char*)freeProtocol.cmdBufTx, "$0605%d#%d", NVRAM0[EM_LASER_CURRENT_CH2], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_TEC_CH2_CURRENT:{//��ȡ����ͨ��2���� CMD=07
						sprintf((char*)freeProtocol.cmdBufTx, "$0705%d#%d", NVRAM0[EM_LASER_CURRENT_CH3], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}					
					case CMD_GET_LASER_CH1_POWESET:{//��ȡ������ͨ��1�������� CMD=08
						sprintf((char*)freeProtocol.cmdBufTx, "$0805%d#%d", NVRAM0[EM_LASER_POWER_CH0], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_CH2_POWESET:{//��ȡ������ͨ��2�������� CMD=09
						sprintf((char*)freeProtocol.cmdBufTx, "$0905%d#%d", NVRAM0[EM_LASER_POWER_CH1], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_ONTIME:{//��ȡ���ⷢ��ʱ�� CMD=10
						sprintf((char*)freeProtocol.cmdBufTx, "$1005%d#%d", NVRAM0[EM_LASER_POSWIDTH], 13);
						freeProtocol.txIndex = 9;
						startSendCmd();
						break;
					}
					case CMD_GET_LASER_STATUS:{//��ȡ���ⷢ��״̬ CMD=11
						temp16 = 0;
						memset(freeProtocol.cmdBufTx, 0x00, FP_TX_SIZE);
						freeProtocol.cmdBufTx[0] = '$';
						freeProtocol.cmdBufTx[1] = '1';
						freeProtocol.cmdBufTx[2] = '1';
						//����״̬
						if(LD(R_ALRAM)){
							freeProtocol.cmdBufTx[3] = '1';
						}
						else{
							freeProtocol.cmdBufTx[3] = '0';
						}
						//ͨ��2����״̬
						if(LD(Y_LASER2_LED)){
							freeProtocol.cmdBufTx[5] = '1';
						}
						else{
							freeProtocol.cmdBufTx[5] = '0';
						}
						//ͨ��1����״̬
						if(LD(Y_LASER1_LED)){
							freeProtocol.cmdBufTx[6] = '1';
						}
						else{
							freeProtocol.cmdBufTx[6] = '0';
						}
						//ͨ��2ָʾ��״̬
						if(LD(R_AIM_ENABLE_CH1)){
							freeProtocol.cmdBufTx[7] = '1';
						}
						else{
							freeProtocol.cmdBufTx[7] = '0';
						}
						//ͨ��1ָʾ��״̬
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


