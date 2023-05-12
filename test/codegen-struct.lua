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