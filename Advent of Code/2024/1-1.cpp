#include <bits/stdc++.h>
using namespace std;

inline int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    vector<int> left, right;
    int x, y;
    while(scanf(" %d %d", &x, &y) != EOF) {
        left.push_back(x);
        right.push_back(y);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    int n = left.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += abs(right[i] - left[i]);
    }
    printf("%d\n", ans);
    return 0;
}
