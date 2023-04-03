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
