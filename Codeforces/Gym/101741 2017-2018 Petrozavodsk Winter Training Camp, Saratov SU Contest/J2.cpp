#include <bits/stdc++.h>
#define FOR(x, n) for(int x=0; x<n; x++)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
#define pb push_back
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define MAXN 200009
#define MAXLOGN 18
#define MOD 1000000007
using namespace std;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<int> vi;

int cnt[20], m;
int acum[MAXN][20];

struct state {
	int c[20];
	state() {
		FOR(j, 20) c[j] = 0;
		c[0] = 1;
	}
	void print() {
		FOR(j, m) printf("%d ", c[j]);
		printf("\n");
	}
};

state operator +(state &a, state &b) {
	state c; c.c[0] = 0;
	FOR(i, m)
		if (a.c[i] > 0)
			FOR(j, m) {
				c.c[(i+j)%m] = (c.c[(i+j)%m] + a.c[i]*1ll*b.c[j])%MOD;
			}
	return c;
}

vector<state> acum_mat[20];
int arr[MAXN];

int main() {
	int n, a, b;
	scanf("%d %d", &n, &m);
	FOR1(i, n) {
		scanf("%d", &arr[i]);
		FOR(k, m) {
			acum[i][k] = acum[i-1][k];
		}
		cnt[arr[i]%m]++;
		acum[i][arr[i]%m]++;
	}

	FOR(i, m) {
		state c;
		acum_mat[i].pb(c);

		FOR1(j, cnt[i]) {
			state nc;
			FOR(k, m) nc.c[k] = (c.c[k] + c.c[(k+m-i)%m])%MOD;
			swap(nc, c);
			acum_mat[i].pb(c);
		}
	}

	int q; scanf("%d", &q);
	while (q--) {
		scanf("%d %d", &a, &b);
		a--;

		int t = acum[b][0] - acum[a][0];
		state ans = acum_mat[0][t];

		FOR1(k, m-1) {
			t = acum[b][k] - acum[a][k];
			if (t == 0) continue;
			state nans = ans + acum_mat[k][t];
			swap(nans, ans);
		}
		printf("%d\n", ans.c[0]);
	}
}