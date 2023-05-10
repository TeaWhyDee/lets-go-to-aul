struct Point
    x: num
    y: num

    function dist(p: Point) -> num
        return (p.x - self.x) + (p.y - self.y)
    end
end

p1 = Point(1, 1)
-- p2 = Point(3, 3)
-- 
-- printf("%f\n", p1.dist(p2))