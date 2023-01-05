#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAXN 1000009
#define UNVISITED -1

/*
 * Tarjan SCC O(n)
 */

int num[MAXN], vis[MAXN], comp[MAXN], low[MAXN];
int counter, numSCC;
stack<int> st;
vector<int> adjList[MAXN];

void dfs(int u) {
	low[u] = num[u] = counter++;
	st.push(u); vis[u] = 1;
	for (int j = 0; j < (int)adjList[u].size(); j++) {
		int v = adjList[u][j];
		if (num[v] == UNVISITED) dfs(v);
		if (vis[v]) low[u] = min(low[u], low[v]);
	}
	if (low[u] == num[u]) {
		while (true) {
			int v = st.top(); st.pop();
			vis[v] = 0;
			comp[v] = numSCC;
			if (u == v) break;
		}
		numSCC++;
	}
}

void tarjan(int n) {
	counter = numSCC = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&vis, 0, sizeof vis);
	memset(&low, 0, sizeof low);
	for (int i = 0; i < n; i++) {
		if (num[i] == UNVISITED)
			dfs(i);
	}
}

/*
 * 2-SAT O(n)
 */

bool twosat(bool x[], int n) {
	tarjan(2*n);
	for(int i = 0; i < n; i++) {
		if (comp[2*i] == comp[2*i+1]) return false;
		x[i] = (comp[2*i] > comp[2*i+1]);
	}
	return true;
}

void implies(int u, bool pu, int v, bool pv) {
	adjList[2*u+(pu?1:0)].push_back(2*v+(pv?1:0));
	adjList[2*v+(pv?0:1)].push_back(2*u+(pu?0:1));
}

/*
 * TEST MATRIX
 */

#include <cassert>

bool checked[MAXN];
bool checkdfs(int u, bool x[]) {
	if (checked[u]) return true;
	checked[u] = true;
	printf("  therefore x[%d]=%d\n", u/2, u%2);
	if ((u%2 != 0) != x[u/2]) return false;
	for(int i = 0; i < (int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (!checkdfs(v, x)) return false;
	}
	return true;
}

bool check(bool x[], int n) {
	memset(&checked, false, sizeof checked);
	for(int i = 0; i < n; i++) {
		printf("x[%d]=%d:\n", i, x[i]);
		if (x[i] && !checkdfs(2*i+1, x)) return false;
		if (!x[i] && !checkdfs(2*i, x)) return false;
	}
	return true;
}

bool reached[MAXN];
void reach(int u, int n) {
	if (reached[u]) return;
	reached[u] = true;
	if (u < 2*n) printf(" x[%d]=%d", u/2 + 1, u%2);
	for(int i = 0; i < (int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		reach(v, n);
	}
}

void print(int n) {
	for(int i = 0; i < 2*n; i++) {
		printf("x[%d]=%d ->", i/2 + 1, i%2);
		memset(&reached, false, sizeof reached);
		reach(i, n);
		printf("\n");
	}
}

/*
 * Brazilian ICPC Summer Camp 2019, Group W, Day 2
 * Problem B
 */

vector<int> pref[MAXN];
bool x[MAXN];

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	while(k --> 0) {
		int a, b;
		scanf("%d %d", &a, &b);
		pref[a].push_back(b);
	}
	int cnt = m;
	for(int a = 1; a <= n; a++) {
		int sz = pref[a].size();
		vector<int> pre(sz), suf(sz);
		for(int i = 0; i < sz; i++) {
			pre[i] = cnt++; suf[i] = cnt++;
		}
		for(int i = 0; i < sz; i++) {
			int u = pref[a][i];
			if (i > 0) {
				implies(pre[i], true, pre[i-1], true);
				implies(abs(u)-1, u < 0, pre[i-1], true);
			}
			if (i+1 < sz) {
				implies(suf[i], true, suf[i+1], true);
				implies(abs(u)-1, u < 0, suf[i+1], true);
			}
			implies(pre[i], true, abs(u)-1, u > 0);
			implies(suf[i], true, abs(u)-1, u > 0);
		}
	}
	//print(m);
	if (twosat(x, cnt)) {
		//assert(check(x, cnt));
		vector<int> ans;
		for(int i = 0; i < m; i++) {
			if (x[i]) ans.push_back(i+1);
		}
		printf("%u\n", ans.size());
		for(int i = 0; i < (int)ans.size(); i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	else printf("-1\n");
	return 0;
}
