#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXH 100009
#define MAXW 7

vector<string> shapes[5] = {
    {
        "@@@@",
    },
    {
        ".@.",
        "@@@",
        ".@.",
    },
    {
        "@@@",
        "..@",
        "..@",
    },
    {
        "@",
        "@",
        "@",
        "@",
    },
    {
        "@@",
        "@@",
    },
};

char tower[MAXH][MAXW];

bool fits(vector<string> &shape, int sx, int sy) {
    if (sx < 0 || sy < 0) {
        return false;
    }
    int h = shape.size();
    int w = shape[0].size();
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            int nx = x + sx;
            int ny = y + sy;
            if (nx >= MAXW || ny >= MAXH) {
                return false;
            }
            if (tower[ny][nx] == '#' && shape[y][x] == '@') {
                return false;
            }
        }
    }
    return true;
}

void rest(vector<string> &shape, int sx, int sy) {
    int h = shape.size();
    int w = shape[0].size();
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            int nx = x + sx;
            int ny = y + sy;
            if (shape[y][x] == '@') {
                tower[ny][nx] = '#';
            }
        }
    }
}

char buf[MAXH][MAXW+1];
void print(vector<string> &shape, int sx, int sy) {
    int h = shape.size();
    int w = shape[0].size();
    for(int y = 0; y < sy+h; y++) {
        for(int x = 0; x < MAXW; x++) {
            buf[y][x] = tower[y][x];
        }
        buf[y][MAXW] = 0;
    }
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            int nx = x + sx;
            int ny = y + sy;
            if (shape[y][x] == '@' && buf[ny][nx] == '.') {
                buf[ny][nx] = '@';
            }
        }
    }
    for(int y = sy+h-1; y >= 0; y--) {
        printf("|%s|\n", buf[y]);
    }
    printf("+-------+\n\n");
}

char input[MAXN];

int main() {
    memset(tower, '.', sizeof tower);
    int floor = 0;
    scanf(" %s", input);
    int cmd = 0, cmdMod = strlen(input);
    for(int rock = 0; rock < 2022; rock++) {   
        int sx = 2;
        int sy = floor + 3;
        vector<string> &shape = shapes[rock%5];

        while(true) {
            char c = input[cmd];
            cmd=(cmd+1)%cmdMod;
            if (c == '>') {
                sx++;
                if (!fits(shape, sx, sy)) {
                    sx--;
                }
            }
            else {
                sx--;
                if (!fits(shape, sx, sy)) {
                    sx++;
                }
            }

            sy--;
            if (!fits(shape, sx, sy)) {
                sy++;
                rest(shape, sx, sy);
                floor = max(floor, sy+(int)shape.size());
                break;
            }
        }
    }
    printf("%d\n", floor);
    return 0;
}