function f(a: num) -> num
    return 3
end

a = 3

struct S
    b: num
    function g() -> num
        f(3)
        a = 5
    end
end
