b = 1 -- global

function f()
  b = 5 -- global reassigned
  printf("in func b: %.3f", b)
end

f()
printf("after func: %.3f", b)
