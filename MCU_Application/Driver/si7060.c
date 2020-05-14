#include "si7060.h"
/*****************************************************************************/
uint8_t si7060ReadValue(const uint8_t registerAdd){ 																 
	uint8_t temp=0;	
	iic1Start();  
	iic1SendByte((I2C_ADDRESS_SI7060_00 << 1) & 0xFE);//����д����
	iic1WaitAck();
	iic1SendByte(registerAdd);//���͸ߵ�ַ		 
	iic1WaitAck(); 

	iic1Start();  	 	   
	iic1SendByte(((I2C_ADDRESS_SI7060_00 << 1) | 0x01));//�������ģʽ			   
	iic1WaitAck();	 
	temp = iic1ReadByte(0);//��һ���ֽڣ���Ӧ���ź��ź�	   
	iic1NAck();
	iic1Stop();        //����һ��ֹͣ����
	return temp;
}
void si7060WriteValue(const uint8_t registerAdd, const uint8_t value){
	iic1Start(); 
	iic0SendByte((I2C_ADDRESS_SI7060_00 << 1) & 0xFE);//����д����
	iic0WaitAck();
	iic0SendByte(registerAdd);
	iic0WaitAck();
	iic0SendByte(value);
	iic0WaitAck();	   
	iic0Stop();//����һ��ֹͣ���� 
}
void si7060Init(void){//SI7060��ʼ��
	uint8_t ret;
	ret = si7060ReadValue(CMD_SI7060_ID);
	if(ret != 0x14){
		SET(SPCOIL_SI7060_INIT_FAIL);
	}
	else{
		RES(SPCOIL_SI7060_INIT_FAIL);
	}
	ret = si7060ReadValue(CMD_SI7060_meas);
	 // Prepare Mesure
	si7060WriteValue(CMD_SI7060_meas,0x04);
	ret = si7060ReadValue(CMD_SI7060_meas);
	si7060WriteValue(CMD_SI7060_sw_op,0x4E);
	si7060WriteValue(CMD_SI7060_sw_hyst,0x1C);
}
int16_t si7060ReadTemperature(void){
	fp32_t temp;
	uint8_t dspsigm;
	uint8_t dspsigl;
	uint8_t ret;
	ret = si7060ReadValue(CMD_SI7060_Dspsigm);
	dspsigm = (ret&0x7F);
	ret = si7060ReadValue(CMD_SI7060_Dspsigl);
	dspsigl = ret;
	temp = 55+ ((float)(256*dspsigm)+(float)(dspsigl-16384))/160;
	return (int16_t)(temp*10);
}


void sI7060Sleep() {
  // Prepare Mesure
  si7060WriteValue(CMD_SI7060_meas,0x01);
}



