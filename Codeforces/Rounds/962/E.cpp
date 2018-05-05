#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF (1LL<<60)

typedef long long ll;
ll x[MAXN];
char own[MAXN];
vector<int> cables[MAXN];

void getmaxmin(int i1, int i2, char c, ll & minc, ll & maxc) {
	minc = INF;
	maxc = -INF;
	for(int i = i1; i <= i2; i++) {
		if (own[i] == c) {
			minc = min(minc, x[i]);
			maxc = max(maxc, x[i]);
		}
	}
}

int main() {
	int N;
	scanf("%d", &N);
	vector<int> pid;
	for(int i = 0; i < N; i++) {
		scanf("%I64d %c", &x[i], &own[i]);
		if (own[i] == 'P') pid.push_back(i);
	}
	ll ans = 0;
	if (pid.empty()) {
		ll minr, maxr, minb, maxb;
		getmaxmin(0, N-1, 'R', minr, maxr);
		getmaxmin(0, N-1, 'B', minb, maxb);
		if (maxr >= minr) ans += maxr - minr;
		if (maxb >= minb) ans += maxb - minb;
	}
	else {
		for (int i = 0; i+1 < int(pid.size()); i++) {
			int id1 = pid[i];
			int id2 = pid[i+1];
			int lastr = id1, lastb = id1;
			ll d = x[id2] - x[id1];
			ll maxb = -INF, maxr = -INF;
			for(int j = id1; j <= id2; j++) {
				if (own[j] == 'P' || own[j] == 'R') {
					maxr = max(maxr, x[j] - x[lastr]);
					lastr = j;
				}
				if (own[j] == 'P' || own[j] == 'B') {
					maxb = max(maxb, x[j] - x[lastb]);
					lastb = j;
				}
			}
			if (maxb < 0 || maxr < 0) ans += d;
			else {
				ll opt1 = 3*d - maxr - maxb;
				ll opt2 = 2*d;
				ans += min(opt1, opt2);
			}
		}
		ll minr = x[pid[0]], maxr = x[pid.back()];
		ll minb = x[pid[0]], maxb = x[pid.back()];
		for(int j = 0; j < N; j++) {
			if (own[j] == 'B') {
				minb = min(minb, x[j]);
				maxb = max(maxb, x[j]);
			}
			if (own[j] == 'R') {
				minr = min(minr, x[j]);
				maxr = max(maxr, x[j]);
			}
		}
		ans += x[pid[0]] - minr;
		ans += x[pid[0]] - minb;
		ans += maxb - x[pid.back()];
		ans += maxr - x[pid.back()];
	}
	printf("%I64d\n", ans);
	return 0;
}