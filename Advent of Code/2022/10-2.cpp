#include <bits/stdc++.h>
using namespace std;

int abs(int x) {
    return x < 0 ? -x : x;
}

int cycle = 0;
int x = 1;
char image[6][41];

void bumpCycle() {
    int i = cycle%40;
    int j = cycle/40;
    if (j > 5) {
        return;
    }
    cycle++;
    if (abs(i-x) <= 1) {
        image[j][i] = '#';
    }
    else {
        image[j][i] = '.';
    }
}

int main() {
    char cmd[10];
    while(scanf(" %s", cmd) != EOF) {
        if(!strcmp(cmd, "noop")) {
            bumpCycle();
        }
        if(!strcmp(cmd, "addx")) {
            bumpCycle();
            bumpCycle();
            int dx;
            scanf(" %d", &dx);
            x += dx;
        }
    }
    while(cycle < 220) bumpCycle(); 
    for (int j = 0; j < 6; j++) {
        image[j][40] = 0;
        printf("%s\n", image[j]);
    }
    return 0;
}