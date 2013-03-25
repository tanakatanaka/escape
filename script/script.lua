require "script/lib"

--[[ 変数宣言 ]]--
local door_open = 1.658064
local game_start = false
local slide_unlocked = false
local slide_opened = false
local get_paper0 = false
local get_paper1 = false
local get_paper2 = false
local get_paper3 = false
local get_hammer = false
local break_pot = false 
local break_lamp = false
local get_huton = false
local get_makura = false

--[モデルの描画設定]--
MV1SetVisible(room.paper1, 0);
MV1SetVisible(room.paper2, 0);
MV1SetVisible(room.paper3, 0);

shuffle_box()

--[[
  条件用の変数
    command
    area
    hougaku
  操作する関数
    text("文字", X, Y)
    draw(画像番号, X, Y)
--]]

do
	local o = map.show

	o(0, 0, "door")
	o(1, 2, "door")
	o(1, 3, "pict")
	o(2, 3, "pict")
	o(3, 3, "pict")
	o(3, 1, "slide")
	o(4, 0, "paper")
	o(5, 1, "pot")
	o(6, 1, "black box", "green box", "yellow box")
	o(6, 3, "table", "hammer", "cup")
	o(7, 1, "lamp", "bed", "pillow", "clothes")
end

function on_move()
	
	Twod_erase_image(twod)
	Mess_erase_word(mess) 
	
	if area_hougaku(0, 0) then
		only_once(function()
			text("Enter keyをすばやく２回おしてください。", 10, 10)
			text("check doorと入力してください。", 10, 26)
		end)
	end
	
	if game_start == true  and  player.area == 0 then
			player.game_end = true
		end
	
	if player.area == 1 then
		only_once(function()
			text("気の利いたコメントが出るはず。", 10, 10)
		end)
	end

	if area_hougaku(2, 0) then
		only_once(function()
			game_start = true
			room.swit = -1
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

  	if area_hougaku(0, 0) or area_hougaku(1, 2) then
	  	if command == "check door" then
	    	text("open door と入力してください。", 10, 10)
	  	elseif command == "open door" and room.rotY ~= door_open then
	  		room.swit = 1
	  	 	if area_hougaku(1, 2) then
	  	 		text("部屋を出るとゲームが終了します。", 10, 10)
	  		end
	  	end	
	end
	
	if command == "check pict" then
	  if area_hougaku(1, 3) then
	  	text("pict1", 10, 10)
	    text("タイトル : the O", 10, 26)
	    draw("o", 50 , 10)
	  elseif area_hougaku(2, 3) then
	  	text("pict2", 10, 10)
	    text("タイトル : the V", 10, 26)
	    draw("v", 50 , 10)
	  elseif area_hougaku(3, 3) then
	  	 text("pict3", 10, 10)
	     text("タイトル : the X", 10, 26)
	     draw("x", 50 , 10)
	  end
	end

	if area_hougaku(3, 1) then
		if not slide_unlocked then
			if command == "check slide" then
			    text("コード(数値)を入力してください。", 10, 10)
			    text("hint  X = pict1 + pict2 + pict3", 10, 10 + 16)
	  		elseif command == "15" then
		  		slide_unlocked = true
		  		text("正解です。", 10, 10)
		    	text("ドアが開きました。", 10, 10 + 16)
		   	   	room.s_swit = 1
	  		end 
		end
	end
	
	if area_hougaku(4, 0) then
		if not get_paper0 then
			if command == "check paper" then
				text("paper1", 10, 10)
			elseif command == "get paper" then
				MV1SetVisible(room.paper0, 0);
				get_paper0 = true
				text("書類を手に入れました。", 10, 10)
				player.get_paper = player.get_paper + 1
				hide("paper")
			end
		end
	end

	if area_hougaku(5, 1) then
		if not break_pot then
			if command == "check pot" then
		   		text("壺があります。", 10, 10)
			elseif get_hammer and command == "break pot" then
		   		MV1SetVisible(room.pot, 0);
		   		MV1SetVisible(room.paper1, 1);
		   		break_pot = true
		   		hide("pot")
			end
		elseif not get_paper1 then
		 	if command == "get paper" then
		 		MV1SetVisible(room.paper1, 0);
		 		text("書類を手に入れました。", 10, 10)
			   	get_paper1 = true
			   	player.get_paper = player.get_paper + 1
				hide("paper")
			end
		end
	end
	
	if area_hougaku(6, 1) then
		if command == "check box" then
		   text("3つの箱があります。", 10, 10)
		elseif command == "open black box" then 
			box_eff(1)
			MV1SetFrameVisible(room.table, room.black_cap, 0);
		elseif command == "open green box" then
			box_eff(2)
			MV1SetFrameVisible(room.table, room.green_cap, 0);
		elseif command == "open yellow box" then 
			box_eff(3)
			MV1SetFrameVisible(room.table, room.yellow_cap, 0);
		end 
	end
	
	if area_hougaku(6, 3) then
  		if command == "check table" then
  			local list = {}

  			if check("cup") then table.insert(list, "カップ") end
  			if check("hammer") then table.insert(list, "ハンマー") end

  			local msg = "テーブルの上に"

  			if #list == 0 then
  				msg = msg .. "はなにもありません。"
  			else
  				msg = msg .. table.concat(list, "と") .. "があります。"
  			end
    		
    		text(msg, 10, 10)
	 	elseif command == "check cup" then
	    	text("カップがあります。", 10, 10)
		elseif not get_hammer then
	  		if command == "check hammer" then
	    		text("ハンマーがあります。", 10, 10)
	  		elseif command == "get hammer" then
	    		text("ハンマーを入手しました。", 10, 10)
	    		text("break コマンドが使えます。", 10, 10 + 16)
	    		MV1SetVisible(room.hammer, 0);
	    		get_hammer = true
				hide("hammer")
	    	end
	  	end
	end
	
	if area_hougaku(7, 1) then
		if command == "check bed" then
			text("硬そうなベッドです。", 10, 10)
		elseif command == "get pillow" and not get_makura  then
			text("マクラを手に入れました。", 10, 10);
			MV1SetFrameVisible(room.bed, room.makura, 0);
			get_makura = true
			hide("pillow")
		end
			
		if get_huton then
			if not get_paper3 and command == "get paper" then
				MV1SetVisible(room.paper3, 0);
	 			text("書類を手に入れました。", 10, 10)
		   		get_paper3 = true
		   		player.get_paper = player.get_paper + 1
				hide("paper")
			end
		else 
			if command == "get clothes" then
				text("フトンを手に入れました。", 10, 10);
				MV1SetFrameVisible(room.bed, room.huton, 0);
				MV1SetVisible(room.paper3, 1);
				get_huton = true
				show("paper")
				hide("clothes")
			end
		end

		if not break_lamp then
			if  get_hammer and command == "break lamp" then
				MV1SetFrameVisible(room.bed, room.stand, 0);
				MV1SetVisible(room.paper2, 1);
				break_lamp = true
				show("paper")
				hide("lamp")
			end
		else 
			if  not get_paper2 and command == "get paper" then
				MV1SetVisible(room.paper2, 0);
	 			text("書類を手に入れました。", 10, 10)
		   		get_paper2 = true
		   		player.get_paper = player.get_paper + 1
				hide("paper")
			end
		end
	end
	
	if command == "check" then			
		local objects = check_all()

		if #objects == 0 then
			text("特に見当たるものはありません。", 10, 10)
		else
			for i = 1, #objects do
	  			text(objects[i] .. " が見えます。", 10, 10 + 16 * (i - 1))
			end
		end
	end	
end
