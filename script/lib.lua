--[[
  各種C言語から持ってきた関数とか
]]--

-- テキストの表示
function text(msg, x, y)
	Mess_add_word(mess, x, y, msg)
end

-- 画像の表示
function draw(name, x, y)
	Twod_add_image(twod, x, y, name)
end

-- エリアと方角の判断 (bool値を返す)
function area_hougaku(x, y)
	local area = Player_get_area(player)
	local hougaku = Player_get_hougaku(player)

	return area == x and hougaku == y
end

-- Room_act関連
function room_act(msg)
	 Room_act(room, msg)
end

--Player_act関連
function player_act(msg)
	Player_act(player, msg)
end	

-- 入力されたコマンドの取得
function get_command()
	local command = console_d_bag(console)
	
	command = string.gsub(command, "^%s+", "") -- 先頭の空白を消す
	command = string.gsub(command, "%s+$", "") -- 最後の空白を消す
	command = string.gsub(command, "%s+", " ") -- 間の空白は一個に統一
	command = string.lower(command) -- 小文字に統一
	
	return command
end

--[[
  only_once
  
  一回だけしか実行しない処理をつくる。
      一回だけしか実行したくない処理
    end)
]]--
local funcs = {}

function only_once(func)
  if not funcs[func] then
    funcs[func] = true
    func()
  end
end
