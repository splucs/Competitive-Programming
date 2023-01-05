#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

int arr[MAXN], dif[MAXN];

int main() {
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		arr[0] = 0;
		for(int i=1; i<=N; i++) {
			scanf("%d", &arr[i]);
			dif[i] = arr[i] - arr[i-1];
		}
		int ans = 0;
		for(int i=N; i>0; i-=2) {
			ans ^= dif[i];
		}
		if (ans) printf("TAK\n");
		else printf("NIE\n");
	}
	return 0;
}