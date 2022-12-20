#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

char grid[MAXN][MAXN];
int ans = 0;

void print() {
    for (int y = 0; y < 13; y++) {
        for (int x = 493; x < 504; x++) {
            printf("%c", grid[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

struct point {
    int x, y;
    point(int _x, int _y) : x(_x), y(_y) {}
    bool operator != (point o) {
        return x != o.x || y != o.y;
    }
};

int unitary(int x) {
    if (x < -1) return -1;
    if (x > 1) return 1;
    return x;
}

bool deposit(int x, int y) {
    if (x < 0 || y < 0 || x >= MAXN || y >= MAXN) {
        return false;
    }
    if (grid[x][y] == '#' || grid[x][y] == 'o') {
        return true;
    }
    if (grid[x][y] == '~') {
        return false;
    }
    if (deposit(x, y+1) && deposit(x-1, y+1) && deposit(x+1, y+1)) {
        ans++;
        grid[x][y] = 'o';
        return true;
    }
    else {
        grid[x][y] = '~';
        return false;
    }
}

void processLine(vector<point > &points) {
    if (points.empty()) {
        return;
    }
    point cur = points[0];
    grid[cur.x][cur.y] = '#';
    for (point target : points) {
        int dx = unitary(target.x - cur.x);
        int dy = unitary(target.y - cur.y);
        do {
            cur.x += dx;
            cur.y += dy;
            grid[cur.x][cur.y] = '#';
        } while(cur != target);
    }
}


void readInput() {
    char buf[MAXN];
    memset(grid, '.', sizeof grid);
    char word[MAXN];
    vector<point> points;
    bool newline = true;
    while(scanf(" %s", word) != EOF) {
        if (!strcmp(word, "->")) {
            newline = false;
        }
        else {
            if (newline) {
                processLine(points);
                points.clear();
            }
            newline = true;
            int x, y;
            sscanf(word, " %d,%d ", &x, &y);
            points.push_back(point(x, y));
        }
    }
    processLine(points);
}

int main () {
    readInput();
    deposit(500, 0);
    printf("%d\n", ans);
    return 0;
}