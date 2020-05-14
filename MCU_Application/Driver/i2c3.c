#include "i2c3.h"
/*****************************************************************************/				
static void setSCL3(uint8_t s){//P7.6
	uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE   = CONFIG_PAGE;
	if(s)
		P7 |= 0x40;
	else
		P7 &= 0xBF;
	SFRPAGE = SFRPAGE_SAVE;// Restore SFRPAGE
}
static void setSDA3(uint8_t s){//P7.7
	uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE   = CONFIG_PAGE;
	if(s)
		P7 |= 0x80;
	else
		P7 &= 0x7F;
	SFRPAGE = SFRPAGE_SAVE;// Restore SFRPAGE
}
static uint8_t getSCL3(void){//P7.6
	uint8_t temp;
	uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE = CONFIG_PAGE;
	temp = (P7 >> 6) & 0x01;
	SFRPAGE = SFRPAGE_SAVE;
	return temp; 
}
static uint8_t getSDA3(void){//P7.7
	uint8_t temp;
	uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE = CONFIG_PAGE;
	temp = (P7 >> 7) & 0x01;
	SFRPAGE = SFRPAGE_SAVE;
	return temp;  
}
void iic3Start(void){//����IIC��ʼ�ź�
	setSDA3(1);	  	  
	setSCL3(1);
	delayUs(CONFIG_I2C3_FREQ);
 	setSDA3(0);//START:when CLK is high,DATA change form high to low 
	delayUs(CONFIG_I2C3_FREQ);
	setSCL3(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
void iic3Stop(void){//����IICֹͣ�ź�
	setSCL3(0);
	setSDA3(0);//STOP:when CLK is high DATA change form low to high
 	delayUs(CONFIG_I2C3_FREQ);
	setSCL3(1); 
	setSDA3(1);//����I2C���߽����ź�
	delayUs(CONFIG_I2C3_FREQ);							   	
}

uint8_t iic3WaitAck(void){
//�������ݺ󣬵ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ�ܣ�IICֱ���˳�
//        0������Ӧ��ɹ���ʲô������
	uint8_t ucErrTime=0;  
	setSDA3(1);
	delayUs(1);	   
	setSCL3(1);
	delayUs(1);	 
	while(getSDA3()){
		ucErrTime ++;
		if(ucErrTime >= CONFIG_I2C_WAITACT_TIME){
			iic3Stop();
			return 1;
		}
	}
	setSCL3(0);    //ʱ�����0 	   
	return 0;  
}
void iic3Ack(void){//����ACKӦ��
	setSCL3(0);
	setSDA3(0);
	delayUs(CONFIG_I2C3_FREQ);
	setSCL3(1);
	delayUs(CONFIG_I2C3_FREQ);
	setSCL3(0);
}
	    
void iic3NAck(void){//������ACKӦ��	
	setSCL3(0);
	setSDA3(1);
	delayUs(CONFIG_I2C3_FREQ);
	setSCL3(1);
	delayUs(CONFIG_I2C3_FREQ);
	setSCL3(0);
}					 				     	  
void iic3SendByte(uint8_t txd){//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��                        
	uint8_t t;    	    
    setSCL3(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t = 0;t < 8;t ++)
    {              
        //SDA3=(txd&0x80)>>7;
		if((txd & 0x80) >> 7)
			setSDA3(1);
		else
			setSDA3(0);
		txd <<= 1; 	  
		delayUs(CONFIG_I2C3_FREQ);
		setSCL3(1);
		delayUs(CONFIG_I2C3_FREQ); 
		setSCL3(0);	
		delayUs(CONFIG_I2C3_FREQ);
    }	 
} 	    
  
uint8_t iic3ReadByte(uint8_t ack){//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK 
	uint8_t i, receive=0;
    for(i=0;i<8;i++ ){
        setSCL3(0); 
        delayUs(CONFIG_I2C3_FREQ);
		setSCL3(1);
        receive <<= 1;
        if(getSDA3())
			receive ++;   
		delayUs(CONFIG_I2C3_FREQ); 
    }					 
    if(!ack)
        iic3NAck();        //����nACK
    else
        iic3Ack();         //����ACK   
    return receive;
}
