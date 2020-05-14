#ifndef __APPSPLCADR_H__
#define __APPSPLCADR_H__
/*****************************************************************************/
#define EM_LASER_SCHEME_NAME									(EM_START + 0)//��������
#define EM_LASER_SELECT												(EM_START + 13)//ͨ��ѡ��
#define EM_LASER_PULSE_MODE										(EM_START + 14)//����ģʽ
#define EM_LASER_POWER_CH0										(EM_START + 15)//ͨ��0����
#define EM_LASER_POWER_CH1										(EM_START + 16)//ͨ��1����
#define EM_LASER_POWER_CH2										(EM_START + 17)//ͨ��2����
#define EM_LASER_POWER_CH3										(EM_START + 18)//ͨ��3����
#define EM_LASER_SP_POSWIDTH									(EM_START + 19)//������������
#define EM_LASER_MP_POSWIDTH									(EM_START + 20)//������������
#define EM_LASER_MP_NEGWIDTH									(EM_START + 21)//�����帺����
#define EM_LASER_GP_POSWIDTH									(EM_START + 22)//Group����������
#define EM_LASER_GP_NEGWIDTH									(EM_START + 23)//Group���帺����
#define EM_LASER_GP_TIMES											(EM_START + 24)//Group������
#define EM_LASER_GP_GROUP_OFF									(EM_START + 25)//Group������
#define EM_LASER_SIGNAL_ENERGY_INTERVAL				(EM_START + 26)//SIGNAL�������
#define EM_LASER_DERMA_POSWIDTH								(EM_START + 27)//DERMA������
#define EM_LASER_DERMA_NEGWIDTH								(EM_START + 28)//DERMA������
#define EM_LASER_DERMA_SPOT_SIZE							(EM_START + 29)//DERMA���ֱ��
#define EM_LASER_AVERAGE_POWER								(EM_START + 30//����ģʽƽ������
#define EM_LASER_FREQUENCY										(EM_START + 31)//��ǰģʽƵ��
#define EM_LASER_DUTY_CYCLE										(EM_START + 32)//��ǰģʽռ�ձ�
/*****************************************************************************/
#define EM_DIODE_TEMP0												(EM_START + 40)//�������¶�0
#define EM_DIODE_TEMP1												(EM_START + 41)//�������¶�1
#define EM_DRIVE_TEMP													(EM_START + 42)//�������¶�
#define EM_ENVI_TEMP													(EM_START + 43)//�����¶�
#define EM_DIODE_HIGH_TEMP										(EM_START + 44)//�����ܹ�����ֵ
#define EM_DRIVE_HIGH_TEMP										(EM_START + 45)//������������ֵ
#define EM_ENVI_HIGH_TEMP											(EM_START + 46)//����������ֵ
#define EM_COOL_SET_TEMP											(EM_START + 47)//�趨��ȴ�¶�
#define EM_COOL_DIFF_TEMP											(EM_START + 48)//�趨��ȴ�ز����
/*****************************************************************************/				
#define EM_TOTAL_POWER												(EM_START + 50)//�����ܹ���
#define EM_HMI_OPERA_STEP											(EM_START +	51)//��������								
#define EM_ERROR_CODE													(EM_START + 52)//������					
#define EM_SCHEME_NUM_TMP											(EM_START + 53)//��ȷ�Ϸ������			
#define EM_DK25L_VER													(EM_START + 54)//DK25Lģ��汾
/*****************************************************************************/
#define EM_DC_PAGE														(EM_START + 64)//HMIҳ���� 			
#define EM_DC_PASSCODE_INDEX									(EM_START + 65)//��������λ����		
#define EM_DC_NEW_PASSCODE0										(EM_START + 66)//����������0			
#define EM_DC_NEW_PASSCODE1										(EM_START + 67)//����������1			
#define EM_DC_NEW_PASSCODE2										(EM_START + 68)//����������0			
#define EM_DC_NEW_PASSCODE3										(EM_START + 69)//����������1			
#define EM_DC_DEFAULT_PASSCODE0								(EM_START + 70)//Ĭ������0				
#define EM_DC_DEFAULT_PASSCODE1								(EM_START + 71)//Ĭ������1				
#define EM_DC_DEFAULT_PASSCODE2								(EM_START + 72)//Ĭ������1	
#define EM_DC_DEFAULT_PASSCODE3								(EM_START + 73)//Ĭ������1				
#define EM_DC_DISPLAY_RELEASE_TIME						(EM_START + 74)//��ʾ����ʱ��			
#define EM_DC_DISPLAY_RELEASE_ENERGY					(EM_START + 75)//��ʾ��������
/*****************************************************************************/
#define FD_LASER_SCHEME_NAME									(FD_START +  0)//��������
#define FD_LASER_SELECT												(FD_START +  13)//ͨ��ѡ��
#define FD_LASER_PULSE_MODE										(FD_START +  14)//����ģʽ
#define FD_LASER_POWER_CH0										(FD_START +  15)//ͨ��0����
#define FD_LASER_POWER_CH1										(FD_START +  16)//ͨ��1����
#define FD_LASER_POWER_CH2										(FD_START +  17)//ͨ��2����
#define FD_LASER_POWER_CH3										(FD_START +  18)//ͨ��3����
#define FD_LASER_SP_POSWIDTH									(FD_START +  19)//������������
#define FD_LASER_MP_POSWIDTH									(FD_START +  20)//������������
#define FD_LASER_MP_NEGWIDTH									(FD_START +  21)//�����帺����
#define FD_LASER_GP_POSWIDTH									(FD_START +  22)//Group����������
#define FD_LASER_GP_NEGWIDTH									(FD_START +  23)//Group���帺����
#define FD_LASER_GP_TIMES										(FD_START +  24)//Group������
#define FD_LASER_GP_GROUP_OFF									(FD_START +  25)//Group������
#define FD_LASER_SIGNAL_ENERGY_INTERVAL							(FD_START +  26)//SIGNAL�������
#define FD_LASER_DERMA_POSWIDTH									(FD_START +  27)//DERMA������
#define FD_LASER_DERMA_NEGWIDTH									(FD_START +  28)//DERMA������
#define FD_LASER_DERMA_SPOT_SIZE								(FD_START +  29)//DERMA���ֱ��

