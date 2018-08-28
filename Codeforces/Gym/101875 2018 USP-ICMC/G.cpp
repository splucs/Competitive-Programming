#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define FOR1(i, n) for(int i = 1; i <= int(n); i++)
#define MAXN 1000009
#define MAXLOGN 20
#define INF 1e+30
#define EPS 1e-9
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> ii;

double inter(double nm, double nn, double lm, double ln) {
	double x = (ln-nn)/(nm-lm);
	return x;
}

ii car[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	FOR(i, n) scanf("%d %d", &car[i].fi, &car[i].se);
	sort(car, car+n, greater<ii>());
	vector<int> va;
	vector<int> vs;
	vector<double> ve;
	double ans = 0;
	FOR(i, n) {
		int a = car[i].se;
		int s = car[i].fi;
		//printf("inserting %dx + %d\n", a, s);
		while(!va.empty()) {
			int cura = va.back();
			int curs = vs.back();
			if (a == cura) {
				va.pop_back();
				vs.pop_back();
				ve.pop_back();
			}
			else {
				double x = inter(cura, curs, a, s);
				if (x < EPS || x >= ve.back()) {
					va.pop_back();
					vs.pop_back();
					ve.pop_back();
				}
				else break;
			}
		}
		double x = ve.empty() ? INF : inter(va.back(), vs.back(), a, s);
		if (!ve.empty()) ans = max(ans, x);
		va.pb(a);
		vs.pb(s);
		ve.pb(x);
		//FOR(j, sz(vs)) {
		//	printf("(%.3f], %dx+%d\n", ve[j], va[j], vs[j]);
		//}
	}
	printf("%.20f\n", ans);
	return 0;
}