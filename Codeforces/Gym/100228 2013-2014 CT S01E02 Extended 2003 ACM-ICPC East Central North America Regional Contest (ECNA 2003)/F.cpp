#include <bits/stdc++.h>
using namespace std;
#define MAXN 29

int N, M, b[MAXN][MAXN];

int getMaxDi() {
	int ans = 0;
	for(int j=0; j<M; j++) {
		int cur = 0;
		for(int i=0; i<N; i++) {
			if (b[i][j] > 0) cur++;
		}
		ans = max(ans, cur);
	}
	return N-ans;
}

int getMaxDj() {
	int ans = 0;
	for(int i=0; i<N; i++) {
		int cur = 0;
		for(int j=0; j<M; j++) {
			if (b[i][j] > 0) cur++;
		}
		ans = max(ans, cur);
	}
	return M-ans;
}

bool move(int i, int j, int di, int dj) {
	if (i < 0 || i >= N || j < 0 || j >= M) return false;
	if (b[i][j] == 0) return true;
	if (!move(i+di, j+dj, di, dj)) return false;
	b[i+di][j+dj] = b[i][j];
	b[i][j] = 0;
	return true;
}

void push(int di, int dj, int D) {
	if (di != 0) D = min(D, getMaxDi());
	if (dj != 0) D = min(D, getMaxDj());
	if (di > 0)
		for(int i=0; i<D; i++) for(int j=0; j<M; j++)
			if(!move(i, j, di, dj)) printf("error!\n");
	if (di < 0)
		for(int i=0; i<D; i++) for(int j=0; j<M; j++)
			if(!move(N-1-i, j, di, dj)) printf("error!\n");
	if (dj > 0)
		for(int j=0; j<D; j++) for(int i=0; i<N; i++)
			if(!move(i, j, di, dj)) printf("error!\n");
	if (dj < 0)
		for(int j=0; j<D; j++) for(int i=0; i<N; i++)
			if(!move(i, M-1-j, di, dj)) printf("error!\n");
}

char com[9];

void printb() {
	for(int i=0; i<N; i++) {
		for(int j=0; j<M; j++) {
			printf("%d ", b[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	int K, D, caseNo=1;
	while(scanf("%d %d", &N, &M), N||M) {
		memset(&b, 0, sizeof b);
		scanf("%d", &K);
		for(int k=1, i, j; k<=K; k++) {
			scanf("%d %d", &i, &j);
			b[i][j] = k;
		}
		//printb();
		while(scanf(" %s", com), strcmp(com, "done") != 0) {
			scanf("%d", &D);
			int di=0, dj=0;
			if (strcmp(com, "down") == 0) di = 1;
			if (strcmp(com, "up") == 0) di = -1;
			if (strcmp(com, "left") == 0) dj = -1;
			if (strcmp(com, "right") == 0) dj = 1;
			push(di, dj, D);
			//printb();
		}
		printf("Data set %d ends with boxes at locations", caseNo++);
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				if (b[i][j] > 0) printf(" (%d,%d)", i, j);
			}
		}
		printf(".\n");
	}
	return 0;
}