#define FD_SCHEME_START_0										(FD_START +   0)//����0�洢����ʼ
#define FD_SCHEME_END_0											(FD_START +  29)//����0�洢������		

#define FD_SCHEME_START_1										(FD_START +  30)//����1�洢����ʼ		
#define FD_SCHEME_END_1											(FD_START +  59)//����1�洢������

#define FD_SCHEME_START_2										(FD_START +  60)//����2�洢����ʼ
#define FD_SCHEME_END_2											(FD_START +  89)//����2�洢������

#define FD_SCHEME_START_3										(FD_START +  90)//����3�洢����ʼ
#define FD_SCHEME_END_3											(FD_START + 119)//����3�洢������

#define FD_SCHEME_START_4										(FD_START + 120)//����4�洢����ʼ
#define FD_SCHEME_END_4											(FD_START + 149)//����4�洢������

#define FD_SCHEME_START_5										(FD_START + 150)//����5�洢����ʼ
#define FD_SCHEME_END_5											(FD_START + 179)//����5�洢������

#define FD_SCHEME_START_6										(FD_START + 180)//����6�洢����ʼ
#define FD_SCHEME_END_6											(FD_START + 209)//����6�洢������

#define FD_SCHEME_START_7										(FD_START + 210)//����7�洢����ʼ
#define FD_SCHEME_END_7											(FD_START + 239)//����7�洢������

#define FD_SCHEME_START_8										(FD_START + 240)//����8�洢����ʼ
#define FD_SCHEME_END_8											(FD_START + 269)//����8�洢������

#define FD_SCHEME_START_9										(FD_START + 270)//����9�洢����ʼ
#define FD_SCHEME_END_9											(FD_START + 299)//����9�洢������

#define FD_SCHEME_START_10										(FD_START + 300)//����10�洢����ʼ
#define FD_SCHEME_END_10										(FD_START + 329)//����10�洢������

#define FD_SCHEME_START_11										(FD_START + 330)//����11�洢����ʼ
#define FD_SCHEME_END_11										(FD_START + 359)//����11�洢������

#define FD_SCHEME_START_12										(FD_START + 360)//����12�洢����ʼ
#define FD_SCHEME_END_12										(FD_START + 389)//����12�洢������

#define FD_SCHEME_START_13										(FD_START + 390)//����13�洢����ʼ
#define FD_SCHEME_END_13										(FD_START + 419)//����13�洢������

