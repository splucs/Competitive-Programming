#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

int arr[MAXN], sum[MAXN];

int main() {
	int C, N, X;
	scanf("%d %d", &C, &N);
	memset(&arr, 0, sizeof arr);
	for(int i=0; i<N; i++) {
		scanf("%d", &X);
		arr[X+1]++;
		arr[X+1+C]++;
	}
	sum[0] = 0;
	for(int i=1; i<=2*C; i++) {
		sum[i] = arr[i] + sum[i-1];
	}
	bool ok = false;
	int bl = C/N;
	for(int s=1; s<=bl && !ok; s++) {
		ok = true;
		for(int i=s, j; i<=C && ok; i += bl) {
			j = i + bl - 1;
			if (sum[j] - sum[i-1] != 1) ok = false;
		}
	}
	if (ok) printf("S\n");
	else printf("N\n");
	return 0;
}