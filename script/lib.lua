--[[
  各種C言語から持ってきた関数とか
]]--

require "script/setup/std"
require "script/setup/strict"

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

function box_eff(x)
	if x == 1 then
		text("you got paper", 10, 10)
		player.get_paper = player.get_paper + 1
	elseif x == 2 then
		text("hazure", 10, 10)
		text("minus time", 10, 10)
		player.time_limit = player.time_limit * (2 / 3)
	elseif x == 3 then
		text("tokuninasi", 10, 10)
	end
end

-- デバッグコマンドの実行
local execute_debug_command
do

    execute_debug_command = function (command)
        if not command:match(";$") then
            return false
        end

        local ok, err = load("return " .. command, "command-print")

        if err then
            ok, err = load(command, "command")
        end

        if ok then
            io.write(">> " .. command .. "\n=> ")
            local result = table.pack(ok())
            if result.n == 0 then
                print("ok")
            else
                for i = 1, result.n do
                    table.print(result[i])
                end
            end
        else
            print(err)
        end
      
        return true
    end
end

-- 入力されたコマンドの取得
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
  only_once
  
  一回だけしか実行しない処理をつくる。
  書き方：
  	only_once(function()
      一回だけしか実行したくない処理
    end)
--]]
local funcs = {}

function only_once(func)
  if not funcs[func] then
    funcs[func] = true
    func()
  end
end
