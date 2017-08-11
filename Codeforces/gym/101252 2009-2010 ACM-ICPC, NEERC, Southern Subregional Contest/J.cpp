#include <bits/stdc++.h>
using namespace std;

int N, K;

void solve(int i, int k) {
	if (k == 0) return;
	printf("+%d", i);
	int j;
	for(int j=i; j<=N-k+1; j++) {
		solve(j+1, k-1);
		if (j<N-k+1) printf("++%d", j);
	}
	printf("-%d", N-k+1);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	while(!feof(stdin)) {
		scanf(" %d %d ", &N, &K);
		solve(1, K);
		printf("\n");
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}