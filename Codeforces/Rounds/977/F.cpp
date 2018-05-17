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
#define EPS 1e-9

map<int, int> last;
int a[MAXN], prv[MAXN], sz[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	int ansi = 1;
	FOR1(i, n) {
		scanf("%d", &a[i]);
		last[a[i]] = i;
		if (last.count(a[i]-1)) {
			prv[i] = last[a[i]-1];
			sz[i] = 1 + sz[prv[i]];
		}
		else {
			prv[i] = -1;
			sz[i] = 1;
		}
		if (sz[ansi] < sz[i]) ansi = i;
	}
	vector<int> ans;
	for(int u = ansi; u != -1; u = prv[u]) {
		ans.pb(u);
	}
	reverse(all(ans));
	printf("%u\n", ans.size());
	for(int u : ans) printf("%d ", u);
	printf("\n");
	return 0;
}