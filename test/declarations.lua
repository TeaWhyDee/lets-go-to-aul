function assert(condition: bool, message: str)
    if not condition then
        printf("!!!!!! Assertion failed: %s\n", message)
    end
end

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
