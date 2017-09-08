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
		i++; j++;
		if (i > j) return;
		update(ft1, i, v);
		update(ft1, j+1, -v);
		update(ft2, i, v*(i-1));
		update(ft2, j+1, -v*j);
	}
	ll rsq(int i){
		i++;
		return rsq(ft1, i)*i - rsq(ft2, i);
	}
	ll rsq(int i, int j){
		if (i > j) return 0;
		return rsq(j) - rsq(i-1);
	}
};

typedef pair<int, int> ii;
vector<ii> adjList[MAXN];
int N, M, Q;
FenwickTree nds(1), eds(1), freq(1);

#define DEBUG 75

int main() {
	while(scanf("%d %d", &N, &M) != EOF) {
		int u, v, w;
		freq = FenwickTree(MAXN);
		for(u=1; u<=N; u++) adjList[u].clear();
		for(int j=0; j<M; j++) {
			scanf("%d %d %d", &u, &v, &w);
			adjList[u].push_back(ii(w, v));
			adjList[v].push_back(ii(w, u));
			freq.update(0, w, 1);
		}
		nds = FenwickTree(MAXN);
		eds = FenwickTree(MAXN);
		for(u=1; u<=N; u++) {
			sort(adjList[u].begin(), adjList[u].end());
			
			/*printf("node %d:", u);
			for(int i=0; i<(int)adjList[u].size(); i++) {
				printf(" %d", adjList[u][i].first);
			}
			printf("\n");*/
			int t0, t1, t2;
			//no edges
			if (adjList[u].empty()) t0 = 0;
			else t0 = adjList[u].back().first+1;
			nds.update(t0, MAXN-1, 1);
			//printf("node %d eliminated from %d on\n", u, t0);
			//if (DEBUG >= t0) printf("%d eliminated for %d\n", u, DEBUG);
			if (t0 == 0) continue;
			//two edges
			int it = ((int)adjList[u].size()) - 3;
			if (it == -1) t1=0, t2=adjList[u][0].first;
			else if (it < -1) t1 = MAXN, t2=MAXN-1;
			else {
				t1 = adjList[u][it].first+1;
				t2 = adjList[u][it+1].first;
			}
			//printf("node %d eliminated from %d to %d\n", u, t1, t2);
			//if (DEBUG <= t2 && t1 <= DEBUG) printf("%d eliminated for %d\n", u, DEBUG);
			nds.update(t1, t2, 1);
			eds.update(t1, t2, 1);
		}
		scanf("%d", &Q);
		for(int j=0, t; j<Q; j++) {
			scanf("%d", &t);
			printf("%d %d\n", max(N-(int)nds.rsq(t, t), freq.rsq(t, t) > 0 ? 1 : 0),
			(int)max(freq.rsq(t, t) - eds.rsq(t, t), freq.rsq(t, t) > 0 ? 1LL : 0LL));
		}
	}
	return 0;
}