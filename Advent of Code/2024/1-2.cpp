#include <bits/stdc++.h>
using namespace std;

inline int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    unordered_map<int, int> left, right;
    int x, y;
    while(scanf(" %d %d", &x, &y) != EOF) {
        left[x]++;
        right[y]++;
    }

    long long ans = 0;
    for (const auto& entry : left) {
        int x = entry.first;
        long long freqLeft = entry.second;
        long long freqRight = right[x];
        ans += x*freqLeft*freqRight;
    }
    printf("%lld\n", ans);
    return 0;
}
