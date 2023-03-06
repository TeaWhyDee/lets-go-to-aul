
# Aul
Aul is a modified subset of the Lua 5.4 programming language. It is a statically typed language.

## Modifications to the language
### Typing
We take existing Lua types.
- **Number** -
    Integers, floats are all represented as num.
- **String** -
    Strings are sequences of 8-bit values.
- **Table** -
    Tables are dynamically allocated and contain key-value pairs of the specified types.
    They can be used to represent lists or arrays.
- **Function** -
    Functions are represented as variables and can be changed during runtime. [functions](#functions)

Variables of any type can be specified as constant using the `<const>` attribute.
Types of variables can be specified explicitly or inferred from the context.
The type of a variable cannot be modified during runtime.
Uninitialized variables are considered nil.
```lua
var1: num             -- uninitialized variable, value set as nil
var2 <const> = 2      -- type inferred as num
var3 = table[int, str]
```

As a result of these decisions:
- There is no automatic type coercion/conversion in the language.
- There are no **classes**, since they are represented by tables with values of
    different types (class members, methods), they are not implementable using typed tables.

### Functions
- Function parameter types have to be specified, the return type has to be specified.
- Functions can be changed during runtime (unless constant), but their signature has to stay the same.
- Functions can return multiple values, which can be unpacked into variables.
```lua
t: table[num, str]

f = function(n: num) -> num, string
    return 123, "string"
end

f = function(n2: num) -> num, string  -- functions can be changed during runtime
    return n2, nil
end

num_var, str_var = f(1)  -- types inferred and values unpacked
```

### Scopes
Global variables were removed from the specification, all variables are now
local to their scope. As a result of this decision, attempting to access an
unintialized variables results in an error. TODO: maybe allow var == nil ?????

### Left out features
The following features are not necessary for the proof-of-concept version that we are making.
- **Multi-threading**
- **Coroutines**
- **Goto-labels**
