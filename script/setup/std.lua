
function table.iforeach(f, ...)
   -- assert (type (f) == "function") [wouldn't allow metamethod __call]
   local nargs = select("#", ...)
   if nargs==1 then -- Quick iforeach (most common case), just one table arg
      local t = ...
      assert (type (t) == "table")
      for i = 1, #t do 
         local result = f (t[i])
         -- If the function returns non-false, stop iteration
         if result then return result end
      end
   else -- advanced case: boundaries and/or multiple tables
      -- 1 - find boundaries if any
      local  args, fargs, first, last, arg1 = {...}, { }
      if     type(args[1]) ~= "number" then first, arg1 = 1, 1
      elseif type(args[2]) ~= "number" then first, last, arg1 = 1, args[1], 2
      else   first,  last, i = args[1], args[2], 3 end
      assert (nargs > arg1)
      -- 2 - determine upper boundary if not given
      if not last then for i = arg1, nargs do 
            assert (type (args[i]) == "table")
            last = max (#args[i], last) 
      end end
      -- 3 - perform the iteration
      for i = first, last do
         for j = arg1, nargs do fargs[j] = args[j][i] end -- build args list
         local result = f (table.unpack (fargs)) -- here is the call
         -- If the function returns non-false, stop iteration
         if result then return result end
      end
   end
end

function table.imap (f, ...)
   local result, idx = { }, 1
   local function g(...) result[idx] = f(...);  idx=idx+1 end
   table.iforeach(g, ...)
   return result
end

function table.ifold (f, acc, ...)
   local function g(...) acc = f (acc,...) end
   table.iforeach (g, ...)
   return acc
end

-- function table.ifold1 (f, ...)
--    return table.ifold (f, acc, 2, false, ...)
-- end

function table.izip(...)
   local function g(...) return {...} end
   return table.imap(g, ...)
end

function table.ifilter(f, t)
   local yes, no = { }, { }
   for i=1,#t do table.insert (f(t) and yes or no, t[i]) end
   return yes, no
end

function table.icat(...)
   local result = { }
   for t in values {...} do
      for x in values (t) do
         table.insert (result, x)
      end
   end
   return result
end

function table.iflatten (x) return table.icat (table.unpack (x)) end

function table.irev (t)
   local result, nt = { }, #t
   for i=0, nt-1 do result[nt-i] = t[i+1] end
   return result
end

function table.isub (t, ...)
   local ti, u = table.insert, { }
   local args, nargs = {...}, select("#", ...)
   for i=1, nargs/2 do
      local a, b = args[2*i-1], args[2*i]
      for i=a, b, a<=b and 1 or -1 do ti(u, t[i]) end
   end
   return u
end

function table.iall (f, ...)
   local result = true
   local function g(...) return not f(...) end
   table.iforeach(g, ...)
   return result
end

function table.iany (f, ...)
   local function g(...) return not f(...) end
   return table.iall(g, ...)
end

function table.tostring(t, ...)
   local LINE_MAX, PRINT_HASH = math.huge, true
   for _, x in ipairs {...} do
      if type(x) == "number" then LINE_MAX = x
      elseif x=="nohash" then PRINT_HASH = false
      end
   end
   
   local current_offset =  0  -- indentation level
   local xlen_cache     = { } -- cached results for xlen()
   local acc_list       = { } -- Generated bits of string
   local function acc(...)    -- Accumulate a bit of string
      local x = table.concat{...}
      current_offset = current_offset + #x
      table.insert(acc_list, x) 
   end
   local function valid_id(x)
      -- FIXME: we should also reject keywords.
      return type(x) == "string" and x:match "[a-zA-Z_][a-zA-Z0-9_]*"
   end
   
   -- Compute the number of chars it would require to display the table
   -- as a single line. Helps to decide whether some carriage returns are
   -- required. Since the size of each sub-table is required many times,
   -- it's cached in [xlen_cache].
   local xlen_type = { }
   local function xlen(x, tracker)
      tracker = tracker or { }
      if x==nil then return #"nil" end
      if tracker[x] then return #tostring(x) end
      local len = xlen_cache[x]
      if len then return len end
      local f = xlen_type[type(x)]
      if not f then return #tostring(x) end
      len = f (x, tracker) 
      xlen_cache[x] = len
      return len
   end

   -- optim: no need to compute lengths if I'm not going to use them
   -- anyway.
   if LINE_MAX == math.huge then xlen = function() return 0 end end

   xlen_type["nil"] = function() return 3 end
   function xlen_type.number(x)  return #tostring(x) end
   function xlen_type.boolean(x) return x and 4 or 5 end
   function xlen_type.string(x)  return #string.format("%q",x) end
   function xlen_type.table (adt, tracker)

      -- Circular references detection
      tracker = table.shallow_copy(tracker)
      tracker [adt]  = true 

      local has_tag  = valid_id(adt.tag)
      local alen     = #adt
      local has_arr  = alen>0
      local has_hash = false
      local x = 0
      
      if PRINT_HASH then
         -- first pass: count hash-part
         for k, v in pairs(adt) do
            if k=="tag" and has_tag then 
               -- this is the tag -> do nothing!
            elseif type(k)=="number" and k<=alen and math.fmod(k,1)==0 then 
               -- array-part pair -> do nothing!
            else
               has_hash = true
               if valid_id(k) then x=x+#k
               else x = x + xlen (k, tracker) + 2 end -- count surrounding barckets
               x = x + xlen (v, tracker) + 5          -- count " = " and ", "
            end
         end
      end

      for i = 1, alen do x = x + xlen (adt[i], tracker) + 2 end -- count ", "
      
      if not (has_tag or has_arr or has_hash) then return 3 end
      if has_tag then x=x+#adt.tag+1 end
      if not (has_arr or has_hash) then return x end
      if not has_hash and alen==1 and type(adt[1])~="table" then
         return x-2 -- substract extraneous ", "
      end
      return x+2 -- count "{ " and " }", substract extraneous ", "
   end
   
   -- Recursively print a (sub) table at given indentation level.
   -- [newline] indicates whether newlines should be inserted.
   local function rec (adt, indent, tracker)
      local function acc_newline()
         acc ("\n"); acc (string.rep (" ", indent)) 
         current_offset = indent
      end
      local x = { }
      x["nil"] = function() acc "nil" end
      function x.number()   acc (tostring (adt)) end
      function x.string()   acc (string.format ("%q", adt)) end
      function x.boolean()  acc (adt and "true" or "false") end
      function x.table()
         tracker[adt]   = true
         local has_tag  = valid_id(adt.tag)
         local alen     = #adt
         local has_arr  = alen>0
         local has_hash = false
         local new_indent
         if has_tag then acc("`"); acc(adt.tag) end

         -- First pass: handle hash-part
         if PRINT_HASH then
            for k, v in pairs(adt) do
               if k=="tag" and has_tag then -- this is the tag -> do nothing!
               elseif type(k)=="number" and k<=alen and math.fmod(k,1)==0 then
                  -- nothing: this an array-part pair, parsed later
               else  -- hash-part pair

                  -- Is it the first time we parse a hash pair?
                  if not has_hash then acc "{ "; indent = current_offset
                  else acc ", " end

                  -- Determine whether a newline is required
                  local is_id, expected_len = valid_id(k)
                  if is_id then expected_len = #k + xlen (v, tracker) + #" = , "
                  else expected_len = xlen (k, tracker) + 
                                      xlen (v, tracker) + #"[] = , " end
                  if has_hash and expected_len + current_offset > LINE_MAX
                  then acc_newline() end
                  
                  -- Print the key
                  if is_id then acc(k); acc " = " 
                  else  acc "["; rec (k, current_offset, tracker); acc "] = " end

                  -- Print the value
                  rec (v, current_offset, tracker)
                  has_hash = true
               end
            end
         end

         -- now we know whether there's a hash-part, an array-part, and a tag.
         -- Tag and hash-part are already printed if they're present.
         if not has_tag and not has_hash and not has_arr then acc "{ }"; return
         elseif has_tag and not has_hash and not has_arr then return -- nothing!
         else -- has_hash or has_arr
            if has_hash and has_arr then acc ", " 
            elseif has_tag and not has_hash and alen==1 and type(adt[1])~="table" then
               -- No brace required; don't print "{" and return before printing "}"
               acc (" "); rec (adt[1], new_indent, tracker); return
            elseif not has_hash then
               -- Braces required, but not opened by hash-part handler yet
               acc "{ "; indent = current_offset 
            end

            -- 2nd pass: array-part
            if has_arr then 
               rec (adt[1], new_indent, tracker)
               for i=2, alen do 
                  acc ", ";                   
                  if   current_offset + xlen (adt[i], { }) > LINE_MAX
                  then acc_newline() end
                  rec (adt[i], new_indent, tracker) 
               end
            end
            acc " }"
         end
      end
      local y = x[type(adt)]
      if y then y() else acc(tostring(adt)) end
   end
   rec(t, 0, { })
   return table.concat (acc_list)
end

function string.split(str, pat)
   local t = {} 
   local fpat = "(.-)" .. pat
   local last_end = 1
   local s, e, cap = string.find(str, fpat, 1)
   while s do
      if s ~= 1 or cap ~= "" then
          table.insert(t,cap)
       end
      last_end = e+1
      s, e, cap = string.find(str, fpat, last_end)
   end
   if last_end <= string.len(str) then
      cap = string.sub(str, last_end)
      table.insert(t, cap)
   end
   return t
end

function min (a, ...)
   for n in values{...} do if n<a then a=n end end
   return a
end

function max (a, ...)
   for n in values{...} do if n>a then a=n end end
   return a
end

function compose(...)
   local args = {...}
   local function g (...)
      local result = {...}
      for i=#args, 1, -1 do result = {args[i](table.unpack(result))} end
      return table.unpack (result)
   end
   return g
end

printf = compose(print, string.format)
table.print = compose(print, table.tostring)

function table.values (x) 
   local function iterator (state)
      local it
      state.content, it = next(state.list, state.content) 
      return it
   end
   return iterator, { list = x }
end

function table.keys (x) 
   local function iterator (state)
      local it = next(state.list, state.content) 
      state.content = it
      return it
   end
   return iterator, { list = x }
end
