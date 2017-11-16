#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

int bit[MAXN], last[MAXN];

void update(int i, int v) {
	while(i < MAXN) {
		bit[i] += v;
		i += (i & -i);
	}
}

int query(int i) {
	int sum = 0;
	while(i > 0) {
		sum += bit[i];
		i -= (i & -i);
	}
	return sum;
}

int query(int i, int j) {
	return query(j) - query(i-1);
}

int main() {
	int T, N, M;
	scanf("%d", &T);
	while(T --> 0) {
		
		memset(&bit, 0, sizeof bit);
		scanf("%d %d", &N, &M);
		for(int i=1, v; i<=N; i++) {
			v = N-i+1;
			update(i, 1);
			last[v] = i;
		}
		
		for(int i = N+1, v; i<=N+M; i++) {
			scanf("%d", &v);
			printf("%d", query(last[v]+1, MAXN-1));
			if (i < N+M) printf(" ");
			else printf("\n");
			update(last[v], -1);
			update(i, 1);
			last[v] = i;
		}
	}
	
	return 0;
}