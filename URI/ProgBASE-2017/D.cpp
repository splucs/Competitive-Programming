#include <bits/stdc++.h>
using namespace std;
#define MAXN 209

char in[MAXN], bfs[MAXN];
int N, k;

void dfs(int u) {
	if (u > N) return;
	dfs(2*u);
	bfs[u-1] = in[k++];
	dfs(2*u+1);
}

int main() {
	while(scanf("%d%c", &N, &in[0]), N) {
		for(int i=0; i<N; i++) {
			scanf("%c", &in[i]);
		}
		k = 0;
		dfs(1);
		bfs[k] = 0;
		printf("%s\n", bfs);
	}
	return 0;
}