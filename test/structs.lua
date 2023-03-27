struct S end

struct S
    a: int
    b: num
end

struct S
    a: int

    function f() -> num
        a = 1
    end
end

struct G
    a: S
    new()
        a = S()
    end
end