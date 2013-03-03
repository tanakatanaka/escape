
function text(msg, x, y)
	Mess_add_word(mess, x, y, msg)
end

function area_hougaku(x, y)
	local area = Player_get_area(player)
	local hougaku = Player_get_hougaku(player)

	return area == x and hougaku == y
end

function execute_debug_command(command)
	if not string.match(command, ";$") then
	  return false
	end
	
  local ok, err = load(command, "command", "t")
  if err then
    ok, err = load("return (" .. command .. ")", "command-expr", "t")
    if err then
      print(err)
      return true
    else
	    print(">> " .. command)
	    print("=> " .. tostring(ok()))
    end
  else
    print("!> " .. command)
    ok()
    print("=> ok")
  end
  
  return true
end

function get_command()
	local command = console_d_bag(console)
	
	-- デバッグコマンド
	if execute_debug_command(command) then
	  return nil
	end
	
	command = string.gsub(command, "^%s+", "") -- 先頭の空白を消す
	command = string.gsub(command, "%s+$", "") -- 最後の空白を消す
	command = string.gsub(command, "%s+", " ") -- 間の空白は一個に統一
	command = string.lower(command) -- 小文字に統一
	
	return command
end

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
	if area_hougaku(0, 0) then
		text('Please push "Esc__key"', 10, 10)
		text('and type "check door"', 10, 26)
	end
end

function on_command()
	local command = get_command()
	
	if not command then
	  return
	end
  
	if area_hougaku(0, 0) then
	  if command == "open door" then
	  	Room_act(room, "open_door")
	  end
	end
	
	if command == "check pict" then
	  if area_hougaku(1, 3) then
	    text("title stussy", 10, 10)
	    text("memo", 10, 26)
	    draw("meta/stussy.png")
	  elseif area_hougaku(2, 3) then
	    text("pict B", 10, 10)
	  elseif area_hougaku(3, 3) then
	    text("pict C", 10, 10)
	  end
	end

	slide_unlocked = false
	slide_opened = false

	if area_hougaku(3, 1) and not slide_opened then
	  if command == "check slide" then
	    text("plead enter the code", 10, 10)
	  elseif command == "code 100" and not slide_unlocked then
	    text("the slide unlocked", 10, 10)
	    slide_unlocked = true
	  elseif command == "open slide" then
	    room_act("open_slide")
	    slide_opened = true
	  end
	end

	if area_hougaku(5, 1) then
	  if command == "check pot" then
	    text("pot sugoi", 10, 10)
	  elseif command == "break pot" then
	    room_act("break_pot")
	  end
	end

	hammer_time = false
	if area_hougaku(6, 3) then
	  if command == "check table" then
	    text("cup and hammer on the table", 10, 10)
	    room_get_hammer()
	  elseif command == "check hammer" then
	    text("hammer sugoi", 10, 10)
	  elseif command == "get hammer" then
	    text("you get a hammer", 10, 10)
	    room_act("get_hammer")
	    hammer_time = true
	  elseif command == "check cup" then
	    text("cup sugoi", 10, 10)
	  end
	end
end

