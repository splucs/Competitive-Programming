#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define ALFA 256
#define MOD 1000000009
#define MAXK 70
#define MAXN 100009

typedef pair<int, int> ii;

struct node {
	node *fail, *next[ALFA];
	vector<char> adj;
	vector<int> pats;
	int nid;
	node(int _nid) {
		fail = NULL;
		nid = _nid;
		memset(&next, 0, sizeof next);
	}
};

class AhoCorasick
{
	//Automaton build
private:
	node *trie;
	map<int, int> sizes;
	int size;
	node *suffix(node *x, char c) {
		while (x != trie && x->next[c] == 0) x = x->fail;
		return (x->next[c] ? x->next[c] : trie);
	}
public:
	AhoCorasick() { trie = new node(0); size = 1; }
	void clear() {
		node *x, *y;
		queue<node*> q; q.push(trie);
		while (!q.empty()) {
			x = q.front(); q.pop();
			for (int i = 0; i < (int)x->adj.size(); i++) {
				y = x->next[x->adj[i]];
				if (y != NULL && y != trie) q.push(y);
			}
			delete x;
		}
		trie = new node(0); size = 1;
	}
	void setfails() {
		queue<node*> q;
		node *x, *y;
		for (int i = 0; i < ALFA; i++) {
			x = trie->next[i];
			if (x != NULL && x != trie) {
				x->fail = trie;
				q.push(x);
			}
		}
		while (!q.empty()) {
			x = q.front(); q.pop();
			for (int i = 0; i < (int)x->adj.size(); i++) {
				y = x->next[x->adj[i]];
				y->fail = suffix(x->fail, x->adj[i]);
				y->pats.insert(y->pats.end(),
					y->fail->pats.begin(), y->fail->pats.end());
				q.push(y);
			}
		}
	}
	void insert(const char* s, int id) {
		int len = strlen(s);
		sizes[id] = len;
		node *x = trie, *y;
		for (int i = 0; i < len; i++) {
			y = x->next[s[i]];
			if (y == NULL || y == trie) {
				x->next[s[i]] = new node(size++);
				x->adj.push_back(s[i]);
			}
			x = x->next[s[i]];
		}
		x->pats.push_back(id);
	}
	vector<ii> match(const char *s) {
		node* x = trie;
		int len = strlen(s), id;
		vector<ii> ans;
		for (int i = 0; i < len; i++) {
			x = suffix(x, s[i]);
			for (int j = 0; j < (int)x->pats.size(); j++) {
				id = x->pats[j];
				ans.push_back(ii(id, i - sizes[id]));
			}
		}
		return ans;
	}

	//Dynamic Programming (size left, appeared, node id)
private:
	int dp[MAXK][MAXK][MAXN];
	inline int nOnes(int mask) {
		int ans = 0;
		while (mask > 0) {
			ans++;
			mask -= (mask & -mask);
		}
		return ans;
	}
	int DP(const int s, const int mask, node* x, const int K) {
		if (x == NULL) return 0;
		if (dp[s][mask][x->nid] >= 0) return dp[s][mask][x->nid];
		int nmask = mask;
		for (int i = 0; i < (int)x->pats.size(); i++) {
			nmask |= (1 << x->pats[i]);
		}
		if (nOnes(nmask) > K) return dp[s][mask][x->nid] = 0;
		if (s == 0) return dp[s][mask][x->nid] = 1;
		int ans = 0;
		for (char c = 'a'; c <= 'z'; c++) {
			ans = (ans + DP(s - 1, nmask, suffix(x, c), K)) % MOD;
		}
		return dp[s][mask][x->nid] = ans;
	}
public:
	int DP(int sz, int K) {
		return DP(sz, 0, trie, K);
	}
	void initDP() {
		for (int i = 0; i < MAXK; i++)
			for (int j = 0; j < MAXK; j++)
				for(int s = 0; s < size; s++)
					dp[i][j][s] = -1;
	}
};
/*
 * SPOJ SUB_PROB
 */

char str[MAXN], in[MAXN];
bool found[MAXN];
int N;
AhoCorasick ac;

int main()
{
	scanf(" %s %d", str, &N);
	for (int i = 0; i < N; i++) {
		scanf(" %s", in);
		ac.insert(in, i);
	}
	ac.setfails();
	vector<ii> ans = ac.match(str);
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