#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int n, m;
int grid[MAXN][MAXN];
int ti, tj;

void readInput() {
    n = 0;
    char line[MAXN];
    while(scanf(" %s", line) != EOF) {
        int i = n++;
        m = strlen(line);
        for (int j = 0; j < m; j++) {
            if (line[j] == 'S') {
                grid[i][j] = 0;
            }
            else if (line[j] == 'E') {
                ti = i;
                tj = j;
                grid[i][j] = 'z'-'a';
            }
            else {
                grid[i][j] = line[j]-'a';
            }
        }
    }
}

int dist[MAXN][MAXN];
bool viz[MAXN][MAXN];
int di[4] = {0, -1, 0, 1};
int dj[4] = {-1, 0, 1, 0};

bool isValid(int i, int j) {
    return i >= 0 && j >= 0 && i < n && j < m;
}

int bfs() {
    queue<int> qi, qj;
    memset(viz, false, sizeof viz);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                dist[i][j] = 0;
                viz[i][j] = true;
                qi.push(i);
                qj.push(j);
            }
        }
    }
    while (!qi.empty()) {
        int i = qi.front();
        qi.pop();
        int j = qj.front();
        qj.pop();

        for (int k = 0; k < 4; k++) {
            int ni = i + di[k];
            int nj = j + dj[k];
            if (!isValid(ni, nj)) {
                continue;
            }
            if (grid[ni][nj] > grid[i][j]+1) {
                continue;
            }
            if (viz[ni][nj]) {
                continue;
            }
            viz[ni][nj] = true;
            dist[ni][nj] = dist[i][j] + 1;
            qi.push(ni);
            qj.push(nj);
        }
    }
    return dist[ti][tj];
}

int main() {
    readInput();
    printf("%d\n", bfs());
    return 0;
}