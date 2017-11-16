#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

typedef long long ll;
ll arr[MAXN], red[MAXN];
int N;

int main() {
	scanf("%d", &N);
	
	ll chaos = 0;
	for(int i=0; i<N; i++) {
		scanf("%I64d", &arr[i]);
		if (i > 0) {
			chaos += abs(arr[i] - arr[i-1]);
			red[i-1] = abs(arr[i] + arr[i-1]) - abs(arr[i] - arr[i-1]);
		}
	}
	sort(red, red+N-1);
	if (0 < N-1 && red[0] < 0) chaos += red[0];
	if (1 < N-1 && red[1] < 0) chaos += red[1]; 
	printf("%I64d\n", chaos);
	return 0;
}