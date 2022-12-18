#include <bits/stdc++.h>
using namespace std;

set<int> cyclesOfInterest;
int cycle = 0;
int x = 1;
int ans = 0;

void bumpCycle() {
    cycle++;
    if (cyclesOfInterest.count(cycle)) {
        ans += cycle*x;
    }
}

int main() {
    cyclesOfInterest.insert(20);
    cyclesOfInterest.insert(60);
    cyclesOfInterest.insert(100);
    cyclesOfInterest.insert(140);
    cyclesOfInterest.insert(180);
    cyclesOfInterest.insert(220);

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
    printf("%d\n", ans);
    return 0;
}