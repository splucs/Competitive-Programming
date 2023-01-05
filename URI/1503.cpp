#include <string>
using namespace std;
#define MAXS 600009
#define ALFA 26

/*
 * Palindrome Tree O(n)
 */

int nxt[MAXS][ALFA], len[MAXS];
int link[MAXS], num[MAXS];
int cnt = 0; //limpar nxt se resetar cnt

class PalindromicTree {
private:
	string s;
	int suff;
	char reduce(char c) { return c-'a'; }
	int getlink(int u, int pos) {
		for(; true; u = link[u]) {
			int st = pos - 1 - len[u];
			if (st >= 0 && s[st] == s[pos])
				return u;
		}
	}
public:
	int root1, root2;
	PalindromicTree() {
		root1 = ++cnt; root2 = ++cnt;
		suff = root2;
		len[root1] = -1; link[root1] = root1;
		len[root2] = 0; link[root2] = root1;
	}
	int extend(char c) {
		int pos = s.size(); s.push_back(c);
		c = reduce(c);
		int u = getlink(suff, pos);
		if (nxt[u][c]) {
			suff = nxt[u][c];
			return 0;
		}
		int v = suff = ++cnt;
		len[v] = len[u] + 2;
		nxt[u][c] = v;
		if (len[v] == 1) {
			link[v] = root2;
			return num[v] = 1;
		}
		u = getlink(link[u], pos);
		link[v] = nxt[u][c];           
		return num[v] = 1 + num[link[v]];
	}
};

/*
 * SPOJ NUMOFPAL
 */
 /*
#include <cstdio>
#include <cstring>
#define MAXN 1000009
char s[MAXN];

int main() {
	while(scanf(" %s", s) != EOF) {
		int len = strlen(s);
		PalindromicTree pt;
		long long ans = 0;
		for (int i = 0; i < len; i++) {
			ans += pt.extend(s[i]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
*/

/*
 * URI 1503
 */

#include <cstdio>
#include <cstring>
#include <vector>
#define MAXN 50009

int n, ans;
PalindromicTree pt[10];

void dfs(vector<int> &u) {
	if (len[u[0]] > ans) ans = len[u[0]];
	vector<int> v(n);
	for(char c = 0; c < ALFA; c++) {
		bool ok = true;
		for(int i = 0; i < n && ok; i++) {
			v[i] = nxt[u[i]][c];
			if (!nxt[u[i]][c]) ok = false;
		}
		if (!ok) continue;
		dfs(v);
	}
}

char s[MAXN];

int main() {
	while(scanf("%d", &n) != EOF) {
		cnt = 0;
		vector<int> root1(n), root2(n);
		memset(&nxt, 0, sizeof nxt);
		for(int i = 0; i < n; i++) {
			pt[i] = PalindromicTree();
			root1[i] = pt[i].root1;
			root2[i] = pt[i].root2;
			scanf(" %s", s);
			int len = strlen(s);
			for(int j = 0; j < len; j++) {
				pt[i].extend(s[j]);
			}
		}
		ans = 0;
		dfs(root1);
		dfs(root2);
		printf("%d\n", ans);
	}
	return 0;
}