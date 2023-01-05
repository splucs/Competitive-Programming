#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

struct point {
    int x, y;
    point() {}
    point(int _x, int _y) : x(_x), y(_y) {}
    bool operator < (point o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

set<point> elves;

void readInput() {
    char buf[1009];
    int y = 0;
    elves.clear();
    while(scanf(" %s", buf) != EOF) {
        int n = strlen(buf);
        for(int x = 0; x < n; x++) {
            if (buf[x] == '#') {
                elves.insert(point(x, y));
            }
        }
        y++;
    }
}

int dx[4][3] = {
    {-1, 0, 1},
    {-1, 0, 1},
    {-1, -1, -1},
    {1, 1, 1},
};
int dy[4][3] = {
    {-1, -1, -1},
    {1, 1, 1},
    {-1, 0, 1},
    {-1, 0, 1},
};
int sk = 0;

bool goRound() {
    map<point, int> proposedCnt;
    map<point, point> proposed;

    for (point elf : elves) {
        // Check if elf has neighbor
        bool hasNeighbor = false;
        for(int dir = 0; dir < 12; dir++) {
            point neighbor(elf.x + dx[dir/3][dir%3], elf.y + dy[dir/3][dir%3]);
            if (elves.count(neighbor)) {
                hasNeighbor = true;
            }
        }
        if (!hasNeighbor) {
            continue;
        }

        // Check directions starting from sk
        for(int kt = 0; kt < 4; kt++) {
            int k = (sk + kt)%4;
            bool hasElf = false;

            for(int dir = 0; dir < 3; dir++) {
                point proposal(elf.x + dx[k][dir], elf.y + dy[k][dir]);
                if (elves.count(proposal)) {
                    hasElf = true;
                    break;
                }
            }

            if (!hasElf) {
                point proposal(elf.x + dx[k][1], elf.y + dy[k][1]);
                proposed[elf] = proposal;
                proposedCnt[proposal]++;
                break;
            }
        }
    }

    set<point> newElves;
    bool moved = false;
    for(point elf : elves) {
        if (!proposed.count(elf)) {
            newElves.insert(elf);
            continue;
        }

        point proposal = proposed[elf];
        if (proposedCnt[proposal] > 1) {
            newElves.insert(elf);
        }
        else {
            newElves.insert(proposal);
            moved = true;
        }
    }

    elves = newElves;
    sk++;
    return moved;
}

char grid[109][109];
void print(int sx, int tx, int sy, int ty) {
    for (int y = sy; y <= ty; y++) {
        for (int x = sx; x <= tx; x++) {
            grid[y-sy][x-sx] = '.';
        }
        grid[y-sx][tx+1-sx] = 0;
    }
    for (point elf : elves) {
        grid[elf.y-sy][elf.x-sx] = '#';
    }
    for (int y = sy; y <= ty; y++) {
        printf("|%s|\n", grid[y-sy]);
    }
    printf("\n");
}

int main() {
    readInput();
    //print(-3, 10, -2, 9);
    for(int r = 1; true; r++) {
        if (!goRound()) {
        //printf("== End of Round %d ==\n", r);
        //print(-3, 10, -2, 9);
            printf("%d\n", r);
            break;
        }
        //printf("== End of Round %d ==\n", r);
        //print(-3, 10, -2, 9);
    }
    return 0;
}