#define FD_SCHEME_START_14										(FD_START + 420)//����14�洢����ʼ
#define FD_SCHEME_END_14										(FD_START + 449)//����14�洢������

#define FD_SCHEME_START_15										(FD_START + 450)//����15�洢����ʼ
#define FD_SCHEME_END_15										(FD_START + 479)//����15�洢������
/*****************************************************************************/
#define FD_SCHEME_START_16										(FD_START + 480)//����16�洢����ʼ
#define FD_SCHEME_END_16										(FD_START + 509)//����16�洢������

#define FD_SCHEME_START_17										(FD_START + 510)//����17�洢����ʼ
#define FD_SCHEME_END_17										(FD_START + 539)//����17�洢������

#define FD_SCHEME_START_18										(FD_START + 540)//����18�洢����ʼ
#define FD_SCHEME_END_18										(FD_START + 569)//����18�洢������

#define FD_SCHEME_START_19										(FD_START + 570)//����19�洢����ʼ
#define FD_SCHEME_END_19										(FD_START + 599)//����19�洢������

#define FD_SCHEME_START_20										(FD_START + 600)//����20�洢����ʼ
#define FD_SCHEME_END_20										(FD_START + 629)//����20�洢������

#define FD_SCHEME_START_21										(FD_START + 630)//����21�洢����ʼ
#define FD_SCHEME_END_21										(FD_START + 659)//����21�洢������

#define FD_SCHEME_START_22										(FD_START + 660)//����22�洢����ʼ
#define FD_SCHEME_END_22										(FD_START + 689)//����22�洢������

#define FD_SCHEME_START_23										(FD_START + 690)//����23�洢����ʼ
#define FD_SCHEME_END_23										(FD_START + 719)//����23�洢������

#define FD_SCHEME_START_24										(FD_START + 720)//����24�洢����ʼ
#define FD_SCHEME_END_24										(FD_START + 749)//����24�洢������

#define FD_SCHEME_START_25										(FD_START + 750)//����25�洢����ʼ
#define FD_SCHEME_END_25										(FD_START + 779)//����25�洢������

#define FD_SCHEME_START_26										(FD_START + 780)//����26�洢����ʼ
#define FD_SCHEME_END_26										(FD_START + 809)//����26�洢������

#define FD_SCHEME_START_27										(FD_START + 810)//����27�洢����ʼ
#define FD_SCHEME_END_27										(FD_START + 839)//����27�洢������

#define FD_SCHEME_START_28										(FD_START + 840)//����28�洢����ʼ
#define FD_SCHEME_END_28										(FD_START + 869)//����28�洢������

#define FD_SCHEME_START_29										(FD_START + 870)//����29�洢����ʼ
#define FD_SCHEME_END_29										(FD_START + 899)//����29�洢������

#define FD_SCHEME_START_30										(FD_START + 900)//����30�洢����ʼ
#define FD_SCHEME_END_30										(FD_START + 929)//����30�洢������

#define FD_SCHEME_START_31										(FD_START + 930)//����31�洢����ʼ
#define FD_SCHEME_END_31										(FD_START + 959)//����31�洢������
/*****************************************************************************/
#define TMP_NAME_0												(TMP_START + 0)//��ʱ���ƴ�����
#define TMP_NAME_1												(TMP_START + 15)//��ʱ���ƴ�����
#define TMP_NAME_2												(TMP_START + 30)//��ʱ���ƴ�����
#define TMP_NAME_3												(TMP_START + 45)//��ʱ���ƴ�����
#define TMP_NAME_4												(TMP_START + 60)//��ʱ���ƴ�����
#define TMP_NAME_5												(TMP_START + 75)//��ʱ���ƴ�����
#define TMP_NAME_6												(TMP_START + 90)//��ʱ���ƴ�����
#define TMP_NAME_7												(TMP_START + 105)//��ʱ���ƴ�����
#define TMP_NAME_8												(TMP_START + 120)//��ʱ���ƴ�����
#define TMP_NAME_9												(TMP_START + 135)//��ʱ���ƴ�����
#define TMP_NAME_10												(TMP_START + 150)//��ʱ���ƴ�����
#define TMP_NAME_11												(TMP_START + 165)//��ʱ���ƴ�����
#define TMP_NAME_12												(TMP_START + 180)//��ʱ���ƴ�����
#define TMP_NAME_13												(TMP_START + 195)//��ʱ���ƴ�����
#define TMP_NAME_14												(TMP_START + 210)//��ʱ���ƴ�����
#define TMP_NAME_15												(TMP_START + 225)//��ʱ���ƴ�����

