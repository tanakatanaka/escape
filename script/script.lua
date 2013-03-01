
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

if area == 0 and hougaku == 0 then
  text('Please push "Esc__key"', 10, 10)
  text('and type "check door"', 10, 26)
  
  if command == "open door" then
    room_open_door()
  end
end

if command == "check pict" then
  if area == 1 and hougaku == 3 then
    text("title stussy", 10, 10)
    text("memo", 10, 26)
    draw("meta/stussy.png")
  elseif area == 2 and hougaku == 3 then
    text("pict B", 10, 10)
  elseif area == 3 and hougaku == 3 then
    text("pict C", 10, 10)
  end
end

slide_unlocked = false
slide_opened = false
if area == 3 and hougaku == 1 and not slide_opened then
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

if area == 5 and hougaku == 1 then
  if command == "check pot" then
    text("pot sugoi", 10, 10)
  elseif command == "break pot" then
    room_act("break_pot")
  end
end

hammer_time = false
if area == 6 and hougaku == 3 then
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
