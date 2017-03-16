#include <cstdio>

struct point_i {
	int x, y;
	point_i() { x = y = 0; }
	point_i(int _x, int _y) : x(_x), y(_y) {}
	bool operator < (point_i other) const {
		if (x != other.x) return x < other.x;
		else return y < other.y;
	}
	bool operator == (point_i other) const {
		return (x == other.x && y == other.y);
	}
};

int insideCircle(point_i p, point_i c, int r) {
	int dx = p.x - c.x, dy = p.y - c.y;
	int Euc = dx * dx + dy * dy, rSq = r * r;
	return Euc < rSq ? 0 : Euc == rSq ? 1 : 2;
} //0 = inside/1 = border/2 = outside