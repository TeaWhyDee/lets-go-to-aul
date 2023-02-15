### Type inferencing

```lua
x = 5 -- type: num
y = "abcd" -- type: str
z = x + y -- Error: cannot find `__add(a: num, b: str)`


x = 5
x = "abcd" -- Error: cannot assign `str` to `int`


```

```lua
function from_stdin() -> str
  ...
end

a = int(from_stdin())
b = int(from_stdin())

if a > b
  c = 1
else
  c = "1" -- err: cannot assign `str` to `int`

if a > b
  local c = 1
else
  local c = '1' -- everything is OK
```
