c = 5
d = d * 2

function max(a: num, b: num) -> num
    if a > b then
        return a
    else
        return b
    end
end

max(c, d)

function manhattan(p1: Point, p2: Point) -> num
    return max(p1.x - p2.x, p2.x - p1.x) + max(p1.y - p2.y, p2.y - p1.y)
end

printf("Manhattan: %f\n", manhattan(p1, p2))
