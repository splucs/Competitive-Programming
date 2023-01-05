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

    int window = 14;

    scanf(" %s", input);
    int n = strlen(input);
    for (int i = 0; i < n; i++) {
        up(input[i]);
        if (uniq == window) {
            printf("%d\n", i+1);
            break;
        }
        if (i >= window-1) {
            down(input[i-window+1]);
        }
    }
    return 0;
}