function assert(condition: bool, message: str)
    if not condition then
        printf("!!!!!! Assertion failed: %s\n", message)
    end
end

a = 1
assert(a == 1, "a should be 1")
assert(a == 2, "This should fail, since a is not 2, but 1")


-- -- Check variable declaration
printf("\n\n------------------VARIABLE DECLARATION------------------\n")
b = 16^0.5
a = -5.32
c = 10
e = "1323"
d = (a - 3) + c
printf("Example of printing values of a,b,c,d,e: %.2f, %.2f, %.2f, %f, '%s'\n", a, b, c, d, e)
assert(a == -5.32, "a should be -5.32")
assert(b == 4, "b should be 4")
assert(c == 10, "c should be 10")
assert(d > 1.679 and d < 1.681, "d should be 1.68")


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

-- --check for fibonacci
printf("\n\n------------------FIBONACCI------------------\n")
function fib(n: num) -> num
    if n < 2 then
        return n
    else
        return fib(n - 1) + fib(n - 2)
    end
    return 0
end

result = fib(5)
printf("fib(5) = %.3f\n", result)
assert(result == 5, "fib(5) should be 5")







-- --Check numeric for
-- printf("\n\n------------------FOR------------------\n")
-- for i = 1, 10, 1 do
--   ff = i * 2
--   printf("I = %.3f, FF = %.3f\n", i, ff)
-- end
--
-- check break in for
-- printf("\n\n------------------FOR WITH BREAK------------------\n")
-- last_i = 0
-- for i = 1, 10, 1 do
--   last_i = i
--   ff = i * 2
--   printf("I = %.3f, FF = %.3f\n", i, ff)
--   if i == 5 then
--     break
--   end
-- end
-- printf("For with break finished, last I = %.3f\n", last_i)
-- assert(last_i == 5, "i should be 5")
