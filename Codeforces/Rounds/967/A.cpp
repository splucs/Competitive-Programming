#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int n, t[MAXN], s;

int main() {
	int ans = -1;
	scanf("%d %d", &n, &s);
	FOR(i, n) {
		int h, m;
		scanf("%d %d", &h, &m);
		t[i] = m + h*60;
	}
	FOR(i, n+1) {
		int l, r;
		if (i == 0) l = 0;
		else l = t[i-1] + 1 + s;
		if (i == n) r = INF;
		else r = t[i] - s - 1;
		if (r >= l && ans == -1) ans = l; 
	}
	printf("%d %d\n", ans/60, ans%60);
	return 0;
}