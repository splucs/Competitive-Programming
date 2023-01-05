#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define MAXM 309
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pf push_front
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

int a[MAXN], b[MAXN];

int main() {
	int n, m;
	set<int> sa, sb;
	scanf("%d %d", &n, &m);
	FOR(i, n) {
		scanf("%d", &a[i]);
		sa.insert(a[i]);
	}
	bool ok = true;
	FOR(i, m) {
		scanf("%d", &b[i]);
		if (sa.count(b[i])) {
			sb.insert(b[i]);
		}
		else {
			ok = false;
			FOR(j, i) {
				if (sb.count(b[i]-b[j])) {
					ok = true;
					break;
				}
			}
			if (ok) sb.insert(b[i]);
			else {
				printf("%d\n", b[i]);
				break;
			}
		}
	}
	if (ok) printf("sim\n");
	return 0;
}