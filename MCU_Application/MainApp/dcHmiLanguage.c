#include "dcHmiLanguage.h"
/*****************************************************************************/
#define ID0_MSG_NO_ERROR						0
#define ID0_MSG_INTERLOCK_UNPLUG = "Door interlock disconnected";//��ȫ����û��
#define ID0_MSG_FOOTSWITCH_UNPLUG = "Footswitch not connected";//��̤û��
#define ID0_MSG_ESTOP_PRESS = "ESTOP Press";
#define ID0_MSG_FIBER_UNPLUG = "No fiber connected ";//����û�����RFID��ʶ��
#define ID0_MSG_OUT_ENERGY = "Energy out of tolerance";//����ƫ�20%��Ԥ�����ܣ������Ժ�ʵ��
#define ID0_MSG_DIODE_HTEMP = "Laser overheating";//�¶ȹ���
#define *LANG_WARN_MSG_DIODE_LTEMP = "Laser temperature too low";//�¶ȹ���
#define *LANG_WARN_MSG_DIODE0_OVERCURRENT = "Laser current exceeds set value";//���������޶�ֵ������������
#define *LANG_WARN_MSG_DIODE1_OVERCURRENT = "Laser current exceeds set value";//���������޶�ֵ������������
#define *LANG_WARN_MSG_NTC_ERROR = "Thermistor Error";//�����������
#define *LANG_WARN_MSG_ENVI_HTEMP = "Envi High Temperature";//�����¶ȹ���
#define *LANG_WARN_MSG_FOOT_DEPRESSED = "Foot/finger switch is depressed";//��̤����ȥû������
#define *LANG_WARN_MSG_LASER_EMIT = "Laser is firing";//�������ڷ���
#define *LANG_WARN_MSG_WAIT_TRIGGER = "Wait Laser Trigger";//�ȴ����ⴥ��
#define *LANG_WARN_MSG_FIBER_MISSMATE = "fiber not mate";




code char *LANG_WARN_MSG_NO_ERROR = "";
code char *LANG_WARN_MSG_INTERLOCK_UNPLUG = "Door interlock disconnected";//��ȫ����û��
code char *LANG_WARN_MSG_FOOTSWITCH_UNPLUG = "Footswitch not connected";//��̤û��
code char *LANG_WARN_MSG_ESTOP_PRESS = "ESTOP Press";
code char *LANG_WARN_MSG_FIBER_UNPLUG = "No fiber connected ";//����û�����RFID��ʶ��
code char *LANG_WARN_MSG_OUT_ENERGY = "Energy out of tolerance";//����ƫ�20%��Ԥ�����ܣ������Ժ�ʵ��
code char *LANG_WARN_MSG_DIODE_HTEMP = "Laser overheating";//�¶ȹ���
code char *LANG_WARN_MSG_DIODE_LTEMP = "Laser temperature too low";//�¶ȹ���
code char *LANG_WARN_MSG_DIODE0_OVERCURRENT = "Laser current exceeds set value";//���������޶�ֵ������������
code char *LANG_WARN_MSG_DIODE1_OVERCURRENT = "Laser current exceeds set value";//���������޶�ֵ������������
code char *LANG_WARN_MSG_NTC_ERROR = "Thermistor Error";//�����������
code char *LANG_WARN_MSG_ENVI_HTEMP = "Envi High Temperature";//�����¶ȹ���
code char *LANG_WARN_MSG_FOOT_DEPRESSED = "Foot/finger switch is depressed";//��̤����ȥû������
code char *LANG_WARN_MSG_LASER_EMIT = "Laser is firing";//�������ڷ���
code char *LANG_WARN_MSG_WAIT_TRIGGER = "Wait Laser Trigger";//�ȴ����ⴥ��
code char *LANG_WARN_MSG_FIBER_MISSMATE = "fiber not mate";

