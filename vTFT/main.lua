-- ԭʼ����
local oldPassword = "000000"
-- Ĭ������
local defaultPassword = "198212"
--��������
local newPasswordFirst = "000000"--���������һ��
local newPasswordSecond = "000000"--����������ڶ���
local newPasswordInputTimes--�������������
--����������ʾ����
local inputPassword = ""


--�����г��˳��õĻص�����
--���๦�����Ķ�<<������LUA�ű�API.pdf>>

--��ʼ������
function on_init()
--��FLASH�ж�ȡ������
oldPassword = read_flash_string(0)
end

--��ʱ�ص�������ϵͳÿ��1�����Զ����á�
--function on_systick()
--end

--�û�ͨ�������޸Ŀؼ���ִ�д˻ص�������
--�����ť�ؼ����޸��ı��ؼ����޸Ļ��������ᴥ�����¼���
function on_control_notify(screen,control,value)
	if screen == 1 then --GDDC_PAGE_PASSCODE_0
		--����1
		if control == 1 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 1)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--����2
		if control == 2 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 2)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--����3
		if control == 3 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 3)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--����4
		if control == 4 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 4)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--����5
		if control == 5 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 5)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--����6
		if control == 6 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 6)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--����7
		if control == 7 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 7)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--����8
		if control == 8 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 8)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--����9
		if control == 9 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 9)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--����0
		if control == 10 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 0)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--Cancel ȡ������
		if control == 11 and value == 1 then
			inputPassword = ""
			set_text(1, 15, inputPassword)
			set_text(1, 16, "")			
		end		
		--Backspace ����
		if control == 12 and value == 1 then
			inputPassword = string.sub(inputPassword, 1, -2)
			set_text(1, 15, inputPassword)
			set_text(1, 16, "")			
		end
		--Chane Password ��������
		if control == 13 and value == 1 then
			if inputPassword == defaultPassword or inputPassword == oldPassword then
				newPasswordInputTimes = 1
				change_screen(2)
				set_text(2, 16, "First:")
			else
				set_text(1, 16, "Invalid Password")			
			end
			inputPassword = ""
			set_text(1, 15, inputPassword)	
		end
		--Enter ����
		if control == 14 and value == 1 then
			if inputPassword == defaultPassword or inputPassword == oldPassword then
				change_screen(3)
			else
				set_text(1, 16, "Invalid Password")
			end
			inputPassword = ""
			set_text(1, 15, inputPassword)
		end
	end
	if screen == 2 then --GDDC_PAGE_NEWPASSCODE
		--1 ����
		if control == 1 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 1)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--2 ����
		if control == 2 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 2)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--3 ����
		if control == 3 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 3)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--4 ����
		if control == 4 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 4)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--5 ����
		if control == 5 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 5)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--6 ����
		if control == 6 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 6)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--7 ����
		if control == 7 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 7)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--8 ����
		if control == 8 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 8)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--9 ����
		if control == 9 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 9)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--0 ����
		if control == 10 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 0)
				set_text(2, 15, inputPassword)
				if newPasswordInputTimes == 1 then
					set_text(2, 16, "First:")
				end
				if newPasswordInputTimes == 2 then
					set_text(2, 16, "Second:")
				end
			end
		end
		--Cancel ȡ������
		if control == 11 and value == 1 then
			inputPassword = ""
			set_text(2, 15, inputPassword)
			if newPasswordInputTimes == 1 then
				set_text(2, 16, "First:")
			end
			if newPasswordInputTimes == 2 then
				set_text(2, 16, "Second:")
			end			
		end		
		--Backspace
		if control == 12 and value == 1 then
			inputPassword = string.sub(inputPassword, 1, -2)
			set_text(2, 15, inputPassword)
			if newPasswordInputTimes == 1 then
				set_text(2, 16, "First:")
			end
			if newPasswordInputTimes == 2 then
				set_text(2, 16, "Second:")
			end
		end
		--Save ��������
		if control == 13 and value == 1 then
			if newPasswordInputTimes == 1 then
				newPasswordFirst = inputPassword
				inputPassword = ""
				set_text(2, 15, "")
				set_text(2, 16, "Second:")
				newPasswordInputTimes = 2
			elseif newPasswordInputTimes == 2 then
				newPasswordSecond = inputPassword
				if(newPasswordFirst == newPasswordSecond) then
					oldPassword = newPasswordSecond
					write_flash_string(0, oldPassword) --д��������
					flush_flash() --����д��
					inputPassword = ""
					set_text(2, 15, "")
					change_screen(1)
				else
					newPasswordFirst = ""
					newPasswordSecond = ""
					newPasswordInputTimes = 1
					inputPassword = ""
					set_text(2, 15, "")
					set_text(2, 16, "Not Match:")
				end
			end
		end
		--Back ���ذ���
		if control == 14 and value == 1 then
			newPasswordFirst = ""
			newPasswordSecond = ""
			newPasswordInputTimes = 1
			inputPassword = ""
			set_text(2, 15, "");
			change_screen(1)
		end
	end
end

--�������л�ʱ��ִ�д˻ص�������screenΪĿ�껭�档
--function on_screen_change(screen)
--end