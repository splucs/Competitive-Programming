#include <bits/stdc++.h>
#define MAXN 5009
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define REP(x,n) for(int x=n-1; x>=0; x--)
#define REP1(x,n) for(int x=n; x>0; x--)
#define pb push_back
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef pair<int,int> ii;
typedef long long ll;
typedef vector<int> vi;

int main() {
	int n;
	double x, v;
	while(scanf("%d %lf %lf", &n, &x, &v) != EOF) {
		double vy = 0;
		FOR(i, n) {
			double vi, ri, li;
			scanf("%lf %lf %lf", &li, &ri, &vi);
			vy -= vi*(ri-li);
		}
		vy /= x;
		if (vy > v || v*v - vy*vy < 0) {
			printf("Too hard\n");
			continue;
		}
		double vx = sqrt(v*v - vy*vy);
		double ivx = x/v;
		if (2*vx < ivx + EPS) printf("%.3f\n", x/vx);
		else printf("Too hard\n");
	}
	return 0;
}