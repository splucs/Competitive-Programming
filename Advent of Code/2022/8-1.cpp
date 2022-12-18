#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int n, m;
int grid[MAXN][MAXN];

void readInput() {
    n = 0;
    char line[MAXN];
    while(scanf(" %s", line) != EOF) {
        m = strlen(line);
        for(int j = 0; j < m; j++) grid[n][j] = line[j] - '0';
        n++;
    }
}

bool viz[MAXN][MAXN];
int ans = 0;

void go(int si, int sj, int di, int dj) {
    int h = -1;
    for(int i = si, j = sj; i < n && i >= 0 && j < m && j >= 0; i += di, j += dj) {
        if (grid[i][j] > h) {
            if (!viz[i][j]) ans++;
            viz[i][j] = true;
            h = grid[i][j];
        }
    }
}

int main() {
    readInput();
    memset(viz, false, sizeof viz);
    for(int i = 0; i < n; i++) {
        go(i, 0, 0, 1);
        go(i, m-1, 0, -1);
    }
    for(int j = 0; j < m; j++) {
        go(0, j, 1, 0);
        go(n-1, j, -1, 0);
    }
    printf("%d\n", ans);
    return 0;
}