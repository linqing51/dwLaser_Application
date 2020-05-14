#include "i2c2.h"
/*****************************************************************************/			
/*****************************************************************************/
static void setSCL2(uint8_t s){//P5.4
	uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE   = CONFIG_PAGE;
	if(s)
		P5 |= 0x10;
	else
		P5 &= 0xEF;
	SFRPAGE = SFRPAGE_SAVE;// Restore SFRPAGE
}
static void setSDA2(uint8_t s){//P5.5
	uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE   = CONFIG_PAGE;
	if(s)
		P5 |= 0x20;
	else
		P5 &= 0xDF;
	SFRPAGE = SFRPAGE_SAVE;// Restore SFRPAGE
}
static uint8_t getSCL2(void){//P5.4
	uint8_t temp;
	uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE = CONFIG_PAGE;
	temp = (P5 >> 4) & 0x01;
	SFRPAGE = SFRPAGE_SAVE;
	return temp;
}
static uint8_t getSDA2(void){//P5.5
	uint8_t temp;
	uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE = CONFIG_PAGE;
	temp = (P5 >> 5) & 0x01;
	SFRPAGE = SFRPAGE_SAVE;
	return temp; 
}
void iic2Start(void){//����IIC��ʼ�ź�
	setSDA2(1);	  	  
	setSCL2(1);
	delayUs(CONFIG_I2C2_FREQ);
 	setSDA2(0);//START:when CLK is high,DATA change form high to low 
	delayUs(CONFIG_I2C2_FREQ);
	setSCL2(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
void iic2Stop(void){//����IICֹͣ�ź�
	setSCL2(0);
	setSDA2(0);//STOP:when CLK is high DATA change form low to high
 	delayUs(CONFIG_I2C2_FREQ);
	setSCL2(1); 
	setSDA2(1);//����I2C���߽����ź�
	delayUs(CONFIG_I2C2_FREQ);							   	
}

uint8_t iic2WaitAck(void){
//�������ݺ󣬵ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ�ܣ�IICֱ���˳�
//        0������Ӧ��ɹ���ʲô������
	uint8_t ucErrTime=0;  
	setSDA2(1);
	delayUs(1);	   
	setSCL2(1);
	delayUs(1);	 
	while(getSDA2()){
		ucErrTime ++;
		if(ucErrTime >= CONFIG_I2C_WAITACT_TIME){
			iic2Stop();
			return 1;
		}
	}
	setSCL2(0);    //ʱ�����0 	   
	return 0;  
}
void iic2Ack(void){//����ACKӦ��
	setSCL2(0);
	setSDA2(0);
	delayUs(CONFIG_I2C2_FREQ);
	setSCL2(1);
	delayUs(CONFIG_I2C2_FREQ);
	setSCL2(0);
}
	    
void iic2NAck(void){//������ACKӦ��	
	setSCL2(0);
	setSDA2(1);
	delayUs(CONFIG_I2C2_FREQ);
	setSCL2(1);
	delayUs(CONFIG_I2C2_FREQ);
	setSCL2(0);
}					 				     	  
void iic2SendByte(uint8_t txd){//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��                        
    uint8_t t;    	    
    setSCL2(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t = 0;t < 8;t ++)
    {              
        //SDA2=(txd&0x80)>>7;
		if((txd & 0x80) >> 7)
			setSDA2(1);
		else
			setSDA2(0);
		txd <<= 1; 	  
		delayUs(CONFIG_I2C2_FREQ);
		setSCL2(1);
		delayUs(CONFIG_I2C2_FREQ); 
		setSCL2(0);	
		delayUs(CONFIG_I2C2_FREQ);
    }	 
} 	    
  
uint8_t iic2ReadByte(uint8_t ack){//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK 
	uint8_t i, receive=0;
    for(i=0;i<8;i++ ){
        setSCL2(0); 
        delayUs(CONFIG_I2C2_FREQ);
		setSCL2(1);
        receive <<= 1;
        if(getSDA2())
			receive ++;   
		delayUs(CONFIG_I2C2_FREQ); 
    }					 
    if(!ack)
        iic2NAck();        //����nACK
    else
        iic2Ack();         //����ACK   
    return receive;
}
