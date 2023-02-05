-- comment

--[[
    multiline
    comment
--]]

-- Valid variables: ("if" would be invalid)
If = 123 -- comment at the end of a string
local a1 = 234

if 1==2 and 2~=3 or 4<=5 then
  var3 = 123
end

str = 'text\''
str = "text\'"
str = [[
i am a string
]]
str = [=====[
me too ]]
]=====]

-- numbers (wait for how statics work?)
num = 3
num = 3.0
num = 3.1416
num = 314.16e-2
num = 0.31416E1
num = 0xff
num = 0x56


-- should we keep this??
