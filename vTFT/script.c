/*
������on_init
���ܣ�ϵͳִ�г�ʼ��
*/
void on_init()
{
}

/*
������on_systick
���ܣ�����ִ������(1��/��)
*/
void on_systick()
{
}

/*
������on_timer
���ܣ���ʱ����ʱ֪ͨ
������timer_id����ʱ��ID
��ز�����
������ʱ����start_timer(timer_id,timeout,countdown,repeat)
            timer_id-��ʱ��ID��0~9��
			timeout-��ʱʱ�䣬���뵥λ
			countdown-0˳��ʱ��1����ʱ������sys.timer������ݼ�
			repeat-�ظ�������0��ʾ����
ֹͣ��ʱ����stop_timer(timer_id)
��ʱ����ֵ��sys.timer0~sys.timer9�����뵥λ
*/
void on_timer(int timer_id)
{	
}

/*
������on_variant_upate
���ܣ�����ͨ�ŵ��±�������ʱ��ִ�д˺���
*/
void on_variant_upate()
{
}

/*
������on_control_notify
���ܣ��ؼ�ֵ����֪ͨ
������screen_id������ID
������control_id���ؼ�ID
������value����ֵ
*/
void on_control_notify(int screen_id,int control_id,int value){
	//�������� ���� 1
	if(screen_id == 1 && control_id == 1){//KEY1
		if(value == 1){//����
			R_DC_PASSCODE_KEY1 = 1;		
		}
	}
	//�������� ���� 2
 	if(screen_id == 1 && control_id == 2){//KEY2
		if(value == 1){//����
			R_DC_PASSCODE_KEY2 = 1;	
		}
	}
	//�������� ���� 3
	if(screen_id == 1 && control_id == 3){//KEY3
		if(value == 1){//����
			R_DC_PASSCODE_KEY3 = 1;		
		}
	}	
 	//�������� ���� 4
	if(screen_id == 1 && control_id == 4){
		if(value == 1){//����
			R_DC_PASSCODE_KEY4 = 1;
		}
	}	
  	//�������� ���� 5
	if(screen_id == 1 && control_id == 5){
		if(value == 1){//����
			R_DC_PASSCODE_KEY5 = 1;		
		}
	}	
	//�������� ���� 6
	if(screen_id == 1 && control_id == 6){
		if(value == 1){//����
			R_DC_PASSCODE_KEY6 = 1;		
		}
	}
	//�������� ���� 7
	if(screen_id == 1 && control_id == 7){
		if(value == 1){//����
			R_DC_PASSCODE_KEY7 = 1;		
		}
	}
	//�������� ���� 8
	if(screen_id == 1 && control_id == 8){
		if(value == 1){//����
			R_DC_PASSCODE_KEY8 = 1;		
		}
	}	
	//�������� ���� 9
	if(screen_id == 1 && control_id == 9){
		if(value == 1){//����
			R_DC_PASSCODE_KEY9 = 1;		
		}
	}
 	//�������� ���� 0
	if(screen_id == 1 && control_id == 10){
		if(value == 1){//����
			R_DC_PASSCODE_KEY0 = 1;
		}
	}	
	//�������� ����Cancle
	if(screen_id == 1 && control_id == 11){
		if(value == 1){//����
			R_DC_PASSCODE_CANCEL_REQ = 1;		
		}
	}
	//�������� ����Backspace
	if(screen_id == 1 && control_id == 12){
		if(value == 1){//����
			R_DC_PASSCODE_BACKSPACE_REQ = 1;
		}
	}
	//�������� ����Change Passcode
	if(screen_id == 1 && control_id == 13){
		if(value == 1){//����
			R_DC_PASSCODE_CHANGE_REQ = 1;	
		}
	}
	//�������� ����Enter
	if(screen_id == 1 && control_id == 14){
		if(value == 1){//����
			R_DC_PASSCODE_ENTER_REQ = 1;				
		}
	}
	//�����޸� ����1
	if(screen_id == 2 && control_id == 1){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY1 = 1;		
		}
	}
	//�����޸� ����2
	if(screen_id == 2 && control_id == 2){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY2 = 1;
		}
	}
	//�����޸� ����3
	if(screen_id == 2 && control_id == 3){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY3 = 1;
		}
	}
	//�����޸� ����4
	if(screen_id == 2 && control_id == 4){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY4 = 1;
		}
	}
	//�����޸� ����5
	if(screen_id == 2 && control_id == 5){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY5 = 1;
		}
	}
	//�����޸� ����6
	if(screen_id == 2 && control_id == 6){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY6 = 1;	
		}
	}
	//�����޸� ����7
	if(screen_id == 2 && control_id == 7){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY7 = 1;
		}
	}
	//�����޸� ����8
	if(screen_id == 2 && control_id == 8){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY8 = 1;
		}
	}
	//�����޸� ����9
	if(screen_id == 2 && control_id == 9){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY9 = 1;
		}
	}
	//�����޸� ����0
 	if(screen_id == 2 && control_id == 10){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_KEY0 = 1;
		}
	}	
	//�����޸� ����Cancel
	if(screen_id == 2 && control_id == 11){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_CANCEL_REQ = 1;
		}
	}
	//�����޸� ����Backspace
 	if(screen_id == 2 && control_id == 12){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_BACKSPACE_REQ = 1;
		}
	}	
	//�����޸� Save
	if(screen_id == 2 && control_id == 13){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_SAVE_REQ = 1;	
		}
	}
	//�����޸� Back
	if(screen_id == 2 && control_id == 14){
		if(value == 1){//����
			R_DC_NEW_PASSCODE_ABANDON_REQ = 1;				
		}
	}
}

/*
������on_screen_change
���ܣ������л�֪ͨ����ǰ����ID�����仯ʱִ�д˺���
������screen_id����ǰ����ID
*/
void on_screen_change(int screen_id)
{
}

