require "script/setup/strict"
require "script/lib"

--[[ 変数宣言 ]]--
local slide_unlocked = false
local slide_opened = false
local hammer_time = false
local break_pot = false
local get_paper1 = false

--[[
  条件用の変数
    command
    area
    hougaku
  操作する関数
    text("文字", X, Y)
    draw(画像番号, X, Y)
    room_act("命令")
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
	
	if not command then
	  return
	end
  	
  	if area_hougaku(0, 0) then
	  if command == "check door" then
	     text("please open door", 10, 10)
	  end
	end
  	
	if area_hougaku(0, 0) then
	  if command == "open door" then
	  	 room_act("open_door")
	  end
	end
	
	if command == "check pict" then
	  if area_hougaku(1, 3) then
	    text("title stussy", 10, 10)
	    text("memo", 10, 26)
	    draw("stussy", 50 , 10)
	  elseif area_hougaku(2, 3) then
	    text("pict B", 10, 10)
	  elseif area_hougaku(3, 3) then
	    text("pict C", 10, 10)
	  end
	end

	if area_hougaku(3, 1) and not slide_opened then
	  if command == "check slide" then
	    text("plead enter the code", 10, 10)
	  elseif command == "code 100" and not slide_unlocked then
	    text("the slide unlocked", 10, 10)
	    slide_unlocked = true
	  elseif slide_unlocked and command == "open slide" then
	    room_act("open_slide")
	    slide_opened = true
	  end
	end

	if area_hougaku(5, 1) then
		if not break_pot and command == "check pot" then
		   text("pot sugoi", 10, 10)
		elseif  hammer_time and command == "break pot" then
		   room_act("break_pot")
		   break_pot = true 
		elseif break_pot and not get_paper1 and command == "get paper" then
			room_act("get_paper")
	  	end
	end

	
	if area_hougaku(6, 3) then
	  if command == "check table" then
	    text("cup and hammer on the table", 10, 10)
	    room_get_hammer()
	  elseif not hammer_time and command == "check hammer" then
	    text("hammer sugoi", 10, 10)
	  elseif not hammer_time and command == "get hammer" then
	    text("you get a hammer", 10, 10)
	    room_act("get_hammer")
	    hammer_time = true
	  elseif command == "check cup" then
	    text("cup sugoi", 10, 10)
	  end
	end
end
