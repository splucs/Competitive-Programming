#include <bits/stdc++.h>
using namespace std;
#define MAXN 209
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef vector<int> vi;

int wire[MAXN][MAXN];
int n, a[MAXN], ans[MAXN], aux[MAXN];

int main() {
	#ifdef ONLINE_JUDGE
	freopen("bubble.in", "r", stdin);
	freopen("bubble.out", "w", stdout);
	#endif

	while(scanf("%d", &n) != EOF) {
		FOR(i, n-1) FOR(it, i+1) {
			scanf("%d", &wire[it][i]);
		}
		FOR(i, n) a[i] = i;
		FOR(it, n-1) {
			REP(j, n-1) {
				if (wire[it][j]) {
					//printf("wire %d greater than wire %d\n", a[j], a[j+1]);
					swap(a[j], a[j+1]);
				}
				//else printf("wire %d less than wire %d\n", a[j], a[j+1]);
			}
		}
		FOR(i, n) aux[a[i]] = ans[a[i]] = i;
		
			//FOR(i, n) printf("%d ", ans[i]+1);
			//printf("\n");

		bool ok = true;
		FOR(it, n-1) {
			REP(j, n-1) {
				if ((aux[j] > aux[j+1]) != wire[it][j]) {
					ok = false;
				}
				if (aux[j] > aux[j+1]) swap(aux[j], aux[j+1]);
			}
		}
		if (ok) {
			printf("YES\n");
			FOR(i, n) printf("%d ", ans[i]+1);
			printf("\n");
		}
		else printf("NO\n");
	}
	return 0;
}