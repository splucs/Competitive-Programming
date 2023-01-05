#include <bits/stdc++.h>
using namespace std;
#define MAXN 10900
#define MAXH 100009
#define MAXW 7
#define CODE 25

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

map<long long, int> observedRock[5][MAXN];
const int memory = 9, offset = 100;
int rockCycleStart, rockCycleSize, cycleFloors;
int floors[MAXH];

void print(int floor) {
    for(int y = floor-1-offset; y >= floor-memory-offset && y >= 0; y--) {
        printf("|");
        for(int x = 0; x < MAXW; x++) {
            printf("%c", tower[y][x]);
        }
        printf("|\n");
    }
    printf("+-------+\n\n");
}

long long encode(int floor) {
    long long code = 0;
    for(int y = floor-1-offset; y >= floor-memory-offset && y >= 0; y--) {
        for(int x = 0; x < MAXW; x++) {
            code = (code<<1) + (tower[y][x] == '#' ? 1 : 0);
        }
    }
    return code;
}

bool note(int rock, int cmd, int curFloor) {
    long long curCode = encode(curFloor);
    
    int shapeId = rock%5;
    if (observedRock[shapeId][cmd].count(curCode)) {
            rockCycleStart = observedRock[shapeId][cmd][curCode];
            rockCycleSize = rock - rockCycleStart;
            cycleFloors = curFloor - floors[rockCycleStart];
            return true;
    }
    observedRock[shapeId][cmd][curCode] = rock;
    return false;
}

char input[MAXN];

void findCycles() {
    memset(tower, '.', sizeof tower);
    int floor = 0;
    int cmd = 0, cmdMod = strlen(input);
    for(int rock = 0; true; rock++) {   
        int sx = 2;
        int sy = floor + 3;
        vector<string> &shape = shapes[rock%5];
        int rockCmd = cmd;

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
                floors[rock] = floor;
                if (cycleFloors == 0 && note(rock, rockCmd, floor)) {
                    return;
                }
                break;
            }
        }
    }
}

int main() {
    scanf(" %s", input);
    findCycles();
    long long nRocks = 1e12;
    long long nCycles = (nRocks-rockCycleStart)/rockCycleSize;
    long long ans = nCycles*cycleFloors;
    ans += floors[((nRocks-rockCycleStart)%rockCycleSize) + rockCycleStart-1];
    printf("%lld\n", ans);
    return 0;
}