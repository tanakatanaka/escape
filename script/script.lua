





if area == 0 and hougaku == 0 then
  text('Please push "Esc__key"', 10, 10)
  text('and type "check door"', 10, 26)
end




if command == "check pict" then
  text("title stussy", 10, 10)
  text("memo", 10, 26)
  draw("meta/stussy.png")
end


if area == 0 and hougaku == 0 and command == "code 100" and not slide_is_opened then
   text("the slide unlocked", 10, 10)
   un_lock()
   slide_opened = true
end





