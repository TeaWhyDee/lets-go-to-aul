# Aul Specification
Aul is a modified subset of the Lua 5.4 programming language. It is a statically typed language.

## Summary
**Removed features**  
- Dynamic features of Lua.
- Table based classes.  
- Global variables.
- Operations with nil.

**Additions**
- Types, type inference. [#typing](#Typing)
- Structs (struct, new, and self keywords). [#structs](#Structs)

**Modifications**
- Functions return one value, no packing or unpacking. [#functions](#Functions)
- Tables and function are strongly typed.

**Features missing in our demo due to lack of time**
- Variables unpacking.
- Multi-threading.
- Coroutines.
- Goto-labels.
- `const` keyword.
- Tables.
- Runtime modifiable functions.
- Nested structs.

## Typing
We take existing Lua types and make them static and
introduce structs.
- **num** - All numbers are represented as num (internally float).
- **str** - Strings are sequences of 8-bit values.
- **bool** - Boolean values.
- **table** - Tables are dynamically allocated and contain key-value pairs of the specified types. They can be used to represent lists or arrays.
- **function** - Functions are represented as variables and can be changed during runtime.
- **struct** - Structs replace Lua's table based class implementation. Structs allow the user to create custom types.

Types of variables can be specified explicitly or inferred from the context.
```lua
a = 10          -- type inferred as num
b = "str"       -- type inferred as str
d: num = "str"  -- Error, the type annotation does not match with the expression type
err = a + b     -- Error
```

The type of a variable cannot be modified during runtime.
```lua
a = 10     -- type inferred as num
a = "str"  -- Error, the type of a is num, so cannot assign `str` to `num`
```

Regular variables must be initialized.
```lua
a: num     -- error
b: num = 1
```

**As a result of these decisions**
- There is no automatic type coercion/conversion in the language.
- There are no **classes**, since they are represented by tables with values of different types, instead we intruduce [#structs](#Structs).

## Functions
- Function parameter and return types must be specified.
- Functions can be changed during runtime (their signature cannot change).
- When calling a function, all parameters must be specified.

```lua
function f(n: num) -> str
  return "first"
end

function f2(n: num) -> str  -- functions can be changed during runtime
    return "second"
end

function f3() -> str  -- functions can be changed during runtime
    return "third"
end

f(19)  -- returns `first`

f = f2

f(19)  -- returns `seocnd`

f = f3 -- error, different function signature
```

## Structs
In Lua, classes and data structures are created using tables. This is not possible in Aul, since tables are statically typed. We introduce structs as a replacement of this mechanism.

Structs allows the user to intruduce composite types,  define methods and constructors on those types. All functions defined in structs are **constant**. Functions defined in a struct can refer to the instance with the `self` keyword. Structs constrictor has a specific name `new`.
```lua
struct S 
  var: num 
  new() var = 0 end
  function get_var() -> num
    return self.var
  end
end
```

## Scopes
Global variables were removed from the specification, all variables are now local to their scope. As a result of this decision, attempting to access an unintialized variables results in an error.
```lua
a = "global_a"
x = "global_x"

function f(x: string)
    a = "update_global_a"
    x = "update_param_x"  -- modifies the local x passed as an arngument
    loc = "local_var"
end -- loc no longer exists after exiting scope

f(x)
printf(a)  -- "update_global_a"
printf(x)  -- "global_x"
```

## Example Program
```lua
struct Point
    x: num
    y: num

    new(x: num, y: num)
        self.x = x
        self.y = y
    end

    function dist(p: Point) -> num
        return ((p.x - self.x) ^ 2 + (p.y - self.y) ^ 2) ^ 0.5
    end
end
p1 = Point(5, 5)
p2 = Point(10, 10)

function max(a: num, b: num) -> num
    if a > b then
        return a
    else
        return b
    end
end

function manhattan(p1: Point, p2: Point) -> num
    return max(p1.x - p2.x, p2.x - p1.x) + max(p1.y - p2.y, p2.y - p1.y)
end

printf("Euclidian: %f\n", p1.dist(p2))
printf("Manhattan: %f\n", manhattan(p1, p2))
```
