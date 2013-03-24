
local map = {{}, {}, {}, {}}

--配列にエリアと方角を指定して名前を保存する関数
function objects_at(area, hougaku, names)
  local names = string.split(names, "%s+")
  for i = 1, #names do
    single_object(area, hougaku, names[i])
  end
end

object(0, 0, "door")
object(1, 2, "door")
for i = 1, 3 do object(i, 3, "pict") end
object(3, 3, "slide")
object(4, 0, "paper")
object(5, 1, "pot")
object(6, 1, "black box", "green box", "yellow box")
object(6, 3, "table", "hammer", "cup")
object(7, 1, "lamp", "bed", "pillow", "clothes")




