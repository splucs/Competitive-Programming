#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
typedef long long ll;

int a[MAXN], inv[MAXN];

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		FOR1(i, n) {
			scanf("%d", &a[i]);
			inv[a[i]] = i;
		}
		int ans = 0;
		FOR1(i, n) {
			if(a[i] != i) {
				int j = inv[i];
				swap(a[i], a[j]);
				inv[a[i]] = i;
				inv[a[j]] = j;
				ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}