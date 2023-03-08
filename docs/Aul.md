

# Aul Specification
Aul is a modified subset of the Lua 5.4 programming language. It is a statically typed language.

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
    Functions are represented as variables and can be changed during runtime. [#functions](#functions)  
- **struct** -
    Structs replace Lua's table based class implementation.
    Structs allow the user to create custom types. [#structs](#structs)

Variables of any type can be specified as constant using the `const` keyword,
replacing Lua's `<const>` attribute.
Types of variables can be specified explicitly or inferred from the context.
The type of a variable cannot be modified during runtime.
Variables cannot be used before initialization.
```lua
var1: num           -- uninitialized variable
const var2 = 2      -- type inferred as num, value can't be changed
var3: table[int, str] = {}
var4 = var1 + 2     -- ERROR, attempt to use unitialized variable.
```

As a result of these decisions:
- There is no automatic type coercion/conversion in the language.
- There are no **classes**, since they are represented by tables with values of
    different types, instead we intruduce [#structs](#structs)

## Functions
- Function parameter and return types must be specified.
- Functions can be changed during runtime (unless constant), but their signature has to stay the same.
- Functions can return multiple values, which can be unpacked into variables. 
  All values the a function returns are always unpacked,
  whereas in Lua sometimes some values are dropped.
- When calling a function, all parameters must be specified.
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

## Structs
In Lua, classes and data structures are created using
tables. This is not possible in Aul, since tables are
statically typed.
We introduce structs as a replacement of this mechanism.

Structs allows the user to intruduce composite types, 
define methods and constructors on those types.
All functions defined in structs are constant.
Functions defined in a struct can refer to the instance
with the `self` keyword.
```lua
struct S 
    var: num = 0
    function method() -> num
        return self.num
    end
end
```
Static methods can be defined using the `static` keyword.
```lua
    static function new(x: num) -> S
        self.num = x
    end
```

## Scopes
Global variables were removed from the specification, all variables are now
local to their scope. As a result of this decision, attempting to access an
unintialized variables results in an error.

## Example Program
```lua
struct Point
  _x: num
  _y: num

  static function new(x: num, y: num) -> Point
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
  static lines_amount: num = 0 -- create a static variable

  new(point_a: Point, point_b: Point) -- this is the shortest way to describe a constructor
    Line.lines_amount += 1 -- count anount of lines 
    self._point_a = pointA
    self._point_b = pointB
    self._length = math.sqrt((point_a.get_x()-point_b.get_x())^2 + (point_a.get_y()-point_b.get_y())^2)
  end

  function get_length() -> num
    return self._length
  end
end

print(Line(Point.new(1, 1), Point(5, 5)).get_length()) -- prints 4 * sqrt(2)
print(Line.lines_amount) -- prints 1
```
