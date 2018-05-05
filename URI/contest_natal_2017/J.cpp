#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

typedef unsigned long long ll;
ll arr[MAXN], sum[MAXN], A, B, pascal[MAXN][MAXN];
int N, K;

ll bt(int i, ll p, int k) {
	if (i == -1) {
		return p >= A && p <= B && k == 0 ? 1 : 0;
	}
	if (k == 0) return p >= A && p <= B ? 1 : 0;
	if (i+1 < k) return 0;

	ll biggest = p + sum[i] - (i>=k ? sum[i-k] : 0);
	ll smallest = p + sum[k-1];
	if (smallest > B) return 0;
	if (biggest < A) return 0;
	if (smallest >= A && biggest <= B) return pascal[i+1][k];
	return bt(i-1, p, k) + bt(i-1, p+arr[i], k-1);
}

int main() {
	for(int n = 0; n < MAXN; n++) {
		for(int k = 0; k < MAXN; k++) {
			if (k > n) pascal[n][k] = 0;
			else if (k == 0 || k == n) pascal[n][k] = 1;
			else pascal[n][k] = pascal[n-1][k] + pascal[n-1][k-1];
		}
	}
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d", &N, &K);
		for(int i = 0; i < N; i++) {
			scanf("%llu", &arr[i]);
		}
		scanf("%llu %lld", &A, &B);
		sort(arr, arr+N);
		sum[0] = arr[0];
		for(int i = 1; i < N; i++) sum[i] = arr[i] + sum[i-1];
		printf("%llu\n", bt(N-1, 0, K));
	}
	return 0;
}