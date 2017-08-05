#include <algorithm>
#include <vector>
using namespace std;
#define MAXN 100009
#define MAXS 320

typedef pair<int, int> ii;
int arr[MAXN], N, sn, ans[i], curAns;
vector<ii> queries[MAXN][MAXS];

void add(int i) { ... }
void save() { ... }
void reset() { ... }
void clear() { ... }

void solvequeries(int l, int r, int bl) {
	for(int k=0; k<(int)queries[l][bl].size(); k++) {
		ii cur = queries[l][bl][k];
		while(r < cur.first) add(++r);
		ans[cur.second] = curAns;
	}
}

void solveblock(int bl) {
	clear();
	int r = min(bl*sn, N);
	for(int l=r; l > 0; l--) {
		add(l);
		save();
		solvequeries(l, r, bl);
		reset();
	}
}

void blockquery(int l, int r, int id) {
	clear();
	for(int i=l; i<=r; i++) add(i);
	ans[id] = curAns;
}

void mo() {
	sn = sqrt(N);
	for(int q=1, u, v; q<=Q; q++) {
		scanf("%d %d", &u, &v);
		if (u/sn == v/sn) blockquery(u, v, q);
		else queries[u][v/sn].push_back(ii(v, q));
	}
	for(int i=1; i<=N; i++) {
		for(int j=0; j<MAXS; j++) {
			sort(queries[i][j].begin(), queries[i][j].end());
		}
	}
	for(int j=1; j<MAXS; j++) solveblock(j);
}