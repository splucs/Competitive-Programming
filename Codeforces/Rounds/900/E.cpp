#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF 1000000009

int N, M;
char str[MAXN];
typedef pair<int, int> ii;
ii dp[MAXN];
int app[2][2][MAXN], inter[MAXN];

int wrongA(int i, int j) {
	int low = i > 0 ? app[0][1-(i%2)][i-1] : 0;
	int high = app[0][1-(i%2)][j];
	//printf("%d a's in wrong position from %d to %d\n", high-low, i, j);
	return high - low;
}

int wrongB(int i, int j) {
	int low = i > 0 ? app[1][i%2][i-1] : 0;
	int high = app[1][i%2][j];
	//printf("%d b's in wrong position from %d to %d\n", high-low, i, j);
	return high - low;
}

int interrogations(int i, int j) {
	int low = i > 0 ? inter[i-1] : 0;
	int high = inter[j];
	return high - low;
}

int main() {
	scanf("%d %s %d", &N, str, &M);
	for(int i=0; i<N; i++) {
		app[0][0][i] = i > 0 ? app[0][0][i-1] : 0;
		app[0][1][i] = i > 0 ? app[0][1][i-1] : 0;
		app[1][0][i] = i > 0 ? app[1][0][i-1] : 0;
		app[1][1][i] = i > 0 ? app[1][1][i-1] : 0;
		inter[i] = i > 0 ? inter[i-1] : 0;
		if (str[i] == 'a') app[0][i%2][i]++;
		if (str[i] == 'b') app[1][i%2][i]++;
		if (str[i] == '?') inter[i]++;
	}
	for(int i = N-1; i >= 0; i--) {
		dp[i] = ii(0, 0);
		if (i + 1 < N) dp[i] = max(dp[i], dp[i+1]);
		int j = i + M-1;
		if (j < N && wrongA(i, j) == 0 && wrongB(i, j) == 0) {
			int nmatch = 1 + (i+M < N ? dp[i+M].first : 0);
			int subs = interrogations(i, j) + (i+M < N ? -dp[i+M].second : 0);
			dp[i] = max(dp[i], ii(nmatch, -subs));
		}
		//printf("nmatches from %d: %d\n", i, dp[i].first);
		//printf("subs from %d: %d\n", i, -dp[i].second);
	}
	int ans = -dp[0].second;
	printf("%d\n", ans);
	return 0;
}