#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009

typedef long long ll;

class FenwickTree {
private:
	vector<ll> ft1, ft2;
	ll rsq(vector<ll> & ft, int i) {
		ll sum = 0;
		while(i > 0){
			sum += ft[i];
			i -= (i & -i);
		}
		return sum;
	}
	void update(vector<ll> & ft, int i, ll v) {
		while(i < (int)ft.size()) {
			ft[i] += v;
			i += (i & -i);
		}
	}
public:
	FenwickTree(int n) {
		ft1.assign(n + 1, 0);	//1-indexed
		ft2.assign(n + 1, 0);	//1-indexed
	}
	void update(int i, int j, ll v){
		if (i > j) return;
		update(ft1, i, v);
		update(ft1, j+1, -v);
		update(ft2, i, v*(i-1));
		update(ft2, j+1, -v*j);
	}
	ll rsq(int i){
		return rsq(ft1, i)*i - rsq(ft2, i);
	}
	ll rsq(int i, int j){
		if (i > j) return 0;
		return rsq(j) - rsq(i-1);
	}
};

struct rec {
	int xt, yt, xb, yb;
} recs[MAXN];

struct point {
	int x, y, id;
	bool operator < (point o) {
		if (x != o.x) return x < o.x;
		return y < o.y;
	}
} spots[MAXN];

int N, M, xmax, ymax;

void reduce_coordinates() {
	map<int, int> xapp, yapp;
	for(int i=0; i<N; i++) {
		xapp[spots[i].x] = 0;
		yapp[spots[i].y] = 0;
	}
	for(int j=0; j<M; j++) {
		xapp[recs[j].xb] = 0; xapp[recs[j].xt] = 0;
		yapp[recs[j].yb] = 0; yapp[recs[j].yt] = 0;
	}
	
	xmax = 0;
	for(map<int, int>::iterator it = xapp.begin(); it != xapp.end(); it++) {
		it->second = ++xmax;
	}
	ymax = 0;
	for(map<int, int>::iterator it = yapp.begin(); it != yapp.end(); it++) {
		it->second = ++ymax;
	}
	
	for(int i=0; i<N; i++) {
		spots[i].x = xapp[spots[i].x];
		spots[i].y = yapp[spots[i].y];
		//printf("point at (%d,%d)\n", spots[i].x, spots[i].y);
	}
	for(int j=0; j<M; j++) {
		recs[j].xb = xapp[recs[j].xb];
		recs[j].xt = xapp[recs[j].xt];
		recs[j].yb = yapp[recs[j].yb];
		recs[j].yt = yapp[recs[j].yt];
		//printf("rec at (%d,%d)-(%d,%d)\n", recs[j].xb, recs[j].yb, recs[j].xt, recs[j].yt);
	}
}

typedef pair<int, int> ii;
vector<ii> up[MAXN], down[MAXN];
ll ans[MAXN];
FenwickTree ft(1);

void solve() {
	sort(spots, spots+N);
	int p = 0;
	
	for(int j=0; j<M; j++) {
		up[recs[j].xb].push_back(ii(recs[j].yb+1, recs[j].yt-1));
		down[recs[j].xt].push_back(ii(recs[j].yb+1, recs[j].yt-1));
	}
	
	ft = FenwickTree(MAXN);
	for(int x=1; x<=xmax; x++) {
		for(int i=0; i<(int)down[x].size(); i++) {
			ii cur = down[x][i];
			ft.update(cur.first, cur.second, -1);
		}
		
		while(p < N && spots[p].x == x) {
			ans[spots[p].id] = ft.rsq(spots[p].y, spots[p].y);
			p++;
		}
		
		for(int i=0; i<(int)up[x].size(); i++) {
			ii cur = up[x][i];
			ft.update(cur.first, cur.second, 1);
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++) {
		scanf("%d %d", &spots[i].x, &spots[i].y);
		spots[i].id = i;
	}
	for(int j=0; j<M; j++) {
		scanf("%d %d %d %d", &recs[j].xb, &recs[j].yb, &recs[j].xt, &recs[j].yt);
	}
	reduce_coordinates();
	solve();
	for(int i=0; i<N; i++) printf("%I64d\n", ans[i]);
	return 0;
}