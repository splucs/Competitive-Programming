#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int main() {
    int value[256];
    for(char c = 'a'; c <= 'z'; c++) value[c] = c - 'a' + 1;
    for(char c = 'A'; c <= 'Z'; c++) value[c] = c - 'A' + 27;

    char line[MAXN];
    int ans = 0;
    map<char, int> found;
    for(int group = 1; scanf(" %s", line) != EOF; group++) {
        int n = strlen(line);
        set<char> foundInLine;
        for(int i = 0; i < n; i++) {
            char c = line[i];
            if (foundInLine.count(c)) {
                continue;
            }
            foundInLine.insert(c);
            found[c]++;
        }
        if (group%3 == 0) {
            for (pair<char, int> const& it : found) {
                char c = it.first;
                int cnt = it.second;
                if (cnt == 3) {
                    ans += value[c];
                }
            }
            found.clear();
        }
    }
    printf("%d\n", ans);
    return 0;
}