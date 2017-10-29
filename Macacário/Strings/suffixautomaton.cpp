#include <map>
#include <vector>
#include <queue>
using namespace std;

/*
 * SuffixAutomaton O(n)
 */

struct node {
	int len, link, cnt;
	map<int, int> next;
	node() {
		next.clear();
		len = 0; link = -1; cnt = 1;
	}
};

class SuffixAutomaton {
	vector<node> st;
	int last;
public:
	SuffixAutomaton() { clear(); }
	void clear() {
		st.clear();
		st.push_back(node());
		last = 0;
	}
	void insert(const char *s) {
		for(int i=0; s[i]; i++) extend(s[i]);
	}
	void extend(int c) {
		int cur = st.size();
		st.push_back(node());
		st[cur].len = st[last].len + 1;
		int p;
		for(p = last; p != -1 && !st[p].next.count(c); p = st[p].link) {
			st[p].next[c] = cur;
		}
		if (p == -1) st[cur].link = 0;
		else {
			int q = st[p].next[c];
			if (st[p].len+1 == st[q].len) st[cur].link = q;
			else {
				int clone = st.size();
				st.push_back(node());
				st[clone].len = st[p].len + 1;
				st[clone].next = st[q].next;
				st[clone].link = st[q].link;
				st[clone].cnt = 0;
				while(p != -1 && st[p].next[c] == q) {
					st[p].next[c] = clone;
					p = st[p].link;
				}
				st[q].link = st[cur].link = clone;
			}
		}
		last = cur;
	}
	void computeCnt() {
		vector<int> deg(st.size());
		for(int i=1; i<(int)st.size(); i++)
			deg[st[i].link]++;
		queue<int> q;
		for(int i=1; i<(int)st.size(); i++) {
			if (deg[i] == 0) q.push(i);
		}
		while(!q.empty()) {
			int i = q.front(); q.pop();
			if (i <= 0) continue;
			int j = st[i].link;
			st[j].cnt += st[i].cnt;
			if ((--deg[j]) == 0) q.push(j);
		}
	}
	int nmatches(const char *s) {
		int i, p;
		for(i=0, p=0; s[i]; i++) {
			if (!st[p].next.count(s[i])) return 0;
			p = st[p].next[s[i]];
		}
		return st[p].cnt;
	}
	long long numDifSubstrings() {
		long long ans = 0;
		for(int i=1; i<(int)st.size(); i++) {
			ans += st[i].len - st[st[i].link].len;
		}
		return ans;
	}
	int longestRepeatedSubstring(int times) {
		int ans = 0;
		for(int i=1; i<(int)st.size(); i++) {
			if (st[i].cnt >= times && ans < st[i].len) {
				ans = st[i].len;
			}
		}
		return ans;
	}
	int longestCommonSubstring(const char *s) {
		int cur = 0, len = 0, ans = 0;
		for(int i=0; s[i]; i++) {
			while(cur && !st[cur].next.count(s[i])) {
				cur = st[cur].link;
				len = st[cur].len;
			}
			if (st[cur].next.count(s[i])) {
				cur = st[cur].next[s[i]];
				len++;
			}
			if (ans < len) ans = len;
		}
		return ans;
	}
};

/*
 * SPOJ LCS
 */

#include <cstdio>
#define MAXN 250009

char T[MAXN], P[MAXN];
SuffixAutomaton sa;

int main() {
	scanf(" %s %s", T, P);
	sa.insert(T);
	printf("%d\n", sa.longestCommonSubstring(P));
	return 0;
}