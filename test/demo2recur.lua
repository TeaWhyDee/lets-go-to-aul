-- check for fibonacci
function fib(n: num) -> num
    if n < 2 then
        return n
    else
        return fib(n - 1) + fib(n - 2)
    end
    return 0
end

n = 10
result = fib(n)
printf("fib(%.1f) = %.3f\n", n, result)
