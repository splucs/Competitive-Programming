#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009

int N, arr[MAXN];
typedef long long ll;
ll K;

int main() {
	scanf("%d %I64d", &N, &K);
	int last = 0;
	int ans = -1;
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
		if (i-last-(last==0?1:0) >= K && ans == -1) {
			ans = last;
		}
		if (arr[i] > arr[last]) {
			last = i;
		}
	}
	if (ans == -1) ans = last;
	printf("%d\n", arr[ans]);
	return 0;
}