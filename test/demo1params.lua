a = "first"

function f(a: str)
  a = "updated" -- use parameter
  printf("a = %s\n", a)
end

f(a)
printf("a = %s\n", a)
