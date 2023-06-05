struct point {
	int x, y;
	point() { x = y = 0; }
	point(int _x, int _y) : x(_x), y(_y) {}

	point operator -(point other) const {
		return point(x - other.x, y - other.y);
	}
};

int inline cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool inline collinear(point p, point q, point r) {
	return cross(p-q, r-p) == 0;
}

class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int n = coordinates.size();
        point p1(coordinates[0][0], coordinates[0][1]);
        point p2(coordinates[1][0], coordinates[1][1]);
        for (int i = 2; i < n; i++) {
            point p3(coordinates[i][0], coordinates[i][1]);
            if (!collinear(p1, p2, p3)) {
                return false;
            }
        }
        return true;
    }
};
