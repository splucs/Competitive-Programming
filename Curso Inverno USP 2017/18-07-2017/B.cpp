#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

set<int> special[MAXN];

bool defeats(int x, int y) {
	if (special[x].count(y)) return true;
	return x > y;
}

int main() {
	int T, N, M, x, y;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d", &N, &M);
		for(int i=1; i<=N; i++) special[i].clear();
		for(int j=1; j<=M; j++) {
			scanf("%d %d", &x, &y);
			special[x].insert(y);
		}
		int ans = 1;
		for(int i=1; i<=N && ans > 0; i++) {
			if (defeats(i, ans)) ans = i;
		}
		for(int i=1; i<=N && ans > 0; i++) {
			if (defeats(i, ans)) ans = -1;
		}
		if (ans > 0) printf("2 %d\n", ans);
		else printf("1\n");
	}
	return 0;
}