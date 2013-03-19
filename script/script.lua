require "script/lib"

--[[ 変数宣言 ]]--
local slide_unlocked = false
local slide_opened = false

shuffle_box()

--[[
  条件用の変数
    command
    area
    hougaku
  操作する関数
    text("文字", X, Y)
    draw(画像番号, X, Y)
]]--

function on_move()
	
	Twod_erase_image(twod)
	Mess_erase_word(mess) 
	
	if area_hougaku(0, 0) then
		only_once(function()
			text('Please push "Esc__key"', 10, 10)
			text('and type "check door"', 10, 26)
		end)
	end
end

function on_command()
	
	Twod_erase_image(twod)
	Mess_erase_word(mess)
	
	local command = get_command()
	local objects
	
	if not command then
	  return
	end
  	
  	if area_hougaku(0, 0) then
  		objects = {"door"}
	  	if command == "check door" then
	    	text("please open door", 10, 10)
	  	elseif command == "open door" and room.swit ~= 1 then
	  	 	room.swit = 1
	  	end
	end
	
	if command == "check pict" then
	  if area_hougaku(1, 3) then
	  	text("pict1", 10, 10)
	    text("title : the O", 10, 26)
	    draw("o", 50 , 10)
	  elseif area_hougaku(2, 3) then
	  	text("pict2", 10, 10)
	    text("title : the V", 10, 26)
	    draw("v", 50 , 10)
	  elseif area_hougaku(3, 3) then
	  	 text("pict3", 10, 10)
	     text("title : the X", 10, 26)
	     draw("x", 50 , 10)
	  end
	end
	--pict保存用
	if area_hougaku(2, 3) or area_hougaku(2, 3) or area_hougaku(3, 3) then
       objects = {"pict"}
	end
	
	if area_hougaku(3, 1) then
		objects = {"slide"}
		if not slide_unlocked then
			if command == "check slide" then
			    text("plead enter the code", 10, 10)
			    text("please 'input code X'", 10, 26)
			    text("hint  X = pict1 + pict2 + pict3", 10, 10+ 16 * 2)
	  		elseif command == "code 15" then
		  		slide_unlocked = true
		    	text("the slide unlocked", 10, 10)
			end
		elseif slide_unlocked then
			if room.s_swit ~= 1 and command == "open slide" then
		   	   room.s_swit = 1
	  		end 
		end
	end
	
	if area_hougaku(4, 0) then
		if not room.get_paper0 then
			if command == "check paper" then
				text("paper1", 10, 10)
			elseif command == "get paper" then
				room.get_paper0 = true
				text("you got paper", 10, 10)
				player.get_paper = player.get_paper + 1
			end
		end
	end

	if area_hougaku(5, 1) then
		if not room.break_pot then
			if command == "check pot" then
		   		text("pot sugoi", 10, 10)
			elseif room.get_hammer and command == "break pot" then
		   		room.break_pot = true
			elseif room.break_pot and not room.get_paper1 and command == "get paper" then
				room.get_paper1 = true
				player.get_paper = player.get_paper + 1
	  		end
		end
	end
	
	if area_hougaku(6, 1) then
		if command == "check box" then
		   text("There is a box of green yellow black", 10, 10)
		elseif command == "open black box" then 
			box_eff(1)
		elseif command == "open green box" then
			box_eff(2)
		elseif command == "open yellow box" then 
			box_eff(3)
		end 
	end
	
	if area_hougaku(6, 3) then
		if not room.get_hammer then
	  		if command == "check table"  then
	    		text("cup and hammer on the table", 10, 10)
	  		elseif command == "check hammer" then
	    		text("hammer sugoi", 10, 10)
	  		elseif command == "get hammer" then
	    		text("you got a hammer", 10, 10)
	    		room.get_hammer = true
	    		MV1SetFrameVisible(room.table, room.black_cap, 0);
	    	end
	 	elseif command == "check cup" then
	    	text("cup sugoi", 10, 10)
	  	end
	end

	if  command == "check" then	
		for i = 1, #objects do
	  		text(objects[i] .. "が見える", 10, 10 + 26 * i)
		end
	end
	
end
