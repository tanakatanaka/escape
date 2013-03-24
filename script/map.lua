
map = {[0] = {}, [1] = {}, [2] = {}, [3] = {}}

-- (area, hougaku) にいるとき見えるものの配列を返す。
function map.print_all()
  for h = 0, 3 do
  	for a, objects in pairs(map[h]) do
		for name, value in pairs(objects) do
			print(h, a, name, value)
		end
  	end
  end
end

function map.check_all(area, hougaku)
	local list = {}
	local objects = map[hougaku][area]
	if objects then
		for name, value in pairs(objects) do
			if value then
				table.insert(list, name)
			end
		end
	end
	return list
end

-- (area, hougaku) にいるときnameが見えるならtrue、見えないならfalseを返す。
function map.check(area, hougaku, name)
  return not not (map[hougaku][area] and map[hougaku][area][name])
end

local function set(area, hougaku, value, ...)
  local names = {...}

  if #names == 0 then error("引数が足りません") end

  if not map[hougaku][area] then
  	map[hougaku][area] = {}
  end

  for i = 1, #names do
	map[hougaku][area][names[i]] = value
  end
end

-- (area, hougaku) にあるnameをcheckで出なくする。
function map.hide(area, hougaku, ...)
  set(area, hougaku, false, ...)
end

--配列にエリアと方角を指定して名前を保存する関数
-- (area, hougaku) にnameをcheckで見えるようにする。
function map.show(area, hougaku, ...)
  set(area, hougaku, true, ...)
end
