#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF (1LL << 60)

typedef long long ll;
ll a[MAXN], mina;
int N, K, nxt[MAXN];

int getnxt(int i) {
	if (i == 0 || a[i] > mina) return i;
	else return nxt[i] = getnxt(nxt[i]);
}

int main() {
	scanf("%d %d", &N, &K);
	mina = INF;
	for(int i=1; i<=N; i++) {
		scanf("%I64d", &a[i]);
		mina = min(mina, a[i]);
		nxt[i] = i-1;
	}
	a[0] = 0;
	nxt[0] = -1;
	ll cursum = 0;
	for(int i=1; i<K; i++) {
		cursum += a[i];
	}
	bool possible = true;
	ll ans = 0;
	for(int i=K; i<=N && possible; i++) {
		cursum += a[i];
		cursum -= a[i-K];
		while (cursum >= 0) {
			int j = getnxt(i);
			if (j == 0) {
				possible = false;
				break;
			}
			ll dt = cursum+1;
			if (a[j] - dt < mina) dt = a[j] - mina;
			a[j] -= dt;
			cursum -= dt;
			ans += dt;
		}
	}
	printf("%I64d\n", ans);
	for(int i=1; i<=N; i++) {
		printf("%I64d ", a[i]);
	}
	printf("\n");
	return 0;
}