#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define MAXS 10000009

int N, arr[MAXN], aux[MAXN], it;
char str[MAXS];

void mergesort(const int lo, const int hi) {
	int n = hi-lo+1;
	if (n <= 1) return;
	int mid = lo+n/2;
	mergesort(lo, mid-1);
	mergesort(mid, hi);
	
	int i = lo;
	int j = mid;
	int k = i;
	while(i < mid && j <= hi) {
		if (str[it] == '1') {
			it++;
			aux[k++] = arr[i++];
		}
		else {
			it++;
			aux[k++] = arr[j++];
		}
	}
	while(i < mid) aux[k++] = arr[i++];
	while(j <= hi) aux[k++] = arr[j++];
	for(k=lo; k<=hi; k++) arr[k] = aux[k];
}

int main() {
	int T;
	scanf("%d", &T);
	for(int t = 1; t<=T; t++) {
		scanf("%d %s", &N, str);
		for(int i=1; i<=N; i++) {
			arr[i] = i;
		}
		it = 0;
		mergesort(1, N);
		for(int i=1; i<=N; i++) {
			aux[arr[i]] = i;
		}
		/*for(int i=1; i<=N; i++) {
			printf("%d ", aux[i]);
		}
		printf("\n");*/
		
		int ans = 1;
		for(int i=1; i<=N; i++) {
			ans = (31*ans + aux[i]) % 1000003;
		}
		printf("Case #%d: %d\n", t, ans);
	}
	return 0;
}