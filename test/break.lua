--Check numeric for
printf("\n\n------------------FOR------------------\n")
for i = 1, 10, 1 do
  ff = i * 2
  printf("I = %.3f, FF = %.3f\n", i, ff)
end

check break in for
printf("\n\n------------------FOR WITH BREAK------------------\n")
last_i = 0
for i = 1, 10, 1 do
  last_i = i
  ff = i * 2
  printf("I = %.3f, FF = %.3f\n", i, ff)
  if i == 5 then
    break
  end
end
printf("For with break finished, last I = %.3f\n", last_i)
assert(last_i == 5, "i should be 5")
