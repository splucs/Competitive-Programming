#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef long long ll;
int arr[MAXN];
ll pre[MAXN], suf[MAXN];

ll dc(int l, int r) {
	if (l == r) return arr[l] >= 0;
	int m = (l + r) / 2;
	ll ans = dc(l, m) + dc(m+1, r), cursum;
	int offset = (r-l+1)/2 + 1;
	for(int i=0; i<=2*offset; i++) suf[i] = pre[i] = 0;
	cursum = 0;
	for(int i=m; i>=l; i--) {
		cursum += arr[i];
		suf[cursum+offset]++;
	}
	cursum = 0;
	for(int i=m+1; i<=r; i++) {
		cursum += arr[i];
		pre[cursum+offset]++;
	}
	cursum = 0;
	for(int i=0; i<=2*offset; i++) {
		cursum += suf[2*offset-i];
		ans += pre[i]*cursum;
	}
	return ans;
}

int main() {
	int N, X, h;
	scanf("%d %d", &N, &X);
	for(int i=0; i<N; i++) {
		scanf("%d", &h);
		arr[i] = (h >= X ? 1 : -1);
	}
	printf("%lld\n", dc(0, N-1));
	return 0;
}