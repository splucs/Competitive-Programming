/*
 * Huffman Cost - O(nlogn)
 */

#include <queue>
using namespace std;

typedef long long ll;

ll huffman(ll* a, int n) {
	ll ans = 0, u, v;
	priority_queue<ll> pq;
	for(int i=0; i<n; i++) pq.push(-a[i]);
	while(pq.size() > 1) {
		u = -pq.top(); pq.pop();
		v = -pq.top(); pq.pop();
		pq.push(-u-v);
		ans += u + v;
	}
	return ans;
}

/*
 * Codeforces 101128C
 */
#include <cstdio>
#define MAXN 100009

int main() {
	int T, N;
	ll a[MAXN];
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=0; i<N; i++) scanf("%I64d", &a[i]);
		printf("%I64d\n", huffman(a, N));
	}
	return 0;
}