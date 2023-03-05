# Progress


# Syntax
look at [test/syntax.lua](./test/syntax.lua)

## Tokens
look at [./tokens](./tokens)


# Semantics
https://www.lua.org/manual/5.1/manual.html#2.3

## Other
(f(x,y,z)) - Returns only first value or nil.


# Features
## Skipped
- **Coercion** - no automatic value conversion.
- **Threads**
- **Coroutines**

## To Implement
- [ ] Local, Global, Table variables [ref](https://www.lua.org/manual/5.1/manual.html#2.3)
- [ ] Metatables
- [ ] Table Stuff
- [ ] Environments [ref](https://www.lua.org/manual/5.1/manual.html#2.9)

## Under Question
- **Garbage Collection** - ?
- `a,b,c = f(), x`  - like Python.
- `{f()}          ` - Creates list.
- Crazy Table Constructors [ref](https://www.lua.org/manual/5.1/manual.html#2.5.7)
    `a = { [f(1)] = g; "x", "y"; x = 1, f(x), [30] = 23; 45 }`
- ... paremeter 
    `g(a, b, ...)`
- Not including a parameter in f call results in nil value.
    Also why.
    ```lua
        function f(a, b) end
        function r() return 1,2,3 end
        
        f(r(), 10)      -- a=1, b=10
        f(r())          -- a=1, b=2
    ```
