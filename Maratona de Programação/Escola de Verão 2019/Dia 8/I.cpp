#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define INF 0x3f3f3f3f
#define MAXN 300009
#define MAXLOGN 22
#define MOD 1000000007
#define EPS 1e-9
#define mset(x, y) memset(&x, y, sizeof x)
#define all(x) x.begin(),x.end()
#define sz(x) int(x.size())
typedef long long ll;

#define M 12

bool isOp(char c) {
	return c == '&' || c == '|' || c == '=' || c == '-' || c == '~';
}

bool isCarac(char c) {
	return (c >= 'A' && c <= 'L') || c == '0' || c == '1';
}

char op[MAXN];
int top;

void handleEquiv(int &n, int pol[]) {
	int ans = 0;
	while(top > 0 && op[top-1] == '=') {
		ans++;
		top--;
	}
	pol[n++] = '=';
	pol[n++] = ans + 1;
}


int paren2polish(char par[], int pol[]) {
	int prec[256];
	prec['('] = 0;
	prec['='] = 1;
	prec['-'] = 2;
	prec['|'] = 3;
	prec['&'] = 4;
	prec['~'] = 5;
	int n = 0;
	top = 0;
	for(int i = 0; par[i]; i++) {
		char c = par[i];
		if (isOp(c)) {
			while(top > 0 && prec[op[top-1]] > prec[c]) {
				pol[n++] = op[--top];
			}
			op[top++] = c;
		}
		else if (c == '(') op[top++] = c;
		else if (c == ')') {
			while(op[top-1] != '(') {
				if (op[top-1] == '=')
					handleEquiv(n, pol);
				else {
					pol[n++] = op[--top];
				}
			}
			top--;
		}
		else if (isCarac(c)) {
			pol[n++] = c;
		}
		else assert(false);
	}
	while(top > 0) {
		if (op[top-1] == '=')
			handleEquiv(n, pol);
		else {
			pol[n++] = op[--top];
		}
	}
	pol[n] = 0;
	return n;
}

typedef bitset<(1<<M)> BS;
vector<int> sons[MAXN];
bitset<(1<<M)> cvalue[M];

void computeCValue() {
	FOR(i, M) {
		cvalue[i].reset();
		FOR(j, (1<<M)) {
			if (j & (1<<i)) cvalue[i][j] = 1;
		}
	}
}

BS value(char c, vector<BS> &sons) {
	if (c == '0') {
		assert(sons.empty());
		BS ans;
		ans.reset();
		return ans;
	}
	if (c == '1') {
		assert(sons.empty());
		BS ans;
		ans.set();
		return ans;
	}
	if (isCarac(c)) {
		assert(sons.empty());
		int i = M-1-(c-'A');
		return cvalue[i];
	}
	if (c == '|') {
		assert(sons.size() == 2u);
		return sons[0]|sons[1];
	}
	if (c == '&') {
		assert(sons.size() == 2u);
		return sons[0]&sons[1];
	}
	if (c == '=') {
		assert(sons.size() >= 2u);
		BS v1 = sons[0];
		BS v0 = ~v1;
		FOR1(i, sz(sons)-1) {
			BS &vi = sons[i];
			v0 &= ~vi;
			v1 &= vi;
		}
		return v0|v1;
	}
	if (c == '-') {
		assert(sons.size() == 2u);
		return (~sons[0])|sons[1];
	}
	if (c == '~') {
		assert(sons.size() == 1u);
		return ~sons[0];
	}
	assert(false);
}

BS bs[MAXN/2];

BS compute(int pol[]) {
	int top = 0;
	for(int i = 0; pol[i]; i++) {
		char c = pol[i];
		vector<BS> sons;
		if (c == '~') {
			sons.pb(bs[--top]);
		}
		else if (c == '=') {
			i++;
			int k = pol[i];
			while(k --> 0) sons.pb(bs[--top]);
		}
		else if (isOp(c)) {
			sons.pb(bs[--top]);
			sons.pb(bs[--top]);
			swap(sons[0], sons[1]);
		}
		bs[top++] = value(c, sons);
		assert(top < MAXN);
	}
	assert(top == 1);
	return bs[--top];
}

vector<string> g[MAXN];
bitset<(1<<(M+1))> st;
vector<int> dep[1<<(M+1)];

void dfs(int u, int l, int r, vector<int> cur, const BS &values) {
	dep[u] = cur;
	if (l == r) {
		st[u] = values[r];
	}
	else {
		int m = (l + r) / 2;
		cur.pb(0);
		dfs(2*u, l, m, cur, values);
		cur.back() = 1;
		dfs(2*u+1, m+1, r, cur, values);
		cur.pop_back();
		st[u] = st[2*u]&st[2*u+1];
		if (st[u]) {
			st[2*u] = st[2*u+1] = 0;
		}
	}
}

int buildNN(const BS &values) {
	st.reset();
	//printf("values: %s\n", values.to_string().c_str());
	dfs(1, 0, (1<<M)-1, vector<int>(), values);
	int f = 0;
	FOR(u, (1<<(M+1))) {
		if (!st[u]) continue;
		int v = ++f;
		FOR(i, sz(dep[u])) {
			string s;
			if (!dep[u][i]) s.pb('~');
			s.pb('A' + i);
			g[v].pb(s);
		}
		FOR(i, sz(dep[u])-1) g[v].pb("0");
		if (g[v].empty()) g[v].pb("~0");
	}
	if (f == 0) {
		f++;
		g[f].pb("0");
	}
	f++;
	char buffer[10];
	FOR1(v, f-1) {
		sprintf(buffer, "%d", v);
		g[f].pb(string(buffer));
		if (v > 1) g[f].pb("~0");
	}
	if (g[f].empty()) g[f].pb("0");
	return f;
}

void parse(char par[]) {
	int n = 0;
	for(int i = 0; par[i]; i++) {
		char c = par[i];
		if (c == '<' || c == '>') continue;
		par[n++] = c;
	}
	par[n] = 0;
}

void printPol(int pol[]) {
	for(int i = 0; pol[i]; i++) {
		printf("%c ", pol[i]);
		if (pol[i] == '=') {
			i++;
			printf("%d ", pol[i]);
		}
	}
	printf("\n");
}

void printTruthTable(BS &values) {
	FOR(i, (1<<M)) {
		printf("value[%2d] = %d\n", i, int(values[i]));
	}
}

char par[MAXN];
int pol[MAXN];

int main() {
	#ifdef ONLINE_JUDGE
	freopen("intelligent.in", "r", stdin);
	freopen("intelligent.out", "w", stdout);
	#endif

	scanf("%s", par);
	parse(par);
	//printf("parsed s: %s\n", par);
	paren2polish(par, pol);
	//printPol(pol);
	computeCValue();
	BS values = compute(pol);
	//printTree(root);
	int f = buildNN(values);
	//printTruthTable(values);
	printf("%d\n", f);
	FOR1(u, f) {
		printf("%u", g[u].size());
		FOR(i, sz(g[u])) printf(" %s", g[u][i].c_str());
		printf("\n");
	}
	return 0;
	// std::cin.tie(NULL); std::ios_base::sync_with_stdio(false);

}