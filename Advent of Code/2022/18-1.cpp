#include <bits/stdc++.h>
using namespace std;

int dx[6] = {0, 0, 1, 0, 0, -1};
int dy[6] = {0, 1, 0, 0, -1, 0};
int dz[6] = {1, 0, 0, -1, 0, 0};

struct point {
    int x, y, z;
    point(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    bool operator < (point o) const {
        if (x != o.x) {
            return x < o.x;
        }
        if (y != o.y) {
            return y < o.y;
        }
        if (z != o.z) {
            return z < o.z;
        }
        return false;
    }
    vector<point> neighbors() {
        vector<point> ans;
        for (int k = 0; k < 6; k++) {
            ans.push_back(point(x+dx[k], y+dy[k], z+dz[k]));
        }
        return ans;
    }
};

int main() {
    int x, y, z;
    set<point> points;
    int ans = 0;
    while(scanf(" %d,%d,%d", &x, &y, &z) != EOF) {
        point p(x, y, z);
        ans += 6;
        points.insert(p);
        for(point q : p.neighbors()) {
            if (points.count(q)) {
                ans -= 2;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}