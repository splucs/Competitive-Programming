#include <bits/stdc++.h>
using namespace std;
#define MAXN ((1<<21)+9)
#define FHMSK ((1<<10) - 1)
#define SHMSK (((1<<21) - 1) ^ FHMSK)

typedef long long ll;
int app[MAXN], arr[MAXN], N, M;

bool comp(int a, int b) {
	int pa = __builtin_popcount(a);
	int pb = __builtin_popcount(b);
	if (pa == pb) return a < b;
	return pa < pb;
}

int main() {
	
	scanf("%d %d", &N, &M);
	for(int it=0; it<N; it++) {
		scanf("%d", &arr[it]);
	}
	sort(arr, arr+N, comp);
	
	ll ans = 0;
	for(int it=0, i; it<N; it++) {
		i = arr[it];
		
		for(int j=0; j<=FHMSK; j++) {
			if ((i & j) != j) continue;
			ans += app[(i & SHMSK) ^ j];
		}
		
		for(int j=0; j<=SHMSK; j+=FHMSK+1) {
			if ((i | j) != i) continue;
			app[(i & FHMSK) ^ j]++;
		}
	}
	
	ans = (N*(N-1LL))/2 - ans;
	
	printf("%I64d\n", ans);
	return 0;
}