#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009

char op[MAXN];
int cst[MAXN], N;

int apply(int x) {
	for(int i=0; i<N; i++) {
		if (op[i] == '^') x ^= cst[i];
		if (op[i] == '|') x |= cst[i];
		if (op[i] == '&') x &= cst[i];
	}
	return x;
}

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf(" %c %d", &op[i], &cst[i]);
	}
	int ans0 = apply(0);
	int ans1 = apply(1023);
	int xorcst = 0;
	int andcst = 1023;
	int orcst = 0;
	for(int i=0; i<10; i++) {
		if ((ans0 & (1<<i)) == 0 && (ans1 & (1<<i)) == 0) andcst ^= (1<<i);
		if ((ans0 & (1<<i)) == 0 && (ans1 & (1<<i)) != 0) continue;
		if ((ans0 & (1<<i)) != 0 && (ans1 & (1<<i)) == 0) xorcst ^= (1<<i);
		if ((ans0 & (1<<i)) != 0 && (ans1 & (1<<i)) != 0) orcst ^= (1<<i);
	}
	printf("3\n| %d\n& %d\n^ %d\n", orcst, andcst, xorcst);
	return 0;
}