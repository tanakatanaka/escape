--[[
  各種C言語から持ってきた関数とか
--]]

require "script/setup/std"
require "script/setup/strict"
require "script/setup/debug_command"
require "script/map"

math.randomseed(os.time())

-- テキストのみ表示
function text(msg, x, y)
	Mess_add_word(mess, x, y, encode_to_c(msg))
end

-- 画像の表示
function draw(name, x, y)
	Twod_add_image(twod, x, y, name)
end

function get_area()
	return Player_get_area(player)
end

function get_hougaku()
	return Player_get_hougaku(player)
end

-- エリアと方角の判断 (bool値を返す)
function area_hougaku(x, y)
	local area = get_area()
	local hougaku = get_hougaku()

	return area == x and hougaku == y
end

local answer = math.random(0,99)
local answer_count = 0

function show_answer()
  return answer
end


function slide_quiz(number)
	
	if number == nil then
		return false
	end
	
	if number == answer then
		return true 
	end
	
	if number < answer then
          text("数字が小さいです。",10,10)
    elseif number > answer then
          text("数値が大きいです。",10,10)
	end
	
	answer_count = answer_count + 1
	if answer_count == 5 then
		text("5回間違えたので答えが変更されます。", 10, 26)
		answer = math.random(0,99)
	elseif math.abs(answer - number)  < 3 then
		text("答えとの差は 3 以内です。 ", 10, 26)
	elseif math.abs(answer - number)  < 10 then
		text("答えとの差は 10 以内です。 ", 10, 26)
	end
	
	return false
end

function drink_cup()
	
	local taste =  math.random(10)
	
	if taste <= 1 then
		text("すごい味のコーヒーだ。", 10, 10)
		player.p_state = 1
	elseif taste <= 7 then
		text("時間を忘れるくらいおいしいコーヒーだ。", 10, 10)
  		player.time_limit = player.time_limit * (4 / 5)
	else
		text("おいしいコーヒーだ。", 10, 10)
  		player.time_limit = player.time_limit + player.time_limit * (1 / 5)
	end
end

local box = {1, 2, 3}

-- 箱の中身をシャッフル
function shuffle_box()
  local j = math.random(3)
  box[j], box[3] = box[3], box[j]
  j = math.random(2)
  box[j], box[2] = box[2], box[j]
  return box
end

function show_box()
  return box
end

function box_eff(x)
	
	local y = box[x]
	
	if y == 0 then
		text("すでに開いてます。", 10, 10)
	elseif y == 1 then
		text("書類を手に入れました。", 10, 10)
		player.get_paper = player.get_paper + 1
	elseif y == 2 then
		text("ハズレ。", 10, 10)
		text("時間が減ります。", 10, 10)
		player.time_limit = player.time_limit * (2 / 3)
	elseif y == 3 then
		text("特になし。", 10, 10)
	end
		box[x] = 0
end

local jisho = 
{
	check = {"look", "watch"},
	get = {"take"},
	["break"] = {"attack" , "crush"},
	["read %1"] = {"check (.+ book)"}
}


--動詞の変換関数
function unify_verb(c)
	for verb, words in pairs(jisho) do
	  for i = 1, #words do
	     c = c:gsub(words[i], verb)
	  end
	end
	return c
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
	
	command = unify_verb(command)
	
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

-- mapの各関数の短縮版
do
	local function wrap(fun)
		return function(...)
			local area = get_area()
			local hougaku = get_hougaku()
			return fun(area, hougaku, ...)
		end
	end

	hide = wrap(map.hide)
	show = wrap(map.show)
	check_all = wrap(map.check_all)
	check = wrap(map.check)
end

