-- printf("Goodbye, Aul!\n")
-- a = 3.5
a = "ima"
printf("Values of a: %s'\n", a)
-- b = 3
-- printf("Values of a,b: %s, %.1f'\n", a, b)
-- c = true

function f()
  a = "ima2"
  d = "imd"
  printf("Values of a: %s'\n", a)
  printf("in func:   a, d: %s, %s!\n", a, d)
end
f()
printf("Values of a: %s'\n", a)
--
-- function f1()
--   d = 2
--   printf("a, d: %s, %.1f!\n", a, d)
-- end
--
-- f1()
-- b = 16^0.5

-- c = 10
-- e = "1323"
-- d = (a - b) + c
-- printf("Values of a,b,c,d, e: %.1f, %.1f, %.1f, %.1f, '%s'\n", a, b, c, d, e)


--Check while block
-- printf("\nWHILE\n")
-- printf("A before = %.3f\n", a)
-- a = 10
-- while a > 0 do
--   a = a - 1
--   printf("A = %.3f\n", a)
-- end
-- printf("A after = %.3f\n", a)

--Check repeat until block
-- printf("\nREPEAT UNTIL\n")
-- a = 1
-- repeat
--   printf("A = %.3f\n", a)
--   a = a * 2
-- until a ~= 8
-- printf("A after = %.1f\n", a)

--Check do end block
-- printf("\nDO END\n")
-- a = 1
-- printf("A before = %.3f\n", a)
-- do
--   b: num = 14
--   a = a * b
--   printf("A = %.3f\n", a)
--   printf("B = %.3f\n", b)
-- end
-- printf("A after = %.3f\n", a)
--
-- --Check if block
-- printf("\nIF\n")
-- a = 14
-- printf("A before is %.3f\n", a)
-- if a < 10 then
--   a = 12
--   printf("A = %.3f\n", a)
-- elseif a > 20 then
--   a = 22
--   printf("A = %.3f\n", a)
-- else
--   a = 32
--   printf("A = %.3f\n", a)
-- end
-- printf("A after = %.3f\n", a)
--
-- --Check numeric for
-- printf("\nFOR\n")
-- for i = 1, 10, 1 do
--   ff = i * 2
--   printf("I = %.3f, FF = %.3f\n", i, ff)
-- end
-- printf("For finished\n")
--
-- -- check break in for
-- printf("\nBREAK\n")
-- for i = 1, 10, 1 do
  -- ff = i * 2
  -- printf("I = %.3f, FF = %.3f\n", i, ff)
--   if i == 5 then
--     break
--   end
-- end
-- printf("For with break finished\n")


-- Below is not working yet (with all code of the above, but works by itself)
-- check for fibonacci
-- function fib(n: num) -> num
--     if n < 2 then
--         return n
--     else
--         return fib(n - 1) + fib(n - 2)
--     end
--     return 0
-- end
--
-- result = fib(5)
--
-- printf("fib(5) = %.3f, expected(5)\n", result)
