#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 100000009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;

int dp[MAXM];
int n, d;

struct frog {
	int w, h, l;
};

bool operator < (frog a, frog b) {
	return a.w < b.w;
}

frog a[MAXN];

int main() {
	while(scanf("%d %d", &n, &d) != EOF) {
		FOR(i, n) {
			scanf("%d %d %d", &a[i].l, &a[i].w, &a[i].h);
		}
		sort(a, a+n);
		int j = n;
		REP(i, MAXM) {
			dp[i] = (i+1 == MAXM ? 0 : dp[i+1]);
			while(j > 0 && a[j-1].w > i) j--;
			if (j == n) dp[i] = 0;
			else 
		}
	}
}