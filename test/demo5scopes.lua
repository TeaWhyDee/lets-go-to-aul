a = "ga"
b = "gb"

function f(a: str)
  a = "upd_a" -- use parameter
  b = "upd_b"
  c = "loc_c"
  printf("a, b, c = %s, %s, %s\n", a, b, c)
end

f(a)
printf("a, b = %s, %s\n", a, b) -- c not defined

