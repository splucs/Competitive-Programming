#include <bits/stdc++.h>
using namespace std;
#define MAXX 30
#define MINX -1

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
    bool valid() {
        if (x < MINX || x > MAXX) {
            return false;
        }
        if (y < MINX || y > MAXX) {
            return false;
        }
        if (z < MINX || z > MAXX) {
            return false;
        }
        return true;
    }
};

set<point> rock, water;

void dfs(point p) {
    if (!p.valid()) {
        return;
    }
    if (rock.count(p) || water.count(p)) {
        return;
    }
    water.insert(p);
    for (point q : p.neighbors()) {
        dfs(q);
    }
}

int main() {
    int x, y, z;
    while(scanf(" %d,%d,%d", &x, &y, &z) != EOF) {
        point p(x, y, z);
        rock.insert(p);
        if (x <= MINX || x >= MAXX || y <= MINX || y >= MAXX || z <= MINX || z >= MAXX) {
            printf("invalid point at input (%d,%d,%d)\n", x, y, z);
            exit(1);
        }
    }
    for (int x = MINX; x <= MAXX; x++) {
        for(int y = MINX; y <= MAXX; y++) {
            dfs(point(x, y, MINX));
            dfs(point(x, y, MAXX));
            dfs(point(x, MINX, y));
            dfs(point(x, MAXX, y));
            dfs(point(MINX, x, y));
            dfs(point(MAXX, x, y));
        }
    }
    int ans = 0;
    for (point p : rock) {
        for (point q : p.neighbors()) {
            if (water.count(q)) {
                ans++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}