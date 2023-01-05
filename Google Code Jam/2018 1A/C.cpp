#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define MOD 1000000007
#define INF (1LL<<60)
#define EPS 1e-7
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int N;
double P;
typedef pair<double, double> dd;
double mi[MAXN], ma[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d %lf", &N, &P);
		double W, H, sum = 0;
		vector<dd> intervals;
		vector<dd> toadd;
		vector<dd> newintervals;
		FOR(i, N) {
			scanf("%lf %lf", &W, &H);
			mi[i] = 2*min(W, H);
			ma[i] = 2*hypot(W, H);
			sum += 2*(W+H);
		}
		intervals.pb(dd(sum, sum));
		FOR(i, N) {
			toadd.clear();
			for(dd in : intervals) {
				toadd.pb(dd(in.first + mi[i], in.second + ma[i]));
			}
			int l = 0, r = 0;
			newintervals.clear();
			while (l < int(intervals.size()) && r < int(toadd.size())) {
				if (intervals[l].second >= toadd[r].first && intervals[r].first <= toadd[r].first) {
					intervals[l].second = max(intervals[l].second, toadd[r].second);
					r++;
				}
				else if (intervals[l].first <= toadd[r].second && intervals[l].first >= toadd[r].first) {
					toadd[r].second = max(toadd[r].second, intervals[l].second);
					l++;
				}
				else if (intervals[l].first > toadd[r].first) {
					if (toadd[r].first <= P) newintervals.pb(toadd[r]);
					r++;
				}
				else {
					if (intervals[l].first <= P) newintervals.pb(intervals[l]);
					l++;
				}
			}
			while (l < int(intervals.size())) {
				if (intervals[l].first <= P) newintervals.pb(intervals[l]);
				l++;
			}
			while (r < int(toadd.size())) {
				if (toadd[r].first <= P) newintervals.pb(toadd[r]);
				r++;
			}
			intervals.swap(newintervals);
		}
		double ans = 0;
		for(dd in : intervals) {
			if (in.first <= P) {
				ans = max(ans, min(P, in.second));
			}
		}
		printf("Case #%d: %.7f\n", caseNo, ans);
	}
	return 0;
}