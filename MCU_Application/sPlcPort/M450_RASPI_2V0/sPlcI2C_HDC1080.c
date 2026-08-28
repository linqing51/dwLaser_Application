#include "sPlcI2C_hdc1080.h"
/*****************************************************************************/
#define HDC1080_ADDR                0x40 << 1  // I2C地址左移一位（HAL库格式）
#define HDC1080_TEMP_REG            0x00        // 温度寄存器
#define HDC1080_HUMI_REG            0x01        // 湿度寄存器
#define HDC1080_CONFIG_REG          0x02        // 配置寄存器
/*****************************************************************************/
inline static void hdc1080_siic_start(void);// I2C起始信号
inline static void hdc1080_siic_stop(void);// I2C停止信号
inline static void hdc1080_siic_ack(void);// 发送应答信号
inline static uint8_t hdc1080_siic_wait_ack(void);// 等待应答信号
inline static void hdc1080_siic_nack(void);//I2C 不响应
inline static void hdc1080_siic_send_byte(uint8_t data);// 发送一个字节
inline static uint8_t hdc1080_siic_read_byte(uint8_t ack);// 读取一个字节
/*****************************************************************************/
inline static void hdc1080_siic_start(void){//发送I2C起始信号
	/*    _____
	 *SDA      \_____________
	 *    __________
	 *SCL           \________
	 */
	//SDA =1
	SET_HDC1080_SDA(GPIO_PIN_SET);	
	//SCL =1
	SET_HDC1080_SCL(GPIO_PIN_SET);	
	softDelayUs(HDC1080_SOFTI2C_DELAY);
	//SDA = 0
	SET_HDC1080_SDA(GPIO_PIN_RESET);	
	softDelayUs(HDC1080_SOFTI2C_DELAY);
	//SCL = 0
	SET_HDC1080_SCL(GPIO_PIN_RESET);	
	softDelayUs(HDC1080_SOFTI2C_DELAY);
}

inline static void hdc1080_siic_stop(void){//发送I2C停止信号
	/*               _______
	 *SDA __________/
	 *          ____________
	 *SCL _____/
	 */
	//SDA = 0
	SET_HDC1080_SDA(GPIO_PIN_RESET);	
	//SCL = 1
	SET_HDC1080_SCL(GPIO_PIN_SET);	
	softDelayUs(HDC1080_SOFTI2C_DELAY);
	//SDA = 1
	SET_HDC1080_SDA(GPIO_PIN_SET);
	softDelayUs(HDC1080_SOFTI2C_DELAY);
}

inline static uint8_t hdc1080_siic_wait_ack(void){//等待从机应答
	uint32_t timeout = 0;
	SET_HDC1080_SDA(GPIO_PIN_SET);//SDA = 1	
	softDelayUs(HDC1080_SOFTI2C_DELAY);
	SET_HDC1080_SCL(GPIO_PIN_SET);//SCL = 1
	softDelayUs(HDC1080_SOFTI2C_DELAY);
	while(GET_HDC1080_SDA){
		timeout++;
		if(timeout > 200000){
			return 0;
		}
	}
	
	SET_HDC1080_SCL(GPIO_PIN_RESET);//SCL = 0
	softDelayUs(HDC1080_SOFTI2C_DELAY);
	return 1;
}

inline static void hdc1080_siic_ack(void){//发送应答信号
   /*           ____
     *SCL ______/    \______
     *    ____         _____
     *SDA     \_______/
     */
	//SDA = 0
  SET_HDC1080_SDA(GPIO_PIN_RESET);
  softDelayUs(HDC1080_SOFTI2C_DELAY);
	//SCL = 1
	SET_HDC1080_SCL(GPIO_PIN_SET);
	softDelayUs(HDC1080_SOFTI2C_DELAY);
  //SCL = 0
	SET_HDC1080_SCL(GPIO_PIN_RESET);
  softDelayUs(HDC1080_SOFTI2C_DELAY);
  //SDA = 1
	SET_HDC1080_SDA(GPIO_PIN_SET);
}

inline void hdc1080_siic_nack(void){//I2C 不响应
    /*           ____
     *SCL ______/    \______
     *    __________________
     *SDA
     */
	//SDA = 1
	SET_HDC1080_SDA(GPIO_PIN_SET);
	softDelayUs(HDC1080_SOFTI2C_DELAY);
  //SCL = 1
	SET_HDC1080_SCL(GPIO_PIN_SET);
	softDelayUs(HDC1080_SOFTI2C_DELAY); 
	//SCL = 0
	SET_HDC1080_SCL(GPIO_PIN_RESET);
	softDelayUs(HDC1080_SOFTI2C_DELAY);
}

