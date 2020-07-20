class Point
    def initialize(x, y)
        @x, @y = x, y
    end

    def getX() @x end
    def getY() @y end
    
    def setX(x) @x = x end
    def setY(y) @y = y end
    
    def to_s
        "(#{@x}, #{@y})"
    end
end

