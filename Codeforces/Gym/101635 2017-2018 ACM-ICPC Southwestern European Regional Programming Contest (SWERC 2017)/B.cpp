#include <bits/stdc++.h>
#define MAXN 2009
#define MAXM 100009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

struct query {
	int id;
	int dx, dy;
	int ans;
};

query qrs[MAXM];

bool compdx(query a, query b) {
	return a.dx > b.dx;
}

bool compid(query a, query b) {
	return a.id < b.id;
}

int n, m;

bool valid(int i, int j) {
	return i >= 1 && j >= 1 && i <= n && j <= m;
}

int dx[MAXN][MAXN], dy[MAXN][MAXN];
bool field[MAXN][MAXN];
bool active[MAXN][MAXN];

int ang[MAXN], lin[MAXN];

void update(int i, int k, int bit[]) {
	for(; i < MAXN; i += (i&-i)) bit[i] += k;
}

int rsq(int i, int bit[]) {
	int ans = 0;
	for(; i; i -= (i&-i)) ans += bit[i];
	return ans;
}

int rsq(int i, int j, int bit[]) {
	return rsq(j, bit) - rsq(i-1, bit);
}

void increase(int i) {
	update(i, 1, lin);
	update(i, i, ang);
}

void decrease(int i) {
	update(i, -1, lin);
	update(i, -i, ang);
}

int count(int i) {
	return rsq(i, MAXN-1, ang) - (i-1)*rsq(i, MAXN-1, lin);
}

ii par[MAXN][MAXN];
void initUF() {
	FOR1(i, n) FOR1(j, m) {
		par[i][j] = {i, j};
	}
}

ii find(int i, int j) {
	if (par[i][j] == ii(i, j)) return {i, j};
	return par[i][j] = find(par[i][j].fi, par[i][j].se);
}

void unite(int i1, int j1, int i2, int j2) {
	if (!valid(i1, j1) || !valid(i2, j2)) return;
	if (!active[i1][j1] || !active[i2][j2]) return;
	ii f1 = find(i1, j1);
	ii f2 = find(i2, j2);
	par[f1.fi][f1.se] = f2;
	decrease(dy[f2.fi][f2.se]);
	decrease(dy[f1.fi][f1.se]);
	dy[f2.fi][f2.se] += dy[f1.fi][f1.se];
	increase(dy[f2.fi][f2.se]);
}

void activate(int i, int j) {
	active[i][j] = true;
	dy[i][j] = 1;
	increase(dy[i][j]);
	unite(i, j, i, j+1);
	unite(i, j, i, j-1);
}

int main() {
	int k, q;
	scanf("%d %d %d %d", &n, &m, &k, &q);
	initUF();
	while(k --> 0) {
		int i1, i2, j1, j2;
		scanf("%d %d %d %d", &i1, &i2, &j1, &j2);
		i1++; j1++;
		for(int i = i1; i <= i2; i++) for(int j = j1; j <= j2; j++) {
			field[i][j] = true;
		}
	}
	priority_queue< pair<int,ii> > pq;
	FOR1(i, n) {
		FOR1(j, m) {
			if (!field[i][j]) dx[i][j] = 1 + dx[i-1][j];
			pq.push({dx[i][j], {i,j}});
			//printf("%d ", dx[i][j]);
		}
		//printf("\n");
	}
	FOR(qt, q) {
		scanf("%d %d", &qrs[qt].dx, &qrs[qt].dy);
		qrs[qt].id = qt;
	}
	sort(qrs, qrs+q, compdx);
	FOR(qt, q) {
		query &qr = qrs[qt];

		while(!pq.empty() && pq.top().fi >= qr.dx) {
			activate(pq.top().se.fi, pq.top().se.se);
			pq.pop();
		}
		qr.ans = count(qr.dy);
	}
	sort(qrs, qrs+q, compid);
	FOR(qt, q) printf("%d\n", qrs[qt].ans);
	return 0;
}