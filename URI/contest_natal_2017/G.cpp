#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define OFFSET 7

int arr[MAXN], N;
bool vis[MAXN][20];

bool bt(int i, int b) {
	if (vis[i][b+OFFSET]) return false;
	vis[i][b+OFFSET] = true;
	if (abs(b) > 5) return false;
	if (i == N) return true;
	return bt(i+1, b+arr[i]) || bt(i+1, b-arr[i]);
}

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d", &N);
		for(int i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
		}
		memset(&vis, false, sizeof vis);
		if (bt(0, 0)) printf("Feliz Natal!\n");
		else printf("Ho Ho Ho!\n");
	}
	return 0;
}