struct A
    x: num
    new(x: num)
        printf("Before assignment: %f %f\n", x, self.x)
        self.x = x
        printf("After assignment: %f %f\n", x, self.x)
    end
end

p1 = A(1)
-- struct Point
--     x: num
--     y: num
-- 
--     function dist(p: Point) -> num
--         return (p.x - self.x) + (p.y - self.y)
--     end
-- end
-- p2 = Point(3, 3)
-- 
-- printf("%f\n", p1.dist(p2))