#include <bits/stdc++.h>
#define MAXN 100009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int n, a[MAXN];

int main() {
	scanf("%d", &n);
	a[0] = 0;
	FOR1(i, n) {
		scanf("%d", &a[i]);
		a[i] += a[i-1];
	}
	FOR1(s, n) {
		int ans = 0;
		int i = s, t = 0;
		while(i <= n) {
			t++;
			int j = i + 3*t;
			if (j > n) j = n+1;
			ans += max(0, a[j-1]-a[i-1]);
			i = j;
		}
		printf("%d\n", ans);
	}
	return 0;
}