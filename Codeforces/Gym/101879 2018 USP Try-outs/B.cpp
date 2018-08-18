#include <bits/stdc++.h>
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;

int arr[2009];
vector<int> divi;

bool ok(int n, int d) {
    map<int,int> cnt;
    int b = n/d;

    FOR(i, n) {
        cnt[arr[i]%d]++;
    }
    FOR(i, d) {
        if (cnt[i] != b) return false;
    }
    cnt.clear();
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    for (int i = 1; i*i <= n; i++) {
        if (n%i == 0) {
            divi.push_back(i);
            if (n/i != i) divi.push_back(n/i);
        }
    }
    sort(divi.begin(), divi.end());
    for (int i = 0; i < divi.size(); i++) {
        if (divi[i] == 1) continue;

        if (ok(n, divi[i])) { printf("%d\n", divi[i]); return 0; }
    }
    printf("-1\n");
}
