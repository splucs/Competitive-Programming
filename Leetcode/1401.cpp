class Solution {
private:
    bool rectangleContainsZero(int x1, int y1, int x2, int y2) {
        return x1*x2 <= 0 && y1*y2 <= 0;
    }
    bool circleContainsZero(int radius, int xCenter, int yCenter) {
        return xCenter*xCenter + yCenter*yCenter <= radius*radius;
    }
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        x1 -= xCenter, x2 -= xCenter;
        y1 -= yCenter, y2 -= yCenter;
        // Minkowski sum
        return rectangleContainsZero(x1-radius, y1, x2+radius, y2)
            || rectangleContainsZero(x1, y1-radius, x2, y2+radius)
            || circleContainsZero(radius, x1, y1)
            || circleContainsZero(radius, x1, y2)
            || circleContainsZero(radius, x2, y1)
            || circleContainsZero(radius, x2, y2);
    }
};
