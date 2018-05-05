#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int solve(vector<ii> & ans, vector<int> d) {
	int n = d.size();
	if (n == 0) return 1;
	if (n == 1) {
		FOR1(u, d[0]+1) {
			FOR1(v, u-1) ans.pb({u, v});
		}
		return d[0] + 1;
	}
	vector<int> nd;
	for(int i = 1; i < n-1; i++) {
		nd.pb(d[i] - d[0]);
	}
	int cnt = solve(ans, nd);
	cnt += d[n-1] - d[n-2];
	for(int u = cnt+1; u <= cnt+d[0]; u++) {
		FOR1(v, u-1) {
			ans.pb({u, v});
		}
	}
	return cnt + d[0];
}

int main() {
	int n;
	scanf("%d", &n);
	vector<int> d(n);
	FOR(i, n) {
		scanf("%d", &d[i]);
	}
	vector<ii> ans;
	int cnt = solve(ans, d);
	printf("%u\n", ans.size());
	for(auto pp : ans) {
		printf("%d %d\n", pp.first, pp.second);
	}
	return 0;
}