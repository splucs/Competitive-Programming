#include <map>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

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
	void print() {
		for(int i=0; i<(int)st.size(); i++) {
			printf("state %d: link = %d, len = %d, cnt = %d\n", i, st[i].link, st[i].len, st[i].cnt);
			for(map<int, int>::iterator it = st[i].next.begin(); it != st[i].next.end(); it++)
				printf("(%c,%d) ", it->first, it->second);
			printf("\n");
		}
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
};

#define MAXN 1009

char str[MAXN];
SuffixAutomaton sa;

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		scanf(" %s", str);
		sa.clear();
		sa.insert(str);
		printf("%lld\n", sa.numDifSubstrings());
	}
	return 0;
}