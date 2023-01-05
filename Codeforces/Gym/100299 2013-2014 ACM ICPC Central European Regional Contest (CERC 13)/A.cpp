#include <bits/stdc++.h>
using namespace std;
#define MAXN 209
#define MAXM 300009
#define MAXLOGN 20
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

void reduce(int arr[]) {
	map<int, int> r;
	FOR(i, 4) r[arr[i]] = 0;
	int cnt = 0;
	for(auto &pp : r) pp.se = cnt++;
	FOR(i, 4) arr[i] = r[arr[i]];
}

int encode(int per[]) {
	int ans = 0;
	REP(i, 4) ans = (4*ans + per[i]);
	return ans;
}

void decode(int per[], int code) {
	FOR(i, 4) {
		per[i] = code%4;
		code /= 4;
	}
}

int pairi[4] = {0, 2, 0, 1};
int pairj[4] = {1, 3, 2, 3};
int prv[16][309];

void bfs() {
	int per[4] = {0, 1, 2, 3};
	int s = encode(per);
	queue<int> mq, sq;
	mset(prv, -1);
	prv[0][s] = -2;
	mq.push(0);
	sq.push(s);
	while(!mq.empty()) {
		int mask = mq.front(); mq.pop();
		int code = sq.front(); sq.pop();
		decode(per, code);
		FOR(k, 4) {
			int i = pairi[k];
			int j = pairj[k];
			swap(per[i], per[j]);
			int ncode = encode(per);
			int nmask = mask^(1<<k);
			if (prv[nmask][ncode] == -1) {
				prv[nmask][ncode] = k;
				mq.push(nmask);
				sq.push(ncode);
			}
			swap(per[i], per[j]);
		}
	}
}

int n, m;
int A[MAXN][MAXN];
int row[MAXN], col[MAXN];
vector< pair<char, int> > ans;

void fliprow(int i) {
	ans.pb({'R', i+1});
	FOR(j, m/2) {
		swap(A[i][j], A[i][m-j-1]);
	}
}

void flipcol(int j) {
	ans.pb({'C', j+1});
	FOR(i, n/2) {
		swap(A[i][j], A[n-i-1][j]);
	}
}

void fixodd() {
	if (n % 2 != 0 && m > 1 && A[n/2][0] > A[n/2][1])
		fliprow(n/2);
	if (m % 2 != 0 && n > 1 && A[0][m/2] > A[1][m/2])
		flipcol(m/2);
}

void gopath(int mask, int code, int i, int j) {
	int it = n-1-i;
	int jt = m-1-j;
	int per[4];
	while(prv[mask][code] != -2) {
		int k = prv[mask][code];
		decode(per, code);
		if (k == 0) fliprow(i);
		if (k == 1) fliprow(it);
		if (k == 2) flipcol(j);
		if (k == 3) flipcol(jt);
		swap(per[pairi[k]], per[pairj[k]]);
		mask ^= (1<<k);
		code = encode(per);
	}
}

vector< bitset<MAXN> > equations;
vector<int> val;
bitset<MAXN> sol;

void processequations() {
	int per[4];
	equations.clear();
	val.clear();
	FOR(i, n/2) FOR(j, m/2) {
		int it = n-1-i;
		int jt = m-1-j;
		per[0] = A[i][j];
		per[1] = A[i][jt];
		per[2] = A[it][j];
		per[3] = A[it][jt];
		reduce(per);
		int code = encode(per);
		bitset<MAXN> eq;
		eq[row[i]] = 1;
		eq[row[it]] = 1;
		eq[col[j]] = 1;
		eq[col[jt]] = 1;
		equations.pb(eq);
		if (prv[0][code] == -1) val.pb(1);
		else val.pb(0);
	}
}

bool gauss() {
	int cnt = 0;
	FOR(j, MAXN) {
		int i;
		for(i = cnt; i < sz(equations); i++) {
			if (equations[i][j]) break;
		}
		if (i == sz(equations)) continue;
		swap(equations[i], equations[cnt]);
		swap(val[i], val[cnt]);
		i = cnt;
		cnt++;
		FOR(k, sz(equations)) {
			if (i == k || !equations[k][j]) continue;
			equations[k] ^= equations[i];
			val[k] ^= val[i];
		}
	}
	sol.reset();
	FOR(i, sz(equations)) {
		int acum = val[i];
		FOR(j, MAXN) {
			if (equations[i][j]) {
				sol[j] = acum;
				acum ^= sol[j];
			}
		}
	}
	FOR(i, sz(equations)) {
		int acum = 0;
		FOR(j, MAXN) {
			if (equations[i][j]) acum ^= sol[j];
		}
		if (acum != val[i]) {
			return false;
		}
	}
	return true;
}

void applysol() {
	FOR(i, n) {
		if (sol[row[i]]) fliprow(i);
	}
	FOR(j, m) {
		if (sol[col[j]]) flipcol(j);
	}
}

bool solve() {
	int per[4];
	FOR(i, n/2) FOR(j, m/2) {
		int it = n-1-i;
		int jt = m-1-j;
		per[0] = A[i][j];
		per[1] = A[i][jt];
		per[2] = A[it][j];
		per[3] = A[it][jt];
		reduce(per);
		int code = encode(per);
		if (prv[0][code] == -1) {
			return false;
		}
		gopath(0, code, i, j);
	}
	return true;
}

bool check() {
	int cnt = 0;
	FOR(i, n) FOR(j, m) {
		if (A[i][j] != ++cnt) {
			return false;
		}
	}
	return true;
}

bool go() {
	int cnt = 0;
	FOR(i, n) row[i] = cnt++;
	FOR(j, m) col[j] = cnt++;
	ans.clear();
	fixodd();
	processequations();
	if (!gauss()) return false;
	applysol();
	if (!solve()) return false;
	return check();
}

int main() {
	bfs();

	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d %d", &m, &n);
		FOR(i, n) FOR(j, m) scanf("%d", &A[i][j]);
		if (go()) {
			printf("POSSIBLE %u", ans.size());
			for(auto pp : ans) printf(" %c%d", pp.fi, pp.se);
			printf("\n");
		}
		else printf("IMPOSSIBLE\n");
	}
	return 0;
}