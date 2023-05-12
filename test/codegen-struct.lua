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

printf("%f\n", p2.dist(p1))