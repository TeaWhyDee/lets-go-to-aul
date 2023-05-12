-- Check a while block
printf("\n\n------------------WHILE------------------\n")
a = 10
while a > 0 do
  a = a - 1.5
  printf("A = %.3f\n", a)
end
printf("A after = %.3f\n", a)
assert(a == -0.5, "a should be -0,5")

-- Check repeat until block
printf("\n\n------------------REPEAT UNTIL------------------\n")
a = 1
repeat
  printf("A = %.3f\n", a)
  a = a * 2
until a ~= 8
printf("A after = %.1f\n", a)
assert(a == 8, "a should be 8")


-- -- Check do end block
printf("\n\n------------------DO END------------------\n")
a = 1
printf("A before = %.3f\n", a)
do
  b: num = 14
  a = a * b
  printf("A = %.3f\n", a)
  printf("B = %.3f\n", b)
end
printf("A after = %.3f\n", a)
assert(a == 14, "a should be 14")
