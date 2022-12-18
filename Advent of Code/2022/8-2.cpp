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

inline int abs(int x) {
    return x < 0 ? -x : x;
}

int score[MAXN][MAXN];

void go(int si, int sj, int di, int dj) {
    stack<int> sth, sti, stj;
    for(int i = si, j = sj; i < n && i >= 0 && j < m && j >= 0; i += di, j += dj) {
        int h = grid[i][j];
        int mult = 0;
        while (!sth.empty() && h > sth.top()) {
            sth.pop();
            sti.pop();
            stj.pop();
        }

        int d;
        if (sth.empty()) {
            d = abs(i-si) + abs(j-sj);
        }
        else {
            d = abs(i-sti.top()) + abs(j-stj.top());
        }

        sth.push(h);
        sti.push(i);
        stj.push(j);

        score[i][j] *= d;
    }
}

int main() {
    readInput();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            score[i][j] = 1;
        }
    }

    for(int i = 0; i < n; i++) {
        go(i, 0, 0, 1);
        go(i, m-1, 0, -1);
    }
    for(int j = 0; j < m; j++) {
        go(0, j, 1, 0);
        go(n-1, j, -1, 0);
    }

    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (ans < score[i][j]) {
                ans = score[i][j];
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}