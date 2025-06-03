#include <SimpleTimer.h>
#include <Adafruit_SleepyDog.h>
int EC_PWR_KEY = 4;   //
int EC_STOP_KEY = 5;  //
int EC_PWR_LED = 3;

int EC_24V_ON = 6;
int EC_5V_ON = 8;
int EC_12V_ON = 7;
int MCU_ESTOP = 9;
int MPU_SLEEP = 0;
int MPU_RESET = 1;
int MPU_SHUTDOWN = 2;

char KeyPwrOn_0, KeyPwrOn_1;                  //电源开关按键状态
char KeyEmergencyStop_0, KeyEmergencyStop_1;  //急停开关按键状态
char FlagPwrOnLaser, FlagPwrOnMcu, FlagPwrOnLcd, FlagStopLaser;
int KeyPwrOnCounter;
// Create a first timer and specify its interval in milliseconds
SimpleTimer keyTimer;
void setup() {
  // put your setup code here, to run once:
  KeyPwrOn_0 = 0;
  KeyPwrOn_1 = 0;
  KeyEmergencyStop_0 = 0;
  KeyEmergencyStop_1 = 0;
  FlagPwrOnLaser = 0;
  FlagPwrOnMcu = 0;
  FlagPwrOnLcd = 0;
  FlagStopLaser = 0;
  Serial.begin(115200);
  pinMode(EC_PWR_KEY, INPUT);
  pinMode(EC_STOP_KEY, INPUT);
  pinMode(EC_PWR_LED, OUTPUT);
  pinMode(EC_24V_ON, OUTPUT);
  pinMode(EC_5V_ON, OUTPUT);
  pinMode(EC_12V_ON, OUTPUT);
  pinMode(MCU_ESTOP, OUTPUT);
  digitalWrite(EC_24V_ON, LOW);   //关闭主电源24V
  digitalWrite(EC_5V_ON, LOW);    //关闭5V供电
  digitalWrite(EC_12V_ON, LOW);   //关闭12V供电
  digitalWrite(EC_PWR_LED, LOW);  //关闭电源指示灯
  keyTimer.setInterval(10);       //计时器间隔时间10ms
  delay(1000);
  Watchdog.enable(100);
  Serial.println("Enabled the watchdog with 100ms");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (keyTimer.isReady()) {
    KeyPwrOn_0 = digitalRead(EC_PWR_KEY);
    KeyEmergencyStop_0 = digitalRead(EC_STOP_KEY);
    if (KeyPwrOn_0 == KeyPwrOn_1) {
      if (KeyPwrOn_0) {
        FlagPwrOnLaser = 0;
        FlagPwrOnMcu = 0;
        FlagPwrOnLcd = 0;
      } else {
        FlagPwrOnLaser = 1;
        FlagPwrOnMcu = 1;
        FlagPwrOnLcd = 1;
      }
    }
    if (KeyEmergencyStop_0 == KeyEmergencyStop_1) {
      if (KeyEmergencyStop_0) {
        FlagStopLaser = 0;
      } else {
        FlagStopLaser = 1;
      }
    }
    KeyPwrOn_1 = KeyPwrOn_0;
    KeyEmergencyStop_1 = KeyEmergencyStop_0;
    keyTimer.reset();
  }
  if (FlagPwrOnLaser) {
    digitalWrite(EC_24V_ON, HIGH);//打开24V供电
    digitalWrite(EC_PWR_LED, HIGH);//打开电源指示灯
  } else {
    digitalWrite(EC_24V_ON, LOW);
    digitalWrite(EC_PWR_LED, LOW);
  }
  if (FlagPwrOnMcu) {
    digitalWrite(EC_5V_ON, HIGH);  //打开5V供电
  } else {
    digitalWrite(EC_5V_ON, LOW);
  }
  if (FlagPwrOnLcd) {
    digitalWrite(EC_12V_ON, HIGH);  //打开12V供电
  } else {
    digitalWrite(EC_12V_ON, LOW);
  }
  if (FlagStopLaser) {
    digitalWrite(MCU_ESTOP, LOW);  //急停低电平有效
  } else {
    digitalWrite(MCU_ESTOP, HIGH);
  }
  Watchdog.reset();
}
