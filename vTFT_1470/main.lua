--下面列出了常用的回调函数
--更多功能请阅读<<物联型LUA脚本API.pdf>>

--初始化函数
--function on_init()
--end

--定时回调函数，系统每隔1秒钟自动调用。
--function on_systick()
--end

--用户通过触摸修改控件后，执行此回调函数。
--点击按钮控件，修改文本控件、修改滑动条都会触发此事件。
--function on_control_notify(screen,control,value)
--end

--当画面切换时，执行此回调函数，screen为目标画面。
function on_screen_change(screen)
end

function on_control_notify(screen,control,value)
	--***************************************************************************
	--功能：按钮控件画面读写按钮控件值
	--调用函数：set_value(screen,control,value) 设置控件数值（也可以设置进度条、滑块、仪表等）
	--调用函数： get_value(screen,control)	   获取控件的数值
    --Input value :   screen  画面ID
	--			      control 控件ID
	--			      value   控件值(0 or 1)
	--***************************************************************************
	if screen == 5 then
		if control == 12 and value == 1 then
		--CW 按键按下
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
		--MP 按键按下
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
			--选择 635nm
			set_value(5,23,0)
		end
		if control == 23 and value == 1 then
			--选择 1470nm
			set_value(5,25,0)
		end
	end

	if screen == 9 and value == 1 then --方案选择
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
