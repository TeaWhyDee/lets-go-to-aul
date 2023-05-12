

-- --Check if block
printf("\n\n------------------IF------------------\n")
a = 14
printf("A before is %.3f\n", a)
if a < 10 then
  a = 12
  printf("A = %.3f\n", a)
elseif a > 20 then
  a = 22
  printf("A = %.3f\n", a)
else
  a = 32
  printf("A = %.3f\n", a)
end
printf("A after = %.3f\n", a)
assert(a == 32, "a should be 32")
