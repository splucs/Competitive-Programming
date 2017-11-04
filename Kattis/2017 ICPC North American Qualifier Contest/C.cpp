#include <bits/stdc++.h>
using namespace std;
#define MAXN 5000009
#define MAXC 109
#define INF (1<<30)

int N, arr[MAXC], dp[MAXN], greed, value;

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr+N);
	dp[0] = 0;
	bool ok = true;
	for(int i=1; i<MAXN && ok; i++) {
		dp[i] = INF;
		for(int j=0; j<N; j++) {
			if (i >= arr[j] && dp[i] > 1+dp[i-arr[j]]) dp[i] = 1+dp[i-arr[j]];
		}
		greed = 0;
		value = i;
		for(int j=N-1; j>=0; j--) {
			greed += value/arr[j];
			value -= (value/arr[j])*arr[j];
		}
		if (greed != dp[i]) ok = false;
	}
	if (ok) printf("canonical\n");
	else printf("non-canonical\n");
	return 0;
}