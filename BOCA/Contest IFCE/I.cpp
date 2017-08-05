#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int t[MAXN], dt[MAXN];

int main() {
	memset(&t, 0, sizeof t);
	int N, M;
	scanf("%d %d", &N, &M);
	dt[0] = 0;
	for(int i=0; i<N; i++) {
		scanf("%d", &dt[i+1]);
		t[i%M] -= dt[i+1] - dt[i];
	}
	for(int i=0; i<M; i++) {
		t[i] += dt[N];
		printf("%d ", t[i]);
	}
	printf("\n");
	return 0;
}