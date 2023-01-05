#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int max(int x, int y) {
    return x < y ? y : x;
}

char grid[MAXN][MAXN];
int n, m;
vector<string> cmds;

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}

void readInput() {
    for(n = m = 0; gets(grid[m]) && strlen(grid[m]) > 0; m++) {
        n = max(n, strlen(grid[m]));
    }
    for(int y = 0; y < m; y++) {
        for(int x = strlen(grid[y]); x < n; x++) {
            grid[y][x] = ' ';
        }
        grid[y][n] = 0;
    }

    char cmd[10009];
    gets(cmd);
    int len = strlen(cmd);
    string cur;
    for(int i = 0; i < len; i++) {
        if (i > 0 && isNumber(cmd[i-1]) != isNumber(cmd[i])) {
            cmds.push_back(cur);
            cur.clear();
        }
        cur.push_back(cmd[i]);
    }
    cmds.push_back(cur);
}

void print() {
    for(int y = 0; y < m; y++) {
        printf("|%s|\n", grid[y]);
    }
    printf("\n");
}

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
char dc[4] = {'>', 'v', '<', '^'};

int go() {
    int dir = 0;
    int x = 0, y = 0;
    for(; grid[y][x] != '.'; x++);

    for(string cmd : cmds) {
        if (!isNumber(cmd[0])) {
            switch (cmd[0])
            {
            case 'L':
                dir = (dir+3)%4;
                break;
            case 'R':
                dir = (dir+1)%4;
                break;
            default:
                printf("found unknown cmd %s\n", cmd.c_str());
                exit(1);
            }
        }
        else {
            int cnt = atoi(cmd.c_str());
            while(cnt --> 0) {
                int nx = x, ny = y;
                do {
                    nx = (nx + dx[dir] + n)%n;
                    ny = (ny + dy[dir] + m)%m;
                } while (grid[ny][nx] == ' ');

                if (grid[ny][nx] == '#') {
                    break;
                }
                x = nx;
                y = ny;
                grid[y][x] = dc[dir];
            }
        }
    }

    return 1000*(y+1) + 4*(x+1) + dir;
}

int main() {
    readInput();
    int ans = go();
    printf("%d\n", ans);
    return 0;
}