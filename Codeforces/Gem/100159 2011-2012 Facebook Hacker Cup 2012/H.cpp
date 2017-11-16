#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define INF (1LL<<60)

typedef long long ll;
int N, K;
ll X, A, B, M, p, q;
ll aa[MAXN], bb[MAXN], cc[MAXN], dd[MAXN];

struct trapezoid {
	ll a, b, c, d;
} tr[MAXN];

bool comp(trapezoid t1, trapezoid t2) {
	return t1.b < t2.b;
}

inline ll nxt() {
	X = (A*X + B) % M;
	return X;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int cases = 1; cases<=T; cases++) {
		scanf("%d %d %I64d %I64d %I64d %I64d %I64d %I64d", &N, &K, &X, &A, &B, &M, &p, &q);
		A%=M; B%=M; X%=M;
		for(int i=0; i<N; i++) {
			if (i < K) {
				scanf("%I64d %I64d %I64d %I64d", &aa[i], &bb[i], &cc[i], &dd[i]);
			}
			else {
				aa[i] = aa[i-K] + nxt()%(2*p) - p;
				bb[i] = aa[i] + 1 + nxt()%(2*(bb[i%K] - aa[i%K]));
				cc[i] = cc[i-K] + nxt()%(2*q) - q;
				dd[i] = cc[i] + 1 + nxt()%(2*(dd[i%K] - cc[i%K]));
			}
			tr[i].a = aa[i]*1000000 + i;
			tr[i].b = bb[i]*1000000 + i;
			tr[i].c = cc[i]*1000000 + i;
			tr[i].d = dd[i]*1000000 + i;
		}
		sort(tr, tr+N, comp);
		int ans = N+1;
		ll mx=-INF;
		for(int i=0; i<N; i++) {
			//printf("%I64d %I64d %I64d %I64d\n", tr[i].a, tr[i].b, tr[i].c, tr[i].d);
			int cur = 0;
			mx = max(tr[i].d, mx);
			for(int j=i+1; j<N; j++) {
				if (tr[j].c < mx || tr[j].a < tr[i].b) cur++;
			}
			if (cur >= N-i-1) continue;
			//printf("cur[%d] = %d\n", i, cur);
			ans = min(ans, cur);
		}
		printf("Case #%d: %d\n", cases, ans <= N ? ans : -1);
	}
	return 0;
}