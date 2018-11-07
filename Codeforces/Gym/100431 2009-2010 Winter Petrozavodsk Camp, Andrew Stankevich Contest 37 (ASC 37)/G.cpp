#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXLOGN 20
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef vector<int> vi;

int P[MAXN][MAXLOGN];
int back[MAXN], len[MAXN], val[MAXN];
int latest, nds;

int la(int u, int i) {
	FOR(j, MAXLOGN) {
		if (i & (1<<j)) u = P[u][j];
	}
	return u;
}

void push(int ver, int x) {
	int &u = back[++latest];
	u = ++nds;
	val[u] = x;
	len[latest] = len[ver] + 1;
	if (len[latest] == 1) P[u][0] = u;
	else P[u][0] = back[ver];
	FOR1(i, MAXLOGN-1) {
		P[u][i] = P[P[u][i-1]][i-1];
	}
}

int pop(int ver) {
	int &u = back[++latest];
	u = back[ver];
	len[latest] = len[ver] - 1;
	return val[la(u, len[latest])];
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	#endif

	int n;
	while(scanf("%d", &n) != EOF) {
		latest = nds = 0;
		int op, ver, x;
		while(n --> 0) {
			scanf("%d", &op);
			if (op == 1) {
				scanf("%d %d", &ver, &x);
				push(ver, x);
			}
			if (op == -1) {
				scanf("%d", &ver);
				printf("%d\n", pop(ver));
			}
		}
	}
	return 0;
}