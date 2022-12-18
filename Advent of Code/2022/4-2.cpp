#include <bits/stdc++.h>
using namespace std;

int main() {
    int ans = 0;
    int l1, r1, l2, r2;
    while(scanf(" %d-%d,%d-%d", &l1, &r1, &l2, &r2) != EOF) {
        if (!(r2 < l1 || r1 < l2)) {
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;   
}