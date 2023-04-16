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
    do 
        c = 1
    end
    c = c + 1
    inside_scope = 1
end

inside_scope = 0
function print()
    return 1
end

print(inside_scope)

struct GResult
    a: int
    b: str
end

-- function call
function f(a: int, b: str, c: int)
    a = 1
    b = 245
    d = 123
    f(a, b, 1)
end

function g() -> GResult
    return g()
end

k()

f = 123

g = g()
f = f()
x = 1

struct S
    a: int
    b: str
    c: num
    d: S
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

g: f = G()
s: G = S()

g.f()



function perm(n: num) -> num
    if n < 1 then
        return 1
    else
        return n * perm(n - 1)
    end
end

perm("10")
