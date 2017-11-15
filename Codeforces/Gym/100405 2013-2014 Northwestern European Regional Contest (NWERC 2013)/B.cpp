#include <bits/stdc++.h>
using namespace std;
#define MAXN 459

int N, M, S[MAXN], ans, id[MAXN], lf[MAXN], adjMatrix[MAXN][MAXN];
vector<int> cur;

void backtrack(int it, int sum) {
	int u = id[it];
	ans = max(ans, sum);
	if (it == N) return;
	
	if (sum + lf[it] <= ans) return;
	
	backtrack(it+1, sum);
	
	bool ok = true;
	for(int i=0; i<(int)cur.size() && ok; i++) {
		int v = cur[i];
		if (!adjMatrix[u][v]) ok = false;
	}
	if (!ok) return;
	
	cur.push_back(u);
	backtrack(it+1, sum+S[u]);
	cur.pop_back();
}

bool comp(int i, int j) {
	return S[i] > S[j];
}

int main() {
	while(scanf("%d %d", &N, &M) != EOF) {
		memset(&adjMatrix, 0, sizeof adjMatrix);
		for(int i=0; i<N; i++) {
			scanf("%d", &S[i]);
			id[i] = i;
		}
		for(int j=0, u, v; j<M; j++) {
			scanf("%d %d", &u, &v);
			adjMatrix[u-1][v-1] = adjMatrix[v-1][u-1] = 1;
		}
		
		sort(id, id+N, comp);
		lf[N] = 0;
		for(int i=N-1; i>=0; i--) {
			lf[i] = S[id[i]] + lf[i+1];
		}
		
		ans = 0;
		backtrack(0, 0);
		printf("%d\n", ans);
	}
	
	return 0;
}