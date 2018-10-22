#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
typedef long long ll;

int n, cnt[MAXN];
double f, t[MAXN];
int nxt[MAXN], prv[MAXN];

int main() {
	while(scanf("%d %lf", &n, &f) != EOF) {
		set< pair<double,int> > s;
		FOR1(i, n) {
			scanf("%lf", &t[i]);
			cnt[i] = 1;
			s.insert({t[i], i});
		}
		FOR(i, n+2) {
			nxt[i] = i+1;
			prv[i] = i-1;
		}
		double t1, t2;
		while(!s.empty()) {
			int i = s.begin()->se;
			s.erase(s.begin());
			t1 = t[i];
			if (i == n) t2 = t[i];
			nxt[prv[i]] = nxt[i];
			prv[nxt[i]] = prv[i];
			int j = nxt[i];
			if (j == n+1) continue;
			double dt = (t[j] - t[i])*cnt[j];
			s.erase({t[j], j});
			cnt[j] += cnt[i];
			cnt[i] = 0;
			t[j] = t[i] + dt/cnt[j];
			s.insert({t[j], j});
		}
		t1 /= f;
		t2 /= f;
		printf("%.20f %.20f\n", t2, t1);
	}
	return 0;
}