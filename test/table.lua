struct S
  text: str
  new(t: str)
    text = t
  end
end

st = S("e")

a: table[int, str] = { "asd" }
b: table[str, s] = { key = 2 } 

a[1] = b["key"]
a[1] = st.text

a = {x=1, y=2, z=3}
a.x = 2

zzzz: table[num, function(int) -> int] = { d }

wwwww = zzzz[1](2)