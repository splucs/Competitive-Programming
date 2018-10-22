#include <bits/stdc++.h>
#define MAXN 5009
#define ALFA 26
#define FOR(x, n) for(int x=0; x<n; x++)
#define REP(x, n) for(int x=n-1; x>=0; x--)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define REP1(x, n) for(int x=n; x>0; x--)
#define all(x) x.begin(), x.end()
#define sz(x) (int (x.size()) )
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;

bool isOp(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isCarac(char c) {
	return (c >= 'a' && c <= 'z');
}

void par2pol(char par[], char pol[]) {
	map<char, int> prec;
	prec['('] = 0;
	prec['+'] = prec['-'] = 1;
	prec['*'] = prec['/'] = 2;
	prec['^'] = 3;
	int len = 0;
	stack<char> op;
	for(int i = 0; par[i]; i++) {
		char c = par[i];
		//printf("c = %c\n", c);
		if (isOp(c)) {
			while(!op.empty() && prec[op.top()] >= prec[c]) {
				if (op.top() == '^' && c == '^') break;
				pol[len++] = op.top(); op.pop();
			}
			op.push(c);
		}
		else if (c == '(') op.push(c);
		else if (c == ')') {
			for(; op.top() != '('; op.pop()) {
				pol[len++] = op.top();
			}
			op.pop();
		}
		else if (isCarac(c)) pol[len++] = c;
	}
	for(; !op.empty(); op.pop()) {
		pol[len++] = op.top();
	}
	pol[len] = 0;
}

int nds = 0, ls[MAXN], rs[MAXN];
char val[MAXN];

void pol2tree(char pol[], int &root) {
	int len = strlen(pol);
	stack<int> nodes;
	FOR(i, len) {
		char c = pol[i];
		int u = ++nds;
		val[u] = c;
		if (isOp(c)) {
			rs[u] = nodes.top();
			nodes.pop();
			ls[u] = nodes.top();
			nodes.pop();
		}
		nodes.push(u);
	}
	root = nodes.top();
}

char ans[MAXN][MAXN];
int maxh = 0;

void dfs(int u, int i, int &j) {
	if (u == 0) return;

	dfs(ls[u], i+2, j);

	maxh = max(maxh, i);
	j++;
	if (!isCarac(val[u])) {
		ans[i][j] = '[';
		j++;
	}
	ans[i][j] = val[u];
	ans[i-1][j] = '|';
	ans[i-2][j] = '.';
	j++;
	if (!isCarac(val[u])) {
		ans[i][j] = ']';
		j++;
	}

	dfs(rs[u], i+2, j);
}

char par[MAXN], pol[MAXN];

int main() {
	#ifdef ONLINE_JUDGE
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	#endif

	scanf("%s", par);
	par2pol(par, pol);
	//printf("polish: %s\n", pol);

	int root;
	pol2tree(pol, root);

	mset(ans, ' ');
	int i = 2, sz = 0;
	dfs(root, i, sz);

	for(int i = 2; i <= maxh; i++) {
		ans[i][sz] = 0;
		bool dash = false;
		FOR(j, sz) {
			if (ans[i][j] == '[' || ans[i][j] == ']' || ans[i][j] == '.')
				dash = !dash;
			if (ans[i][j] == ' ' && dash) ans[i][j] = '-';
		}
		printf("%s\n", ans[i]+1);
	}

	return 0;
}