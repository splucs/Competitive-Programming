#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009

int arr[MAXN], d[MAXN][MAXN], id[MAXN][MAXN], N;
bool app[MAXN];

void solve(int l, int r) {
	if (l == r) return;
	int u = arr[l], v, w;
	memset(&app, false, sizeof app);
	for(int i=l; i<=r; i++) {
		app[arr[i]] = true;
	}
	for(int i=2; i<=N; i++) {
		if (app[d[u][i]]) {
			v = d[u][i];
			break;
		}
	}
	printf("%d %d\n", u, v);
	for(int i=l; i<=r; i++) {
		if (arr[i] == v) {
			swap(arr[i], arr[r]);
			break;
		}
	}
	int m = l+1;
	for(int i=l+1; i<r; i++) {
		w = arr[i];
		if (id[w][u] < id[w][v]) swap(arr[m++], arr[i]);
	}
	solve(l, m-1);
	solve(m, r);
}

int main() {
	int T;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=1; i<=N; i++) {
			arr[i] = i;
			for(int j=1; j<=N; j++) {
				scanf("%d", &d[i][j]);
				id[i][d[i][j]] = j;
			}
		}
		solve(1, N);
		printf("\n");
	}
	return 0;
}