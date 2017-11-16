#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

int N, arr[MAXN];

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr+N);
	int ans = 1, pr = arr[N-1];
	for(int i=0; i+1<N; i++) {
		if (arr[i] <= pr) {
			pr -= arr[i];
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}