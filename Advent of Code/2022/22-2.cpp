#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int max(int x, int y) {
    return x < y ? y : x;
}

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
char dc[4] = {'>', 'v', '<', '^'};

char grid[MAXN][MAXN];
int n, m, faceSize;
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

    faceSize = n > 100 ? 50 : 4;

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

struct direction {
    vector<int> v;
    direction() {}
    direction(int a, int b, int c) {
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
    }
    direction(vector<int> _v) : v(_v) {}

    int& operator[](int i) {
        return v[i];
    }
    bool operator<(direction o) const {
        for (int i = 0; i < 3; i++) {
            if (v[i] != o.v[i]) {
                return v[i] < o.v[i];
            }
        }
        return false;
    }
    bool operator!=(direction o) const {
        for (int i = 0; i < 3; i++) {
            if (v[i] != o.v[i]) {
                return true;
            }
        }
        return false;
    }
    direction operator~() {
        vector<int> nv;
        for (int vi : v) {
            nv.push_back(-vi);
        }
        return direction(nv);
    }
};

struct face {
    direction n, x, y;
    int ox, oy;
    face() {}
    face(direction _n, direction _x, direction _y, int _ox, int _oy) : n(_n), x(_x), y(_y), ox(_ox), oy(_oy) {}

    face move(int dx, int dy) {
        if (dx > 0) {
            return face(x, ~n, y, ox+1, oy);
        }
        if (dx < 0) {
            return face(~x, n, y, ox-1, oy);
        }
        if (dy > 0) {
            return face(y, x, ~n, ox, oy+1);
        }
        if (dy < 0) {
            return face(~y, x, n, ox, oy-1);
        }
        return *this;
    }
};

direction initN(0, 0, -1), initX(1, 0, 0), initY(0, 1, 0);
map<direction, face> faces;

void buildFaces(int sx, int sy) {
    int ox = sx/faceSize;
    int oy = sy/faceSize;
    face curFace(initN, initX, initY, ox, oy);

    queue<direction> q;
    faces[curFace.n] = curFace;
    q.push(curFace.n);
    while(!q.empty()) {
        curFace = faces[q.front()];
        q.pop();
        for (int dir = 0; dir < 4; dir++) {
            int x = (curFace.ox+dx[dir])*faceSize;
            int y = (curFace.oy+dy[dir])*faceSize;
            if (x < 0 || y < 0 || x >= n || y >= m) {
                continue;
            }
            if (grid[y][x] == ' ') {
                continue;
            }

            face newFace = curFace.move(dx[dir], dy[dir]);
            if (faces.count(newFace.n)) {
                continue;
            }
            faces[newFace.n] = newFace;
            q.push(newFace.n);
        }
    }
}

void rotateFace(face target, face curFace, int &x, int &y, int &dir) {
    int ix = (x+faceSize)%faceSize;
    int iy = (y+faceSize)%faceSize;

    if (target.n != curFace.n) {
        printf("cannot rotate unmatching normal vectors\n");
        exit(1);
    }

    while(target.x != curFace.x) {
        direction tmp = curFace.y;
        curFace.y = curFace.x;
        curFace.x = ~tmp;

        int niy = ix;
        int nix = faceSize-iy-1;
        ix = nix;
        iy = niy;
        dir = (dir+1)%4;
    }

    x = target.ox*faceSize + ix;
    y = target.oy*faceSize + iy;
}

void print() {
    for(int y = 0; y < m; y++) {
        printf("|%s|\n", grid[y]);
    }
    printf("\n");
}

int go() {
    int dir = 0;
    int x = 0, y = 0;
    for(; grid[y][x] != '.'; x++);

    buildFaces(x, y);
    face curFace(initN, initX, initY, x/faceSize, y/faceSize);

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
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                int ndir = dir;
                face targetFace = curFace;

                // check if changed faces
                if (nx < 0 || x/faceSize != nx/faceSize || ny < 0 || y/faceSize != ny/faceSize) {
                    face newFace = curFace.move(dx[dir], dy[dir]);
                    targetFace = faces[newFace.n];
                    // newFace and targetFace will have the same normal but different x and y vectors
                    // we have to rotate newFace until they match and update nx and ny accordingly
                    rotateFace(targetFace, newFace, nx, ny, ndir);
                }

                if (grid[ny][nx] == '#') {
                    break;
                }
                curFace = targetFace;
                grid[y][x] = dc[dir];
                x = nx;
                y = ny;
                grid[y][x] = 'O';
                dir = ndir;
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