#define TMP_NAME_16												(TMP_START + 240)//��ʱ���ƴ�����
#define TMP_NAME_17												(TMP_START + 255)//��ʱ���ƴ�����
#define TMP_NAME_18												(TMP_START + 270)//��ʱ���ƴ�����
#define TMP_NAME_19												(TMP_START + 285)//��ʱ���ƴ�����
#define TMP_NAME_20												(TMP_START + 300)//��ʱ���ƴ�����
#define TMP_NAME_21												(TMP_START + 315)//��ʱ���ƴ�����
#define TMP_NAME_22												(TMP_START + 330)//��ʱ���ƴ�����
#define TMP_NAME_23												(TMP_START + 345)//��ʱ���ƴ�����
#define TMP_NAME_24												(TMP_START + 360)//��ʱ���ƴ�����
#define TMP_NAME_25												(TMP_START + 375)//��ʱ���ƴ�����
#define TMP_NAME_26												(TMP_START + 390)//��ʱ���ƴ�����
#define TMP_NAME_27												(TMP_START + 405)//��ʱ���ƴ�����
#define TMP_NAME_28												(TMP_START + 420)//��ʱ���ƴ�����
#define TMP_NAME_29												(TMP_START + 435)//��ʱ���ƴ�����
#define TMP_NAME_30												(TMP_START + 450)//��ʱ���ƴ�����
#define TMP_NAME_31												(TMP_START + 465)//��ʱ���ƴ�����
/*****************************************************************************/
#define DM_SCHEME_NUM											(DM_START + 0)//ѡ��ķ������ ��8λ������ ��8λ����ʹ��
#define DM_BEEM_VOLUME											(DM_START + 1)//����������
#define DM_AIM_BRG												(DM_START + 2)//ָʾ��������
#define DM_LCD_BRG												(DM_START + 3)//��Ļ����
#define DM_DC_OLD_PASSCODE0										(DM_START + 4)//��������0-1
#define DM_DC_OLD_PASSCODE1										(DM_START + 5)//��������2-3
#define DM_DC_OLD_PASSCODE2										(DM_START + 6)//��������0-1
#define DM_DC_OLD_PASSCODE3										(DM_START + 7)//��������2-3
/*****************************************************************************/

#define X_FOOTSWITCH_NC											(X_START * 16 + 1)//XIN0 ��̤����
#define X_ESTOP													(X_START * 16 + 0)//XIN1 ����ֹͣ����
#define X_FOOTSWITCH_NO											(X_START * 16 + 2)//XIN2 ��̤����
#define X_INTERLOCK												(X_START * 16 + 3)//XIN0 ��ȫ����

