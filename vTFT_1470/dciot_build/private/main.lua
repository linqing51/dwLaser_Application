--�����г��˳��õĻص�����
--���๦�����Ķ�<<������LUA�ű�API.pdf>>

--��ʼ������
--function on_init()
--end

--��ʱ�ص�������ϵͳÿ��1�����Զ����á�
--function on_systick()
--end

--�û�ͨ�������޸Ŀؼ���ִ�д˻ص�������
--�����ť�ؼ����޸��ı��ؼ����޸Ļ��������ᴥ�����¼���
--function on_control_notify(screen,control,value)
--end

--�������л�ʱ��ִ�д˻ص�������screenΪĿ�껭�档
function on_screen_change(screen)
end

function on_control_notify(screen,control,value)
	--***************************************************************************
	--���ܣ���ť�ؼ������д��ť�ؼ�ֵ
	--���ú�����set_value(screen,control,value) ���ÿؼ���ֵ��Ҳ�������ý����������顢�Ǳ�ȣ�
	--���ú����� get_value(screen,control)	   ��ȡ�ؼ�����ֵ
    --Input value :   screen  ����ID
	--			      control �ؼ�ID
	--			      value   �ؼ�ֵ(0 or 1)
	--***************************************************************************
	if screen == 5 then
		if control == 12 and value == 1 then
		--CW ��������
			set_visiable(5,44,0)
			set_visiable(5,19,0)
	 		set_visiable(5,20,0)
			set_visiable(5,21,0)
			set_visiable(5,22,0)
			set_visiable(5,36,0)
			set_visiable(5,37,0)
			set_value(5,13,0)
		end
		if control == 13 and value== 1 then
		--MP ��������
			set_visiable(5,44,1)
			set_visiable(5,19,1)
	 		set_visiable(5,20,1)
			set_visiable(5,21,1)
			set_visiable(5,22,1)
			set_visiable(5,36,1)
			set_visiable(5,37,1)
			set_enable(5,19,1)
 			set_enable(5,20,1)
			set_enable(5,21,1)
			set_enable(5,22,1)
			set_enable(5,36,1)
			set_enable(5,37,1)
			set_value(5,12,0)
		end
		if control == 25 and value == 1 then
			--ѡ�� 635nm
			set_value(5,23,0)
		end
		if control == 23 and value == 1 then
			--ѡ�� 1470nm
			set_value(5,25,0)
		end
	end

	if screen == 9 and value == 1 then --����ѡ��
		if control == 4 and value == 1 then                   
		    --set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end
	    if control == 5 and value == 1 then                   
		    set_value(9,4,0)
			--set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end
	    if control == 6 and value == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    --set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end
	    if control == 7 and value == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			--set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end
	    if control == 8 and value == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			--set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end
	    if control == 9 and value == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			--set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(6,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end
	    if control == 10 and value == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			--set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end
	    if control == 11 and value == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			--set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end
	    if control == 12 and value == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			--set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end
        if control == 13 and value  == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			--set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end

        if control == 14 and value  == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			--set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end

        if control == 15 and value  == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			--set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end

        if control == 16 and value  == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			--set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end

        if control == 17 and value  == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(6,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			--set_value(9,17,0)
			set_value(9,18,0)
			set_value(9,19,0)	
		end

        if control == 18 and value  == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			--set_value(9,18,0)
			set_value(9,19,0)	
		end

        if control == 19 and value  == 1 then                   
		    set_value(9,4,0)
			set_value(9,5,0)
		    set_value(9,6,0)
 			set_value(9,7,0)
			set_value(9,8,0)
			set_value(9,9,0)
			set_value(9,10,0)
			set_value(9,11,0)
			set_value(9,12,0)
			set_value(9,13,0)
			set_value(9,14,0)
 			set_value(9,15,0)
			set_value(9,16,0)
			set_value(9,17,0)
			set_value(9,18,0)
			--set_value(9,19,0)	
		end
	end
	

end
