#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int c[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int N, L, x;
	bool possible = true;
	scanf("%d %d", &N, &L);
	memset(&c, 0, sizeof c);
	while(N--) {
		scanf("%d", &x);
		c[x]++;
	}
	for(int i=0; i<MAXN; i++) {
		if (c[i]%L != 0) possible = false;
	}
	if (possible) printf("OK\n");
	else printf("ARGH!!1\n");
	fclose(stdin);
	fclose(stdout);
	return 0;
}