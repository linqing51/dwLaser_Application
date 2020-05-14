-- 原始密码
local oldPassword = "000000"
-- 默认密码
local defaultPassword = "198212"
--新设密码
local newPasswordFirst = "000000"--密码输入第一次
local newPasswordSecond = "000000"--新密码输入第二次
local newPasswordInputTimes--新密码输入次数
--密码输入显示缓冲
local inputPassword = ""


--下面列出了常用的回调函数
--更多功能请阅读<<物联型LUA脚本API.pdf>>

--初始化函数
function on_init()
--从FLASH中读取旧密码
oldPassword = read_flash_string(0)
end

--定时回调函数，系统每隔1秒钟自动调用。
--function on_systick()
--end

--用户通过触摸修改控件后，执行此回调函数。
--点击按钮控件，修改文本控件、修改滑动条都会触发此事件。
function on_control_notify(screen,control,value)
	if screen == 1 then --GDDC_PAGE_PASSCODE_0
		--按键1
		if control == 1 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 1)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--按键2
		if control == 2 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 2)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--按键3
		if control == 3 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 3)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--按键4
		if control == 4 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 4)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--按键5
		if control == 5 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 5)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--按键6
		if control == 6 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 6)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--按键7
		if control == 7 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 7)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--按键8
		if control == 8 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 8)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--按键9
		if control == 9 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 9)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--按键0
		if control == 10 and value == 1 then
			if string.len(inputPassword) < 6 then
				inputPassword = string.format("%s%d", inputPassword, 0)
				set_text(1, 15, inputPassword)
				set_text(1, 16, "")
			end
		end
		--Cancel 取消按键
		if control == 11 and value == 1 then
			inputPassword = ""
			set_text(1, 15, inputPassword)
			set_text(1, 16, "")			
		end		
		--Backspace 按键
		if control == 12 and value == 1 then
			inputPassword = string.sub(inputPassword, 1, -2)
			set_text(1, 15, inputPassword)
			set_text(1, 16, "")			
		end
		--Chane Password 更改密码
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
		--Enter 按键
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
		--1 按键
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
		--2 按键
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
		--3 按键
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
		--4 按键
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
		--5 按键
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
		--6 按键
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
		--7 按键
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
		--8 按键
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
		--9 按键
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
		--0 按键
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
		--Cancel 取消按键
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
		--Save 更改密码
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
					write_flash_string(0, oldPassword) --写入新密码
					flush_flash() --立即写入
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
		--Back 返回按键
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

--当画面切换时，执行此回调函数，screen为目标画面。
--function on_screen_change(screen)
--end