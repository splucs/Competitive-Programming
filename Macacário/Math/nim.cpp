/*
 *	Codeforces 101128G
 */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 109
#define MAXM 1009

int K, mat[MAXN][MAXM];
int N, S[MAXN];

vector<int> adjPos(int i, int u) {
	vector<int> ans;
	for(int k=0, v; k<=K; k++) {
		v = u-k;
		if (v < 1) break;
		v -= mat[i][v];
		if (v < 0) continue;
		ans.push_back(v);
	}
	return ans;
}

bool nim() {
	int ans = 0, g[MAXM];
	vector<int> F, G;
	for(int i=0; i<N; i++) {
		g[0] = 0; 
		for(int u=1; u<=S[i]; u++) {
			F = adjPos(i, u);
			G.clear();
			for(int j=0; j<(int)F.size(); j++) {
				G.push_back(g[F[j]]);
			}
			sort(G.begin(), G.end());
			g[u] = 0;
			for(int j=0; j<(int)G.size() && G[j] <= g[u]; j++) {
				if (G[j] == g[u]) g[u]++;
			}
		}
		ans ^= g[S[i]];
	}
	return ans != 0;
}	

int main() {
	scanf("%d %d", &N, &K);
	for(int i=0; i<N; i++) {
		scanf("%d", &S[i]);
		mat[i][0] = 0;
		for(int j=1; j<=S[i]; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
	if (nim()) printf("Alice can win.\n");
	else printf("Bob will win.\n");
	return 0;
}
