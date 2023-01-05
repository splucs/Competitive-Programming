#include <cstring>
#include <queue>
using namespace std;
#define MAXS 500009 // 2*MAXN
#define ALFA 26

/*
 * SuffixAutomaton O(n)
 */

class SuffixAutomaton {
	int len[MAXS], link[MAXS], cnt[MAXS];
	int nxt[MAXS][ALFA], sz, last, root;
	long long ans;
	int newnode() {
		int x = ++sz;
		len[x] = 0; link[x] = -1; cnt[x] = 1;
		for(int c = 0; c < ALFA; c++) nxt[x][c] = 0;
		return x;
	}
	inline int reduce(char c) { return c - 'a'; }
public:
	SuffixAutomaton() { clear(); }
	void clear() {
		sz = ans = 0;
		root = last = newnode();
	}
	void insert(const char *s) {
		for(int i = 0; s[i]; i++) extend(reduce(s[i]));
	}
	void extend(int c) {
		int cur = newnode(), p;
		len[cur] = len[last] + 1;
		ans += len[cur];
		for(p = last; p != -1 && !nxt[p][c]; p = link[p]) {
			nxt[p][c] = cur;
		}
		if (p == -1) link[cur] = root;
		else {
			int q = nxt[p][c];
			if (len[p] + 1 == len[q]) link[cur] = q;
			else {
				int clone = newnode();
				len[clone] = len[p] + 1;
				ans += len[clone];
				for(int i = 0; i < ALFA; i++)
					nxt[clone][i] = nxt[q][i];
				link[clone] = link[q];
				cnt[clone] = 0;
				while(p != -1 && nxt[p][c] == q) {
					nxt[p][c] = clone;
					p = link[p];
				}
				ans += len[link[q]];
				link[q] = link[cur] = clone;
				ans -= len[link[clone]];
				ans -= len[link[q]];
			}
		}
		ans -= len[link[cur]];
		last = cur;
	}
	bool contains(const char *s) {
		for(int i = 0, p = root; s[i]; i++) {
			int c = reduce(s[i]);
			if (!nxt[p][c]) return false;
			p = nxt[p][c];
		}
		return true;
	}
	long long numDifSubstrings() {
		return ans;
	}
	int longestCommonSubstring(const char *s) {
		int cur = root, curlen = 0, ans = 0;
		for(int i = 0; s[i]; i++) {
			int c = reduce(s[i]);
			while(cur != root && !nxt[cur][c]) {
				cur = link[cur];
				curlen = len[cur];
			}
			if (nxt[cur][c]) {
				cur = nxt[cur][c];
				curlen++;
			}
			if (ans < curlen) ans = curlen;
		}
		return ans;
	}
private:
	int deg[MAXS];
public:
	void computeCnt() {
		fill(deg, deg+sz+1, 0);
		for(int i=root+1; i<=sz; i++)
			deg[link[i]]++;
		queue<int> q;
		for(int i=root+1; i<=sz; i++)
			if (deg[i] == 0) q.push(i);
		while(!q.empty()) {
			int i = q.front(); q.pop();
			if (i <= root) continue;
			int j = link[i];
			cnt[j] += cnt[i];
			if ((--deg[j]) == 0) q.push(j);
		}
	}
	int nmatches(const char *s) {
		int p = root;
		for(int i = 0; s[i]; i++) {
			int c = reduce(s[i]);
			if (!nxt[p][c]) return 0;
			p = nxt[p][c];
		}
		return cnt[p];
	}
	int longestRepeatedSubstring(int times) {
		int ans = 0;
		for(int i=root; i<=sz; i++) {
			if (cnt[i] >= times && ans < len[i]) {
				ans = len[i];
			}
		}
		return ans;
	}
};

/*
 * URI 1530
 */

#include <cstdio>
#define MAXN 250009

char s[MAXN];
SuffixAutomaton sa;

int main() {
	while(scanf(" %s", s) != EOF) {
		int n = strlen(s);
		sa.clear();
		for(int i = 0; i < n; i++) {
			if (s[i] == '?') printf("%lld\n", sa.numDifSubstrings());
			else sa.extend(s[i] - 'a');
		}
	}
	return 0;
}