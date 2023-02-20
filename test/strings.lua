
string = "newline:\
another newline:\ntab:\tbackslash:\\"

print(string)

string2 = "opening curly: \123"; other = "sd"

-- These all are same string
a = 'alo\n123"'
a = "alo\n123\""
a = '\97lo\10\04923"'
a = [[alo
123"]]
a = [==[
alo
123"]==]

-- no escape sequences in this one
b = [[
\ me when \n
]]

if (a>5) then
  print()
end

print(b)
