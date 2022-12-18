#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF 0x3f3f3f3f3f3f

int abs(int x) {
    return x < 0 ? -x : x;
}

int max(int x, int y) {
    return x < y ? y : x;
}

struct point {
    int x, y;
    point(int _x, int _y) : x(_x), y(_y) {}
    bool operator <(const point &o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

int dist(point a, point b) {
    return max(abs(a.x-b.x), abs(a.y-b.y));
}

point head(0,0), tail(0,0);
set<point> viz;

void move(point &a, char dir) {
    switch (dir)
    {
    case 'R':
        a.x++;
        break;
    case 'L':
        a.x--;
        break;
    case 'U':
        a.y++;
        break;
    case 'D':
        a.y--;
        break;
    
    default:
        break;
    }
}

void follow() {
    if (dist(head, tail) < 2) {
        return;
    }
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    point bestCand(head.x+1, head.y);
    for (int k = 0; k < 4; k++) {
        point cand(head.x+dx[k], head.y+dy[k]);
        if (dist(tail, cand) < dist(tail, bestCand)) {
            bestCand = cand;
        }
    }
    tail = bestCand;
    viz.insert(tail);
}

void print() {
    const int n = 5, m = 6;
    char grid[n][m+1];
    memset(&grid, '.', sizeof grid);
    grid[tail.y][tail.x] = 'T';
    grid[head.y][head.x] = 'H';
    for(int i = n-1; i >= 0; i--) {
        grid[i][m] = 0;
        printf("%s\n", grid[i]);
    }
    printf("\n");
}

int main() {
    viz.insert(tail);
    char dir;
    int cnt;
    while(scanf(" %c %d", &dir, &cnt) != EOF) {
        while(cnt --> 0) {
            move(head, dir);
            follow();
        }
    }
    printf("%d\n", (int)viz.size());
    return 0;
}