#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
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

ll vx[MAXN], vy[MAXN], x[MAXN], a, b;
map<ll, vector<int> > lines;
int n;

int main() {
	scanf("%d %I64d %I64d", &n, &a, &b);
	FOR1(i, n) {
		scanf("%I64d %I64d %I64d", &x[i], &vx[i], &vy[i]);
		lines[vy[i] - a*vx[i]].pb(i);
	}
	ll ans = 0;
	for(auto & pp : lines) {
		vector<int> & ids = pp.second;

		map<ll, int> reduce;
		for(int i : ids) {
			reduce[vx[i]]++;
		}
		for(int i : ids) {
			ans += ids.size() - reduce[vx[i]];
		}
	}
	printf("%I64d\n", ans);
	return 0;
}