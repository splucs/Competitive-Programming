#include <bits/stdc++.h>
using namespace std;

inline int abs(int x) {
    return x < 0 ? -x : x;
}

vector<unordered_map<char, int>> go;

void buildStateMachine() {
    go.assign(13, unordered_map<char, int>());
    for (int i = 0; i < (int)go.size(); i++) {
        go[i]['m'] = 1;
    }
    go[1]['u'] = 2;
    go[2]['l'] = 3;
    go[3]['('] = 4;
    for (int i = 0; i < 10; i++) {
        go[4]['0'+i] = 5;
        go[5]['0'+i] = 6;
        go[6]['0'+i] = 7;
    }
    go[5][','] = 8;
    go[6][','] = 8;
    go[7][','] = 8;
    for (int i = 0; i < 10; i++) {
        go[8]['0'+i] = 9;
        go[9]['0'+i] = 10;
        go[10]['0'+i] = 11;
    }
    go[9][')'] = 12;
    go[10][')'] = 12;
    go[11][')'] = 12;
}

int process(char s[]) {
    int u = 0, x, y;
    int ans = 0, n = strlen(s);
    for (int i = 0; i < n; i++) {
        char c = s[i];
        u = go[u][c];
        if (u == 4) {
            x = y = 0;
        }
        if (u == 5 || u == 6 || u == 7) {
            x = 10*x + c - '0';
        }
        if (u == 9 || u == 10 || u == 11) {
            y = 10*y + c - '0';
        }
        if (u == 12) {
            ans += x*y;
        }
    }
    return ans;
}

char input[100009];

void readInput() {
    int i = 0;
    char c;
    while((c = getchar()) != EOF) {
        input[i++] = c;
    }
    input[i] = 0;
}

int main() {
    buildStateMachine();
    readInput();
    printf("%d\n", process(input));
    return 0;
}