#define X_FIBER_PROBE											(X_START * 16 + 7)//XIN6 ����̽��0
/*****************************************************************************/
#define Y_LED_POWERON											(Y_START * 16 + 0)//YOUT0 ��Դ��
#define Y_LED_EMIT												(Y_START * 16 + 1)//YOUT1 ����ָʾ��
#define Y_LED_ALARM												(Y_START * 16 + 2)//YOUT2 ����ָʾ��
#define Y_OUT3													(Y_START * 16 + 3)//YOUT3 ����
#define Y_OUT4													(Y_START * 16 + 4)//YOUT4 ����
#define Y_OUT5													(Y_START * 16 + 5)//YOUT5 ����
#define Y_OUT6													(Y_START * 16 + 6)//YOUT6 ����
#define Y_OUT7													(Y_START * 16 + 7)//YOUT7 ����
#define Y_FAN0													(Y_START * 16 + 8)//YOUT8 ���ȿ���0
#define Y_FAN1													(Y_START * 16 + 9)//YOUT9 ���ȿ���1
#define Y_TEC0													(Y_START * 16 + 10)//YOUT10 ���俪��0
#define Y_TEC1													(Y_START * 16 + 11)//YOUT11 ���俪��1
/*****************************************************************************/
#define R_FOOTSWITCH_NC											(R_START * 16 + 0)//
#define R_ESTOP													(R_START * 16 + 1)//
#define R_INTERLOCK												(R_START * 16 + 2)//
#define R_FIBER_PROBE											(R_START * 16 + 3)//
#define R_RFID_PASS												(R_START * 16 + 4)
#define R_DIODE_TEMP_HIGH										(R_START * 16 + 5)//ͨ��0�����ܸ��±�־
#define R_DIODE_TEMP_LOW										(R_START * 16 + 6)//ͨ��0�����ܸ��±�־
#define R_DRIVE_TEMP_HIGH										(R_START * 16 + 7)//���������±�־
#define R_DRIVE_TEMP_LOW										(R_START * 16 + 8)//ͨ��0�����ܸ��±�־
#define R_ENVI_TEMP_HIGH										(R_START * 16 + 9)//�����¶ȱ��
#define R_ENVI_TEMP_LOW											(R_START * 16 + 10)//ͨ��0�����ܸ��±�־
#define R_FAULT													(R_START * 16 + 11)//���ϱ�־
#define R_FAN_ENABLE											(R_START * 16 + 12)//����ʹ��
#define R_DISABLE_RFID											(R_START * 16 + 13)//����NFC���
#define R_DISABLE_FIBER_PROBE									(R_START * 16 + 14)//���ι���̽��
#define R_DISABLE_FAN_SPEED										(R_START * 16 + 15)//���η��ȿ���
#define R_CLEAR_EPROM											(R_START * 16 + 16)//��ȫ���EPROM
#define R_ENGINEER_MODE											(R_START * 16 + 17)//����ʦģʽ
//HMI���״̬
#define R_DCHMI_RESET_REQ										(R_START * 16 + 20)//HMI��λ����
#define R_DCHMI_RESET_DOING										(R_START * 16 + 21)//HMI��λ��
#define R_DCHMI_RESET_DONE										(R_START * 16 + 22)//HMI��λ���	
#define R_DCHMI_UPDATEUI_REQ									(R_START * 16 + 23)//HMI���ݸ�������
#define R_DCHMI_UPDATEUI_DOING									(R_START * 16 + 24)//HMI���ݸ�����
#define R_DCHMI_UPDATEUI_DONE									(R_START * 16 + 25)//HMI���ݸ����������
#define R_DCHMI_RESTORE_REQ										(R_START * 16 + 26)//HMI��FLASH�лָ���������
#define R_DCHMI_RESTORE_DOING									(R_START * 16 + 27)//HMI��FLASH�лָ���
#define R_DCHMI_RESTORE_DONE									(R_START * 16 + 28)//HMI��FLASH�лָ��������	
#define R_DCHMI_DISPLAY_WARN									(R_START * 16 + 30)//HMI��ʾ������Ϣ
#define R_DCHMI_KEY_STANDBY_ENABLE								(R_START * 16 + 40)//STANDBY ʹ��
/*****************************************************************************/
#define R_STANDBY_KEY_POSWIDTH_ADD_DOWN							(R_START * 16 + 80)
#define R_STANDBY_KEY_POSWIDTH_DEC_DOWN							(R_START * 16 + 81)
#define R_STANDBY_KEY_NEGWIDTH_ADD_DOWN							(R_START * 16 + 82)
#define R_STANDBY_KEY_NEGWIDTH_DEC_DOWN							(R_START * 16 + 83)
#define R_STANDBY_KEY_TIMES_ADD_DOWN							(R_START * 16 + 84)
#define R_STANDBY_KEY_TIMES_DEC_DOWN							(R_START * 16 + 85)
#define R_STANDBY_KEY_GROUP_OFF_ADD_DOWN						(R_START * 16 + 86)
#define R_STANDBY_KEY_GROUP_OFF_DEC_DOWN						(R_START * 16 + 87)
#define R_STANDBY_KEY_ENERGY_INTERVAL_ADD_DOWN					(R_START * 16 + 88)
#define R_STANDBY_KEY_ENERGY_INTERVAL_DEC_DOWN					(R_START * 16 + 89)
#define R_STANDBY_KEY_STNADBY_DOWN								(R_START * 16 + 90)
#define R_STANDBY_KEY_STNADBY_UP								(R_START * 16 + 91)
#define R_STANDBY_KEY_ENTER_OPTION_DOWN							(R_START * 16 + 92)
#define R_STANDBY_KEY_ENTER_SCHEME_DOWN							(R_START * 16 + 93)
#define R_STANDBY_KEY_SCHEME_SAVE_DOWN							(R_START * 16 + 94)
/*****************************************************************************/
#define R_OPTION_KEY_ENTER_CORRECTION_DOWN						(R_START * 16 + 100)
#define R_OPTION_KEY_ENTER_INFORMATION_DOWN						(R_START * 16 + 101)
#define R_OPTION_KEY_ENTER_OK_DOWN								(R_START * 16 + 102)
#define R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN						(R_START * 16 + 103)
/*****************************************************************************/
#define R_INFORMATION_KEY_OK_DOWN								(R_START * 16 + 110)
#define R_INFORMATION_KEY_OK_UP									(R_START * 16 + 111)
/*****************************************************************************/
#define R_SCHEME_KEY_RENAME_DOWN								(R_START * 16 + 120)
#define R_SCHEME_KEY_OK_DOWN									(R_START * 16 + 121)
#define R_SCHEME_KEY_CANCEL_DOWN								(R_START * 16 + 122)
#define R_SCHEME_KEY_SCHEME_SELECT_0_DOWN						(R_START * 16 + 123)		
#define R_SCHEME_KEY_SCHEME_SELECT_1_DOWN						(R_START * 16 + 124)
#define R_SCHEME_KEY_SCHEME_SELECT_2_DOWN						(R_START * 16 + 125)
#define R_SCHEME_KEY_SCHEME_SELECT_3_DOWN						(R_START * 16 + 126)
#define R_SCHEME_KEY_SCHEME_SELECT_4_DOWN						(R_START * 16 + 127)
#define R_SCHEME_KEY_SCHEME_SELECT_5_DOWN						(R_START * 16 + 128)
#define R_SCHEME_KEY_SCHEME_SELECT_6_DOWN						(R_START * 16 + 129)
#define R_SCHEME_KEY_SCHEME_SELECT_7_DOWN						(R_START * 16 + 130)
#define R_SCHEME_KEY_SCHEME_SELECT_8_DOWN						(R_START * 16 + 131)
#define R_SCHEME_KEY_SCHEME_SELECT_9_DOWN						(R_START * 16 + 132)
#define R_SCHEME_KEY_SCHEME_SELECT_10_DOWN						(R_START * 16 + 133)
#define R_SCHEME_KEY_SCHEME_SELECT_11_DOWN						(R_START * 16 + 134)
#define R_SCHEME_KEY_SCHEME_SELECT_12_DOWN						(R_START * 16 + 135)
#define R_SCHEME_KEY_SCHEME_SELECT_13_DOWN						(R_START * 16 + 136)
#define R_SCHEME_KEY_SCHEME_SELECT_14_DOWN						(R_START * 16 + 137)
#define R_SCHEME_KEY_SCHEME_SELECT_15_DOWN						(R_START * 16 + 138)
#define R_SCHEME_KEY_NEXT_SCHEME								(R_START * 16 + 139)
#define R_SCHEME_KEY_LAST_SCHEME								(R_START * 16 + 140)
/*****************************************************************************/
#define R_DIAGNOSIS_OK_DOWN										(R_START * 16 + 160)
#define R_DIAGNOSIS_OK_UP										(R_START * 16 + 161)
/*****************************************************************************/
#define R_RENAME_KEY_ENTER_DOWN									(R_START * 16 + 170)
#define R_RENAME_KEY_EXIT_DOWN									(R_START * 16 + 171)
#define R_RENAME_TEXTDISPLAY_READ_DONE							(R_START * 16 + 172)
/*****************************************************************************/
#define MR_FOOSWITCH_HAND_SWITCH								(MR_START * 16 + 10)//��̤HandSwitch �������
#define MR_BEEM_TONE											(MR_START * 16 + 11)//������ģʽ
/*****************************************************************************/
#define T100MS_HMI_POWERUP_DELAY								0//HMI������λ��ʱ
#define T100MS_ENTER_PASSCODE_DELAY								1
#define T100MS_READY_BEEM_DELAY									2//����READY״̬����������ӳ�
#define T100MS_PULSE_BEEM_DELAY									3//����ģʽ�������ӳ�
/*****************************************************************************/
#define T10MS_POSWIDTH_ADD_KEYDOWN_DELAY						3
#define T10MS_POSWIDTH_DEC_KEYDOWN_DELAY						4
#define T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY						5
#define T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY						6
#define T10MS_TIMES_ADD_KEYDOWN_DELAY							7
#define T10MS_TIMES_DEC_KEYDOWN_DELAY							8
#define T10MS_GROUP_OFF_ADD_KEYDOWN_DELAY						9
#define T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY						10
#endif