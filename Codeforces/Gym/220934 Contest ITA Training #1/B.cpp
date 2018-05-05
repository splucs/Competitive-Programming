#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int F[MAXN], idf[MAXN], ida[MAXN], ans[MAXN], A, B, C, N, M;
map<int, int> amount;

bool compf(int i, int j) {
	return F[i] < F[j];
}

bool compa(int i, int j) {
	return amount[i] < amount[j];
}

int main() {
	scanf("%d %d %d %d %d %d", &F[0], &A, &B, &C, &N, &M);
	int z;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			scanf("%d", &z);
			amount[z]++;
		}
	}

	int sz = 0;
	for(auto it = amount.begin(); it != amount.end(); it++) {
		ida[sz++] = it->first;
		//printf("amount(%d) = %d\n", it->first, it->second);
	}
	sort(ida, ida+sz, compa);

	for(int i = 0; i < sz; i++) {
		if (i > 0) F[i] = (A*F[i-1] + B) % C + 1;
		idf[i] = i;
		//printf("F[%d] = %d\n", i, F[i]);
	}
	sort(idf, idf+sz, compf);

	for(int i = 0; i < sz; i++) {
		ans[idf[i]] = ida[i];
	}
	
	printf("%d\n", sz);
	for(int i = 0; i < sz; i++) printf("%d ", ans[i]);
	printf("\n");

	return 0;
}