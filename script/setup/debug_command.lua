
--[[
デバッグコマンドの実行
--]]
function execute_debug_command(command)
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
