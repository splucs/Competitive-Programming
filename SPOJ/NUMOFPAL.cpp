#include <string>
using namespace std;
#define MAXS 1000009
#define ALFA 26

/*
 * Palindrome Tree O(n)
 */

int nxt[MAXS][ALFA], len[MAXS];
int link[MAXS], num[MAXS];
int cnt = 0;

class PalindromicTree {
private:
	string s;
	int suff;
	int root1, root2;
public:
	PalindromicTree() {
		root1 = ++cnt; root2 = ++cnt;
		suff = root2;
		len[root1] = -1; link[root1] = root1;
		len[root2] = 0; link[root2] = root1;
	}
	char reduce(char c) { return c-'a'; }
	int extend(char c) {
		int u = suff;
		int pos = s.size(); s.push_back(c);
		c = reduce(c);
		for(; true; u = link[u]) {
			int st = pos - 1 - len[u];
			if (st >= 0 && s[st] == s[pos]) break;
		}
		if (nxt[u][c]) {
			suff = nxt[u][c];
			return 0;
		}
		int v = suff = ++cnt;
		len[v] = len[u] + 2;
		nxt[u][c] = v;
		if (len[v] == 1) {
			link[v] = root2; num[v] = 1;
			return num[v];
		}
		while (true) {
			u = link[u];
			int st = pos - 1 - len[u];
			if (st >= 0 && s[st] == s[pos]) {
				link[v] = nxt[u][c];
				break;
			}       
		}           
		num[v] = 1 + num[link[v]];
		return num[v];
	}
};

/*
 * SPOJ NUMOFPAL
 */

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