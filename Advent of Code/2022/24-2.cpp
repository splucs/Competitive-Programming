#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 129
#define MAXT 609

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x%y);
}

char grid[MAXT][MAXN][MAXN];
int n, m, T;

void print(int t) {
    for(int y = 0; y < m; y++) {
        grid[t][y][n] = 0;
        printf("%s\n", grid[t][y]);
    }
    printf("\n");
}

void printAll() {
    for (int t = 0; t < T; t++) {
        printf("Minute %d:\n", t);
        print(t);
    }
}

void readInput() {
    memset(grid, '.', sizeof grid);

    for(m = 0; scanf(" %s", grid[0][m]) != EOF; m++);
    n = strlen(grid[0][0]);

    int modx = n-2;
    int mody = m-2;
    T = modx*mody/gcd(modx, mody);

    for(int y = 0; y < m; y++) {
        for(int x = 0; x < n; x++) {
            int dx, dy;
            bool block = true;

            switch (grid[0][y][x])
            {
            case '#':
                dx = 0; dy = 0;
                break;
            case '>':
                dx = 1; dy = 0;
                break;
            case 'v':
                dx = 0; dy = 1;
                break;
            case '<':
                dx = -1; dy = 0;
                break;
            case '^':
                dx = 0; dy = -1;
                break;
            default:
                block = false;
                break;
            }

            if (!block) {
                continue;
            }

            int ix = x, iy = y;
            for (int t = 0; t < T; t++) {
                grid[t][iy][ix] = '#';
                if (dy != 0) {
                    iy = (iy-1+dy+mody)%mody + 1;
                }
                if (dx != 0) {
                    ix = (ix-1+dx+modx)%modx + 1;
                }
            }
        }
    }
}

int dist[3][MAXT][MAXN][MAXN];

int bfs(int sx, int sy, int tx, int ty) {
    memset(dist, INF, sizeof dist);
    queue<int> qs;
    queue<int> qt;
    queue<int> qy;
    queue<int> qx;
    int dx[5] = {0, 1, 0, -1, 0};
    int dy[5] = {1, 0, -1, 0, 0};

    dist[0][0][sy][sx] = 0;
    qs.push(0);
    qt.push(0);
    qy.push(sy);
    qx.push(sx);

    int ans = INF;

    while(!qt.empty()) {
        int s = qs.front(); qs.pop();
        int t = qt.front(); qt.pop();
        int y = qy.front(); qy.pop();
        int x = qx.front(); qx.pop();

        if (s == 2 && x == tx && y == ty) {
            ans = min(ans, dist[s][t][y][x]);
        }

        for(int dir = 0; dir < 5; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            int nt = (t+1)%T;
            int ns = s;
            if (s == 0 && x == tx && y == ty) {
                ns = 1;
            }
            else if (s == 1 && x == sx && y == sy) {
                ns = 2;
            }
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            if (grid[nt][ny][nx] == '#' || dist[ns][nt][ny][nx] < INF) {
                continue;
            }
            dist[ns][nt][ny][nx] = 1 + dist[s][t][y][x];
            qs.push(ns);
            qt.push(nt);
            qy.push(ny);
            qx.push(nx);
        }
    }

    return ans;
}

int main() {
    readInput();
    int ans = bfs(1, 0, n-2, m-1);
    printf("%d\n", ans);
    return 0;
}