#include <cstring>
#include <queue>
#include <vector>
using namespace std;
#define ALFA 26
#define MAXS 100009

typedef pair<int, int> ii;

int nxt[MAXS][ALFA], fail[MAXS], cnt = 0;
vector<ii> pats[MAXS];

class AhoCorasick {
private:
	int root;
	int suffix(int x, int c) {
		while (x != root && nxt[x][c] == 0) x = fail[x];
		return nxt[x][c] ? nxt[x][c] : root;
	}
	int newnode() {
		int x = ++cnt;
		fail[x] = 0; pats[x].clear();
		for(int c = 0; c < ALFA; c++) nxt[x][c] = 0;
		return x;
	}
	inline int reduce(char c) { return c - 'a'; }
public:
	AhoCorasick() { root = newnode(); }
	void setfails() {
		queue<int> q;
		int x, y;
		q.push(root);
		while (!q.empty()) {
			x = q.front(); q.pop();
			for (int c = 0; c < ALFA; c++) {
				y = nxt[x][c];
				if (y == 0) continue;
				fail[y] = x == root ? x : suffix(fail[x], c);
				pats[y].insert(pats[y].end(), 
					pats[fail[y]].begin(), pats[fail[y]].end());
				q.push(y);
			}
		}
	}
	void insert(const char* s, int id) {
		int len = strlen(s);
		int x = root;
		for (int i = 0; i < len; i++) {
			int & y = nxt[x][reduce(s[i])];
			if (y == 0 || y == root) {
				y = newnode();
			}
			x = y;
		}
		pats[x].push_back(ii(id, len));
	}
	vector<ii> match(const char *s) { //(id, pos)
		int x = root;
		vector<ii> ans;
		for (int i = 0; s[i]; i++) {
			x = suffix(x, reduce(s[i]));
			for(int j = 0; j < (int)pats[x].size(); j++) {
				ii cur = pats[x][j];
				ans.push_back(ii(cur.first, i - cur.second + 1));
			}
		}
		return ans;
	}
};

/*
 * SPOJ SUB_PROB
 */

#include <cstdio>
#define MAXN 100009

char str[MAXN], in[MAXN];
bool found[MAXN];
int N;
AhoCorasick aho;

int main() {
	scanf(" %s %d", str, &N);
	for (int i = 0; i < N; i++) {
		scanf(" %s", in);
		aho.insert(in, i);
	}
	aho.setfails();
	vector<ii> ans = aho.match(str);
	memset(&found, false, sizeof found);
	for (int i = 0; i < (int)ans.size(); i++) {
		found[ans[i].first] = true;
	}
	for (int i = 0; i < N; i++) {
		if (found[i]) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}