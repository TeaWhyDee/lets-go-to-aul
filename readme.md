# Aul Specification
Aul is a modified subset of the Lua 5.4 programming language. It is a statically typed language.

## Summary
**Removed features**  
- Dynamic features of Lua.
- Table based classes.  
- Global variables.
- Operations with nil.

**The following features are not necessary for the proof-of-concept version that we are making**
- Variables unpacking
- Multi-threading
- Coroutines
- Goto-labels

**Additions**
- Types (type inference) [#typing](#typing)
- Structs (struct, static, new, and self keywords) [#structs](#structs)

**Modifications**
- Functions return one value, no packing or unpacking [#functions](#functions)
- Strongly typed tables

**Features left out due to lack of time**
- Tables


## Typing
We take existing Lua types and make them static and
introduce structs.
- **number** -
    All numbers (integers, floats) are represented as num (internally float).
- **string** -
    Strings are sequences of 8-bit values.
- **bool** - Boolean values.
- **table** -
    Tables are dynamically allocated and contain key-value
    pairs of the specified types. They can be used to
    represent lists or arrays.
- **function** -
    Functions are represented as variables and can be changed during runtime.
- **struct** -
    Structs replace Lua's table based class implementation.
    Structs allow the user to create custom types.

Types of variables can be specified explicitly or inferred from the context.
```lua
a = 10          -- type inferred as num
b = "str"       -- type inferred as str
d: num = "str"  -- error, the type annotation does not match with the expression type
e = a + b       -- error, cannot find `__add(a: num, b: str)`
```

The type of a variable cannot be modified during runtime.
```lua
a = 10     -- type inferred as num
a = "str"  -- error, the type of a is num, so cannot assign `str` to `num`
```

Variables cannot be used before initialization.
```lua
a: num     -- variable declaration 
b = a + 1  -- error, attempt to use an unitialized variable
```

**As a result of these decisions**
- There is no automatic type coercion/conversion in the language.
- There are no **classes**, since they are represented by tables with values of
    different types, instead we intruduce [#structs](#structs).

## Functions
- Function parameter and return types must be specified.
- Functions can be changed during runtime (except constant).
- When calling a function, all parameters must be specified.

```lua
function f(n: num) -> str
  return "string"
end

f(19)  -- returns `"string"`

function f() -> num  -- functions can be changed during runtime
    return 0
end

f(19)  -- error, f awaits no arguments
```

## Structs
In Lua, classes and data structures are created using
tables. This is not possible in Aul, since tables are
statically typed.
We introduce structs as a replacement of this mechanism.

Structs allows the user to intruduce composite types, 
define methods and constructors on those types.
All functions defined in structs are **constant**.
Functions defined in a struct can refer to the instance
with the `self` keyword.
Structs constrictor has a specific name `new`.
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
Global variables were removed from the specification, all variables are now
local to their scope. As a result of this decision, attempting to access an
unintialized variables results in an error.
```lua
x = 0

function f(x: num)
  x = 1  -- modifies the local x passed as an arngument
end

f(x)
printf(x)  -- still 0
```

## Example Program
```lua
struct Point
  _x: num
  _y: num

  new(x: num, y: num)
    self._x = x
    self._y = y
  end

  function get_x() -> num
    return self._x
  end

  function get_y() -> num
    return self._y
  end
end

struct Line
  _point_a: Point
  _point_b: Point
  _length: num

  new(point_a: Point, point_b: Point)
    self._point_a = pointA
    self._point_b = pointB
    self._length = math.sqrt((point_a.get_x()-point_b.get_x())^2 + (point_a.get_y()-point_b.get_y())^2)
  end

  function get_length() -> num
    return self._length
  end
end

print(Line(Point.new(1, 1), Point(5, 5)).get_length()) -- prints 4 * sqrt(2)
```
