#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

char input[MAXN];
int cnt[256];
int uniq;

void up(char c) {
    cnt[c]++;
    if (cnt[c] == 1) {
        uniq++;
    }
    if (cnt[c] == 2) {
        uniq--;
    }
}

void down(char c) {
    cnt[c]--;
    if (cnt[c] == 1) {
        uniq++;
    }
    if (cnt[c] == 0) {
        uniq--;
    }
}

int main() {
    uniq = 0;
    memset(&cnt, 0, sizeof cnt);

    scanf(" %s", input);
    up(input[0]);
    up(input[1]);
    up(input[2]);
    int n = strlen(input);
    for (int i = 3; i < n; i++) {
        up(input[i]);
        if (uniq == 4) {
            printf("%d\n", i+1);
            break;
        }
        down(input[i-3]);
    }
    return 0;
}