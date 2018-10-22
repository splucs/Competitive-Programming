#include <bits/stdc++.h>
#define MAXN 59
#define FOR(x, n) for(int x=0; x<n; x++)
#define REP(x, n) for(int x=n-1; x>=0; x--)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define REP1(x, n) for(int x=n; x>0; x--)
#define all(x) x.begin(), x.end()
#define sz(x) (int (x.size()) )
using namespace std;

int p[MAXN], w[MAXN];
double P[MAXN];

int main() {
	#ifdef ONLINE_JUDGE
	freopen("casino.in", "r", stdin);
	freopen("casino.out", "w", stdout);
	#endif

	int n, m, s;
	while(scanf("%d %d %d", &n, &m, &s) != EOF) {
		FOR(j, m) scanf("%d %d", &p[j], &w[j]);
		FOR(i, n+2) P[i] = 0;
		double cur, curl, curr;
		FOR(it, 100000) {
			FOR1(i, n) {
				FOR(j, m) {
					curl = ((i+w[j]) > n) ? 1.0 : P[i+w[j]];
					curr = ((i-1) <= 0) ? 0.0 : P[i-1];
					cur = (p[j]*curl + (s-p[j])*curr) / s;
					if (cur > P[i]) P[i] = cur;
				}
			    //printf("%.20f ", P[i]);
			}
			//printf("\n");
		}
		printf("%.20f\n", P[n]);
	}
	return 0;
}