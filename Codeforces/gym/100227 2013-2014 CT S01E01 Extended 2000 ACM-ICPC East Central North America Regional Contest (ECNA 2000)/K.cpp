#include <bits/stdc++.h>
using namespace std;
#define MAXN 309

int num[MAXN], mat[MAXN][MAXN], row[MAXN], K;
bool app[MAXN];

void printmat(int N) {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

bool build(int N) {
	memset(&mat, 0, sizeof mat);
	memset(&row, 0, sizeof row);
	memset(&app, false, sizeof app);
	//printf("N = %d:\n", N);
	for(int i=N-1; i>0; i--) {
		int target = -1;
		for(int j=K-1; j >= 0; j--) {
			if (!app[j] || (j > 0 && num[j-1] < row[j])) {
				target = j;
				break;
			}
		}
		if (target == -1) return false;
		app[target] = true;
		target = num[target];
		//printf("target for row %d is %d\n", i, target);
		for(int j=i-1; j>=0 && row[i] < target; j--) {
			mat[i][j]++;
			mat[j][i]++;
			row[i]++;
			row[j]++;
		}
		if (row[i] < target) return false;
	}
	bool ok = false;
	for(int j=0; j<K; j++) {
		if (num[j] == row[0]) {
			ok = true;
			app[j] = true;
		}
		if (!app[j]) return false;
	}
	if (!ok) return false;
	//printmat(N);
	return true;
}

int main() {
	scanf("%d", &K);
	for(int i=0; i<K; i++) scanf("%d", &num[i]);
	int ans = 1;
	for(ans=1; ans<MAXN; ans++) if (build(ans)) break;
	build(ans);
	printf("%d\n", ans);
	printmat(ans);
	return 0;
	
}