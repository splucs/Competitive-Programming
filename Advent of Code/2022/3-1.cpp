#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int main() {
    int value[256];
    for(char c = 'a'; c <= 'z'; c++) value[c] = c - 'a' + 1;
    for(char c = 'A'; c <= 'Z'; c++) value[c] = c - 'A' + 27;

    char line[MAXN];
    int ans = 0;
    while(scanf(" %s", line) != EOF) {
        int n = strlen(line);
        set<char> found;
        for(int i = 0; i < n/2; i++) {
            char c = line[i];
            found.insert(c);
        }
        for(int i = n/2; i < n; i++) {
            char c = line[i];
            if (found.count(c)) {
                found.erase(c);
                ans += value[c];
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}