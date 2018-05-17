#include <bits/stdc++.h>
using namespace std;
#define MAXN 20000
#define MAXLOGN 22
#define MAXM (30*MAXN)
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

char dir[10];

int main() {
	int n;
	int cur = MAXN;
	scanf("%d", &n);
	bool ok = true;
	FOR1(i, n) {
		int t;
		scanf("%d %s", &t, dir);
		if (dir[0] == 'W' || dir[0] == 'E') {
			if (cur == 0 || cur == MAXN) ok = false;
		}
		else if (dir[0] == 'N') {
			cur += t;
			if (cur > MAXN) ok = false;
		}
		else if (dir[0] == 'S') {
			cur -= t;
			if (cur < 0) ok = false;
		}
		else ok = false;
	}
	if (cur != MAXN) ok = false;
	if (ok) printf("YES\n");
	else printf("NO\n");
	return 0;
}