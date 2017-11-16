#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

int w[MAXN], h[MAXN];

bool comp(int i, int j) {
	return i > j;
}

int main() {
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=0; i<N; i++) {
			scanf("%d", &w[i]);
		}
		for(int i=0; i<N; i++) {
			scanf("%d", &h[i]);
		}
		for(int i=0; i<N; i++) {
			if (h[i] > h[0]) swap(h[0], h[i]);
		}
		sort(w+1, w+N);
		sort(h+1, h+N, comp);
		bool possible = true;
		for(int i=1; i<N; i++) {
			if (w[0]*h[0] <= w[i]*h[i]) possible = false;
		}
		if (possible) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}