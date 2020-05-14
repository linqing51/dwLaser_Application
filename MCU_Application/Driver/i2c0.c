#include "i2c0.h"
/*****************************************************************************/		
static void setSCL0(uint8_t s){//P7_2
	data uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE   = CONFIG_PAGE;
	if(s)
		P7 |= (1 << 2);
	else
		P7 &= ~((uint8_t)(1 << 2));
	SFRPAGE = SFRPAGE_SAVE;// Restore SFRPAGE
}
static void setSDA0(uint8_t s){//P7_3
	data uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE   = CONFIG_PAGE;
	if(s)
		P7 |= (uint8_t)(1 << 3);
	else
		P7 &= ~((uint8_t)(1 << 3));
	SFRPAGE = SFRPAGE_SAVE;             // Restore SFRPAGE
}
static uint8_t getSCL0(void){
	data uint8_t temp;
	data uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE   = CONFIG_PAGE;
	temp = (P7 >> 2) & 0x01;
	SFRPAGE = SFRPAGE_SAVE;        
	return temp;
}
static uint8_t getSDA0(void){
	data uint8_t temp;
	data uint8_t SFRPAGE_SAVE = SFRPAGE;// Save Current SFR page
    SFRPAGE   = CONFIG_PAGE;
	temp = (P7 >> 3) & 0x01;
	SFRPAGE = SFRPAGE_SAVE;        
	return temp;
}
void iic0Start(void){//����IIC��ʼ�ź�
	setSDA0(1);	  	  
	setSCL0(1);
	delayUs(CONFIG_I2C0_FREQ);
 	setSDA0(0);//START:when CLK is high,DATA change form high to low 
	delayUs(CONFIG_I2C0_FREQ);
	setSCL0(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
void iic0Stop(void){//����IICֹͣ�ź�
	setSCL0(0);
	setSDA0(0);//STOP:when CLK is high DATA change form low to high
 	delayUs(CONFIG_I2C0_FREQ);
	setSCL0(1); 
	setSDA0(1);//����I2C���߽����ź�
	delayUs(CONFIG_I2C0_FREQ);							   	
}

uint8_t iic0WaitAck(void){
//�������ݺ󣬵ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ�ܣ�IICֱ���˳�
//        0������Ӧ��ɹ���ʲô������
	data uint8_t ucErrTime=0;  
	setSDA0(1);
	delayUs(1);	   
	setSCL0(1);
	delayUs(1);	 
	while(getSDA0()){
		ucErrTime ++;
		if(ucErrTime >= CONFIG_I2C_WAITACT_TIME){
			iic0Stop();
			return 1;
		}
	}
	setSCL0(0);    //ʱ�����0 	   
	return 0;  
}
void iic0Ack(void){//����ACKӦ��
	setSCL0(0);
	setSDA0(0);
	delayUs(CONFIG_I2C0_FREQ);
	setSCL0(1);
	delayUs(CONFIG_I2C0_FREQ);
	setSCL0(0);
}
	    
void iic0NAck(void){//������ACKӦ��	
	setSCL0(0);
	setSDA0(1);
	delayUs(CONFIG_I2C0_FREQ);
	setSCL0(1);
	delayUs(CONFIG_I2C0_FREQ);
	setSCL0(0);
}					 				     	  
void iic0SendByte(uint8_t txd){//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��                        
    data uint8_t t;    	    
    setSCL0(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t = 0;t < 8;t ++)
    {              
        //SDA0=(txd&0x80)>>7;
		if((txd & 0x80) >> 7)
			setSDA0(1);
		else
			setSDA0(0);
		txd <<= 1; 	  
		delayUs(CONFIG_I2C0_FREQ);
		setSCL0(1);
		delayUs(CONFIG_I2C0_FREQ); 
		setSCL0(0);	
		delayUs(CONFIG_I2C0_FREQ);
    }	 
} 	    
  
uint8_t iic0ReadByte(uint8_t ack){//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK 
	data uint8_t i, receive=0;
    for(i=0;i<8;i++ ){
        setSCL0(0); 
        delayUs(CONFIG_I2C0_FREQ);
		setSCL0(1);
        receive <<= 1;
        if(getSDA0())
			receive ++;   
		delayUs(CONFIG_I2C0_FREQ); 
    }					 
    if(!ack)
        iic0NAck();        //����nACK
    else
        iic0Ack();         //����ACK   
    return receive;
}
