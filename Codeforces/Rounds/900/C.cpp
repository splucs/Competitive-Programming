#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int arr[MAXN], bit[MAXN], N, inc[MAXN], id[MAXN], mx[MAXN];

void update(int i, int k) {
	for(; i <= N; i += (i&-i)) {
		if (bit[i] > 0) bit[i] = N+1;
		else bit[i] += k;
	}
}

int rsq(int i) {
	int sum = 0;
	for(; i; i -= (i&-i)) {
		sum += bit[i];
		if (sum > N) sum = N+1;
	}
	return sum;
}

bool comp(int i, int j) {
	return arr[i] > arr[j];
}

int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
		id[i] = i;
	}
	sort(id+1, id+1+N, comp);
	mx[1] = arr[1];
	inc[arr[1]]--;
	for(int i=2; i<=N; i++) {
		mx[i] = max(arr[i], mx[i-1]);
		if (mx[i] == arr[i]) inc[arr[i]]--;
	}
	for(int it = 1; it <= N; it++) {
		int i = id[it];
		update(i, arr[i]);
		int s = rsq(i-1);
		if (s <= N) inc[s]++;
	}
	int ans = 1;
	for(int i = 1; i <= N; i++) {
		//printf("inc[%d] = %d\n", i, inc[i]);
		if (inc[i] > inc[ans]) ans = i;
	}
	printf("%d\n", ans);
	return 0;
}