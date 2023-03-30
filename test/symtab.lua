a = 125
c = 1

d = a + c
e = a + t

if a > 124 then
    c = 245
else
    d = 435
end

for i = 1, 10 do
    c = c + 1
    inside_scope = 1
end

inside_scope = 0
function print()
    return 1
end

print(inside_scope)

-- function call
function f(a: int, b: str, c: int) -> None
    a = 1
    b = 245
    f(a, b, 1)
end

function g() -> int
    return g()
end

k()

f = 123

g = g()
f = f()

struct S
    a: int
    b: str
    function f()
        a = 2
    end

    function g()
        c = 3
    end

    function k()
        x = 5
    end
end

g = G()
s = S()