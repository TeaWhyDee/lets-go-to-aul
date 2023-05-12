function assert(condition: bool, message: str)
    if not condition then
        printf("!!!!!! Assertion failed: %s\n", message)
    end
end

a = 1
assert(a == 1, "a should be 1")
assert(a == 2, "This should fail, since a is not 2, but 1")
