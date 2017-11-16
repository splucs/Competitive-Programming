#include <bits/stdc++.h>
using namespace std;
#define MAXN 509
#define MAXS 1000009

int N, M;
int depth[MAXN][MAXN], maxd[MAXN][MAXN];
vector<int> qx[MAXS], qy[MAXS];

int main() {
	scanf("%d %d", &N, &M);
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=M; j++) {
			scanf("%d", &depth[i][j]);
			depth[i][j] *= -1;
		}
	}
	memset(&maxd, 0, sizeof maxd);
	int i, j;
	scanf("%d %d", &i, &j);
	maxd[i][j] = depth[i][j];
	qx[depth[i][j]].push_back(i);
	qy[depth[i][j]].push_back(j);
	long long ans = 0;
	for(int d = depth[i][j], it; d>0; d--) {
		it = 0;
		while(it < (int)qx[d].size()) {
			i = qx[d][it];
			j = qy[d][it];
			it++;
			if (maxd[i][j] != d) continue;
			ans += maxd[i][j];
			//printf("maxd[%d][%d] = %d\n", i, j, maxd[i][j]);
			for(int ni = i-1; ni<=i+1; ni++) {
				for(int nj = j-1; nj<=j+1; nj++) {
					if (ni == i && nj == j) continue;
					if (ni < 1 || nj < 1 || ni > N || nj > M) continue;
					if (maxd[ni][nj] >= min(maxd[i][j], depth[ni][nj])) continue;
					maxd[ni][nj] = min(maxd[i][j], depth[ni][nj]);
					if (maxd[ni][nj] <= 0) continue;
					qx[maxd[ni][nj]].push_back(ni);
					qy[maxd[ni][nj]].push_back(nj);
				}
			}
		}
	}
	printf("%I64d\n", ans);
	return 0;
}