void hdc1080_siic_send_byte(uint8_t data){//发送一个字节
	uint8_t i;
	for(i = 0; i < 8; i++){
		if(data & 0x80){
			//SDA = 1
			SET_HDC1080_SDA(GPIO_PIN_SET);
		}
		else{
			//SDA = 0
			SET_HDC1080_SDA(GPIO_PIN_RESET);
		}
		softDelayUs(HDC1080_SOFTI2C_DELAY); 
		//SCL = 1
		SET_HDC1080_SCL(GPIO_PIN_SET);
		softDelayUs(HDC1080_SOFTI2C_DELAY);
		//SCL = 0
		SET_HDC1080_SCL(GPIO_PIN_RESET);
		if(i == 7){
			//SDA
			SET_HDC1080_SDA(GPIO_PIN_SET);
		}
		data <<= 1;
		softDelayUs(HDC1080_SOFTI2C_DELAY);
	}
}

uint8_t hdc1080_siic_read_byte(uint8_t ack){//读取一个字节
	uint8_t i, data = 0;
	for(i = 0; i < 8; i++ ){
		data <<= 1;
		SET_HDC1080_SCL(GPIO_PIN_RESET);	//SCL = 0
		SET_HDC1080_SCL(GPIO_PIN_SET);//SCL = 1
		softDelayUs(HDC1080_SOFTI2C_DELAY);
		if(GET_HDC1080_SDA){
			data++;
		}
		//SCL = 0
		SET_HDC1080_SCL(GPIO_PIN_RESET);
		softDelayUs(HDC1080_SOFTI2C_DELAY);
	}
	return data;
}

uint8_t hdc1080_init(void){//初始化HDC1080
	uint8_t config = 0x00;
	// 发送起始信号
	hdc1080_siic_start();
	// 发送设备地址+写命令
	hdc1080_siic_send_byte(HDC1080_ADDR);
	if(hdc1080_siic_wait_ack()){ 
		return true;
	}
	// 发送配置寄存器地址
	hdc1080_siic_send_byte(HDC1080_CONFIG_REG);
	hdc1080_siic_wait_ack();

	// 配置寄存器高字节（14位分辨率，同时测量温湿度）
	config = 0x10;  // BIT4=1：同时测量温度和湿度
	hdc1080_siic_send_byte(config);
	hdc1080_siic_wait_ack();

	// 配置寄存器低字节
	hdc1080_siic_send_byte(0x00);
	hdc1080_siic_wait_ack();

	// 发送停止信号
	hdc1080_siic_stop();
	softDelayUs(20);// 等待配置生效
	return 0;
}

void hdc1080_read(int16_t *temp, int16_t *humi){//读取温湿度数据
	uint8_t buf[4];
	uint16_t temp_raw, humi_raw;

	// 发送起始信号
	hdc1080_siic_start();
	// 发送设备地址+写命令
	hdc1080_siic_send_byte(HDC1080_ADDR);
	hdc1080_siic_wait_ack();
	// 发送温度寄存器地址（触发测量）
	hdc1080_siic_send_byte(HDC1080_TEMP_REG);
	hdc1080_siic_wait_ack();
	// 发送停止信号
	hdc1080_siic_stop();
	HAL_Delay(20);  // 等待测量完成（HDC1080转换时间最大14ms）
	// 发送起始信号
	hdc1080_siic_start();
	// 发送设备地址+读命令
	hdc1080_siic_send_byte(HDC1080_ADDR | 0x01);
	hdc1080_siic_wait_ack();

	// 读取温度高字节
	buf[0] = hdc1080_siic_read_byte(0);
	hdc1080_siic_ack();
	// 读取温度低字节
	buf[1] = hdc1080_siic_read_byte(0);
	hdc1080_siic_ack();
	// 读取湿度高字节
	buf[2] = hdc1080_siic_read_byte(0);
	hdc1080_siic_ack();
	// 读取湿度低字节
	buf[3] = hdc1080_siic_read_byte(1);
	hdc1080_siic_nack();
	// 发送停止信号
	hdc1080_siic_stop();

	// 转换为实际温度和湿度
	temp_raw = ((uint16_t)buf[0] << 8) | buf[1];
	humi_raw = ((uint16_t)buf[2] << 8) | buf[3];

	*temp = (int16_t)(((temp_raw / 65536.0) * 165.0 - 40.0) * 10);  // 温度计算公式
	*humi = (int16_t)((humi_raw / 65536.0) * 1000.0);         // 湿度计算公式
}
