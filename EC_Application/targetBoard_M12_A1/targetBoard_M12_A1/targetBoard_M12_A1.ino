#include <AcksenButton.h>
#include <Adafruit_SleepyDog.h>
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
int FLAG_PWRON;



AcksenButton powerKeyBasicButton  = AcksenButton(EC_PWR_KEY, ACKSEN_BUTTON_MODE_NORMAL, 10, INPUT);
AcksenButton estopKeyBasicButton  = AcksenButton(EC_STOP_KEY, ACKSEN_BUTTON_MODE_NORMAL, 10, INPUT);
void setup() {
  // put your setup code here, to run once:
  FLAG_PWRON = 0;
  Serial.begin(115200);
  pinMode(EC_PWR_KEY, INPUT);
  pinMode(EC_STOP_KEY, INPUT);
  pinMode(EC_PWR_LED, OUTPUT);
  pinMode(EC_PWR_ON, OUTPUT );
  pinMode(EC_5V_ON, OUTPUT );
  pinMode(EC_12V_ON, OUTPUT );
  pinMode(MCU_ESTOP, OUTPUT);
  digitalWrite(EC_PWR_ON, LOW);//关闭主电源24V
  digitalWrite(EC_5V_ON, LOW);//关闭5V供电
  digitalWrite(EC_12V_ON, LOW);//关闭12V供电
  digitalWrite(EC_PWR_LED, LOW);//关闭电源指示灯
  delay(1000);
  int countdownMS = Watchdog.enable(100);
  Serial.println("Enabled the watchdog with 100ms");
}

void loop() {
  // put your main code here, to run repeatedly:
  powerKeyBasicButton.refreshStatus();
  estopKeyBasicButton.refreshStatus();
  if (powerKeyBasicButton.getButtonState() == true) {
    digitalWrite(EC_PWR_ON, HIGH);//打开主电源24V
    digitalWrite(EC_5V_ON, HIGH);//打开5V供电
    digitalWrite(EC_12V_ON, HIGH);//打开12V供电
    digitalWrite(EC_PWR_LED, HIGH);
    FLAG_PWRON = 1;
    Serial.println("POWER KEY ON");
  }
  else {
    digitalWrite(EC_PWR_ON, LOW);
    digitalWrite(EC_5V_ON, LOW);
    digitalWrite(EC_12V_ON, LOW);
    digitalWrite(EC_PWR_LED, LOW);
    FLAG_PWRON = 0;
    Serial.println("POWER KEY OFF");
  }
  if (FLAG_PWRON) {
    if (estopKeyBasicButton.getButtonState() == true) {
      digitalWrite(MCU_ESTOP, LOW);
    }
    else {
      digitalWrite(MCU_ESTOP, HIGH);
    }
  }
  else {
    digitalWrite(MCU_ESTOP, HIGH);
  }
  delay(10);
  Watchdog.reset();
}
