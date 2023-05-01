struct Empty end

struct Point
    x: num
    y: num
end

struct Square
    p1: Point
    p2: Point

    new()
        self.p1 = Point(1, 2)
        self.p2 = Point(3, 4)
    end

    function set_p1(x: num, y: num)
        self.p1.x = x
        self.p1.y = y
    end

    function set_points(p: Point) -> Point
        if random() > 0.5 then
            self.p1 = p
        else
            self.p2 = p
        end
    end

    function perimeter() -> num
        return 2 * (self.p2.x - self.p1.x + self.p2.y - self.p1.y)
    end

    function area() -> num
        return (self.p2.x - self.p1.x) * (self.p2.y - self.p1.y)
    end
end