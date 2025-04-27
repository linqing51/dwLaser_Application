#ifndef __PRESCHEME_H__
#define __PRESCHEME_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
typedef struct{
	char *name;//��������
	int16_t channel;//����ͨ��ѡ��
	int16_t pulse_mode;//����ģʽ
	int16_t power_ch0;//���� 1470
	int16_t power_ch1;//���� 980
	int16_t power_red;//���� 635
	int16_t poswidth;
	int16_t negwidth;
}myScheme_t;
/*****************************************************************************/
extern myScheme_t sPhlebology[32];//0
extern myScheme_t sProctology[32];//1
extern myScheme_t sGynecology[32];//2
extern myScheme_t sENT[32];//3
extern myScheme_t sNeurosurgery[32];//4
extern myScheme_t sDermatology[32];//5
extern myScheme_t sLiposuction[32];//6
extern myScheme_t sDentistry[32];//7
extern myScheme_t sTherapy[32];//8
/*****************************************************************************/
void schemeInit(uint8_t reDef);//���Ʒ�����ʼ��
void goNextScheme(void);//�л���һ������
void goLastScheme(void);//�л���һ������
#endif


