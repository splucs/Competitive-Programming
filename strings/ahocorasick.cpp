#include <vector>
#include <cstdio>
#include <queue>
#include <cstring>
#include <set>
#include <map>
#define MAXN 1000009
using namespace std;

struct STnode {
	map<char, int> sons;
	char carac;
	int fail; int parent;
	int depth;
	vector<int> ids;
	STnode(int p, char c, int d) {
		fail = -1;
		parent = p; carac = c;
		depth = d;
	}
};

void action(int pos, int id) {
	printf("found %d at pos %d\n", id, pos);
}

class SuffixTrie {
private:
	vector<STnode> st;
	char* str;
	void build(int i, int n, int id) {
		if (str[i] == '\0') {
			st[n].ids.push_back(id); return;
		}
		if (!st[n].sons.count(str[i])) {
			st[n].sons[str[i]] = (int)st.size();
			st.push_back(STnode(n, str[i], st[n].depth + 1));
		}
		build(i + 1, st[n].sons[str[i]], id);
	}
	bool find(int i, int n) {
		if (str[i] == '\0') return true;
		if (!st[n].sons.count(str[i])) return false;
		return find(i + 1, st[n].sons[str[i]]);
	}
	int callids(int pos, int p) {
		for (int i = 0; i<(int)st[p].ids.size(); i++) {
			action(pos, st[p].ids[i]);
		}
		return (int)st[p].ids.size();
	}
	int match(int i, int n) {
		int ans = 0;
		if (str[i] == '\0' || st[n].sons.count(str[i])) {
			int p = n;
			while (p != 0) {
				ans += callids(i - st[p].depth - 1, p);
				p = st[p].fail;
			}
			if (str[i] == '\0') return ans;
			ans += match(i + 1, st[n].sons[str[i]]);
		}
		else if (n != 0) {
			ans += callids(i - st[n].depth - 1, n);
			ans += match(i, st[n].fail);
		}
		else ans += match(i + 1, 0);
		return ans;
	}
public:
	SuffixTrie() { clear(); }
	void push(char* s, int id) {
		str = s;
		build(0, 0, id);
	}
	void clear() {
		st.clear();
		st.push_back(STnode(0, '\0', -1));
	}
	bool count(char* s) {
		str = s;
		return find(0, 0);
	}
	void setfails() {
		st[0].fail = 0;
		queue<int> q; q.push(0);
		map<char, int>::iterator it;
		int n, p; char c;
		while (!q.empty()) {
			n = q.front(); q.pop(); c = st[n].carac;
			for (it = st[n].sons.begin(); it != st[n].sons.end(); it++) {
				q.push(it->second);
			}
			p = st[st[n].parent].fail;
			while (p != 0 && !st[p].sons.count(c)) p = st[p].fail;
			st[n].fail = (p != st[n].parent && st[p].sons.count(c) ? st[p].sons[c] : 0);
		}
	}
	int ahoCorasick(char* s) {
		str = s;
		return match(0, 0);
	}
};