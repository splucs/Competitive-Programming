#include <bits/stdc++.h>
using namespace std;
#define INF (1LL<<40)
#define MAXN 1000009

typedef long long ll;
int N, M, K;
ll arrcost[MAXN], depcost[MAXN];
ll curcost[MAXN];

struct flight {
	int t;
	int cost;
	int city;
	flight(int _t, int _cost, int _city) : city(_city), t(_t), cost(_cost) {}
};

bool comp(flight & f1, flight & f2) {
	return f1.t < f2.t;
}

vector<flight> dep, arr;

int main() {
	scanf("%d %d %d", &N, &M, &K);
	int d, f, t, c;
	for(int j=0; j<M; j++) {
		scanf("%d %d %d %d", &d, &f, &t, &c);
		if (f == 0) arr.push_back(flight(d, c, t));
		else dep.push_back(flight(d, c, f));
	}
	sort(arr.begin(), arr.end(), comp);
	sort(dep.begin(), dep.end(), comp);
	int k=0;
	for(int i=1; i<=N; i++) curcost[i] = INF;
	for(t=0; t<=MAXN-1; t++) {
		depcost[t] = t == 0 ? N*INF : depcost[t-1];
		while(k < (int)dep.size() && dep[k].t <= t) {
			ll dc = curcost[dep[k].city] - dep[k].cost;
			if (dc > 0) {
				//printf("flight from city %d with cost %d\n", dep[k].city, dep[k].cost);
				depcost[t] -= dc;
				curcost[dep[k].city] -= dc;
			}
			k++;
		}
		//printf("depcost[%d] = %I64d\n", t, depcost[t]);
	}
	arrcost[MAXN-1] = N*INF;
	k = ((int)arr.size()) - 1;
	for(int i=1; i<=N; i++) curcost[i] = INF;
	for(t=MAXN-2; t>=0; t--) {
		arrcost[t] = arrcost[t+1];
		while(k >= 0 && arr[k].t >= t) {
			ll dc = curcost[arr[k].city] - arr[k].cost;
			if (dc > 0) {
				//printf("flight to city %d with cost %d\n", arr[k].city, arr[k].cost);
				arrcost[t] -= dc;
				curcost[arr[k].city] -= dc;
			}
			k--;
		}
		//printf("arrcost[%d] = %I64d\n", t, arrcost[t]);
	}
	ll ans = INF;
	for(t=0; t+K+1<MAXN; t++) {
		ans = min(depcost[t] + arrcost[t+K+1], ans);
	}
	if (ans == INF) printf("-1\n");
	else printf("%I64d\n", ans);
	return 0;
}