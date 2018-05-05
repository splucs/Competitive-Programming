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

void find(int y, vector<int> & pos, vector<int> & ans) {
	auto it = upper_bound(all(pos), y);
	if (it != pos.end()) {
		ans.pb(*it);
	}
	if (it != pos.begin()) {
		it--;
		ans.pb(*it);
	}
}

int ceil(int a, int b) {
	if (a % b == 0) return a / b;
	return a / b + 1;
}

vector<int> stairs, ele;

int main() {
	int n, m, cl, ce, v;
	scanf("%d %d %d %d %d", &n, &m, &cl, &ce, &v);
	FOR(i, cl) {
		int x;
		scanf("%d", &x);
		stairs.pb(x);
	}
	FOR(i, ce) {
		int x;
		scanf("%d", &x);
		ele.pb(x);
	}
	int q;
	scanf("%d", &q);
	FOR(j, q) {
		int x1, x2, y1, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		int ans = INF;
		vector<int> s, e;
		find(y1, stairs, s);
		find(y2, stairs, s);
		find(y1, ele, e);
		find(y2, ele, e);
		for(int y : e) {
			int dy = abs(y1-y) + abs(y2-y);
			int dx = ceil(abs(x1-x2), v);
			ans = min(ans, dx+dy);
		}
		for(int y : s) {
			int dy = abs(y1-y) + abs(y2-y);
			int dx = ceil(abs(x1-x2), 1);
			ans = min(ans, dx+dy);
		}
		if (x1 == x2) ans = min(ans, abs(y1-y2));
		printf("%d\n", ans);
	}
	return 0;
}
