#include "Adafruit_Debounce.h"
int EC_PWR_KEY = 4;//
int EC_STOP_KEY = 5;//
int EC_PWR_LED = 3;
int EC_PWR_ON = 6;
int EC_5V_ON = 8;
int EC_12V_ON = 7;
int MCU_ESTOP = 9;
int MPU_SLEEP = 0;
int MPU_RESET = 1;
int MPU_SHUTDOWN = 2;


Adafruit_Debounce powerKey(EC_PWR_KEY, LOW);
Adafruit_Debounce estopKey(EC_STOP_KEY, LOW);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(EC_PWR_KEY, INPUT);
  pinMode(EC_STOP_KEY, INPUT);
  pinMode(EC_PWR_LED, OUTPUT);
  powerKey.begin();
  estopKey.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  powerKey.update();
  estopKey.update();
  if(powerKey.isPressed()){
    digitalWrite(EC_PWR_ON, HIGH);//打开主电源24V
    digitalWrite(EC_5V_ON, HIGH);//打开5V供电
    digitalWrite(EC_12V_ON, HIGH);//打开12V供电  
    //Serial.println("Power Key is pressed!");
  }
  if(estopKey.isPressed()){
    digitalWrite(MCU_ESTOP, LOW);
    //Serial.println("Emergency Stop key is pressed!");
  }
  if(estopKey.isReleased()){
    digitalWrite(MCU_ESTOP, HIGH);
    //Serial.println("Emergency Stop key is Released!");
  }
}
