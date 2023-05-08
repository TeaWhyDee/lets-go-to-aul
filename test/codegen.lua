-- printf("Goodbye, Aul!\n")
-- a = 3
-- b = 5
-- c = 10
-- e = "1323"
--
-- d = (a - b) + c
--
-- printf("Values of a,b,c,d: %.1f, %.1f, %.1f, %.1f, '%s'\n", d, e)


-- --Check while block
-- printf("\nWHILE\n")
-- a = 10
-- printf("A before = %.3f\n", a)
-- while a > 0 do
--   a = a - 1
--   printf("A = %.3f\n", a)
-- end
-- printf("A after = %.3f\n", a)


-- --Check do end block
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


-- --Check repeat until block
-- printf("\nREPEAT UNTIL\n")
-- a = 1
-- repeat
--   printf("A = %.3f\n", a)
--   a = a * 2
-- until a ~= 8
-- printf("A after = %.1f\n", a)


-- --Next part is not working for now!

-- --Check if block (for now not working)
-- printf("\nIF\n")
-- a = 14
-- printf("A is %.3f\n", a)
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


-- --Check numeric for (for now not working)
-- printf("\nNUMERIC FOR\n")
-- for i = 1, 10, 1 do
--   printf("I = %.3f\n", i)
-- end
