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
	if screen == 4 then
		if control == 12 and value == 1 then
		--CW ��������
			set_visiable(4,44,0)
			set_visiable(4,19,0)
	 		set_visiable(4,20,0)
			set_visiable(4,21,0)
			set_visiable(4,22,0)
			set_visiable(4,36,0)
			set_visiable(4,37,0)
			set_value(4,13,0)
		end
		if control == 13 and value== 1 then
		--MP ��������
			set_visiable(4,44,1)
			set_visiable(4,19,1)
	 		set_visiable(4,20,1)
			set_visiable(4,21,1)
			set_visiable(4,22,1)
			set_visiable(4,36,1)
			set_visiable(4,37,1)
			set_enable(4,19,1)
 			set_enable(4,20,1)
			set_enable(4,21,1)
			set_enable(4,22,1)
			set_enable(4,36,1)
			set_enable(4,37,1)
			set_value(4,12,0)
		end
		if control == 25 and value == 1 then
			--ѡ�� 635nm
			set_value(4,23,0)
		end
		if control == 23 and value == 1 then
			--ѡ�� 1470nm
			set_value(4,25,0)
		end
	end

	if screen == 8 and value == 1 then --����ѡ��
		if control == 4 and value == 1 then                   
		    --set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end
	    if control == 5 and value == 1 then                   
		    set_value(8,4,0)
			--set_value(6,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end
	    if control == 6 and value == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    --set_value(6,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end
	    if control == 7 and value == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			--set_value(6,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end
	    if control == 8 and value == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			--set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end
	    if control == 9 and value == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			--set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(6,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end
	    if control == 10 and value == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			--set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end
	    if control == 11 and value == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			--set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end
	    if control == 12 and value == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			--set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end
        if control == 13 and value  == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			--set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end

        if control == 14 and value  == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			--set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end

        if control == 15 and value  == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			--set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end

        if control == 16 and value  == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			--set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end

        if control == 17 and value  == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(6,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			--set_value(8,17,0)
			set_value(8,18,0)
			set_value(8,19,0)	
		end

        if control == 18 and value  == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			--set_value(8,18,0)
			set_value(8,19,0)	
		end

        if control == 19 and value  == 1 then                   
		    set_value(8,4,0)
			set_value(8,5,0)
		    set_value(8,6,0)
 			set_value(8,7,0)
			set_value(8,8,0)
			set_value(8,9,0)
			set_value(8,10,0)
			set_value(8,11,0)
			set_value(8,12,0)
			set_value(8,13,0)
			set_value(8,14,0)
 			set_value(8,15,0)
			set_value(8,16,0)
			set_value(8,17,0)
			set_value(8,18,0)
			--set_value(8,19,0)	
		end
	end
	

end
