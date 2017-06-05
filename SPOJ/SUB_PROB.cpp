#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define ALFA 256
#define MOD 1000000009
#define MAXK 59
#define MAXN 100009
typedef pair<int, int> ii;

struct node {
	node *fail, *next[ALFA];
	vector<char> adj;
	vector<int> pats;
	node() {
		fail = NULL;
		memset(&next, 0, sizeof next);
		//for(int i=0; i<ALFA; i++) next[i] = NULL;
	}
};

class AhoCorasick
{
//Automaton build
private:
	node *trie;
	map<int, int> sizes;
	node *suffix(node *x, char c) {
		while(x != trie && x->next[c] == 0) x = x->fail;
		return x->next[c];
	}
public:
	AhoCorasick() { trie = new node(); }
	void setfails() {
		queue<node*> q;
		node *x, *y;
		for(int i = 0; i < ALFA; i++) {
			x = trie->next[i];
			if(x != NULL && x != trie) {
				x->fail = trie;
                q.push(x);
			}
            else trie->next[i] = trie;
        }
        while(!q.empty()) {
			x = q.front(); q.pop();
			for(int i = 0; i < (int)x->adj.size(); i++) {
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
		for(int i = 0; i < len; i++) {
			y = x->next[s[i]];
			if(y == NULL || y == trie) {
				x->next[s[i]] = new node();
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

//Dynamic Programming (size left, allowed left, node)
private:
	map<node*, int> dp[MAXK][MAXK];
	int DP(int s, int l, node* x) {
		if (dp[s][l].count(x)) return dp[s][l][x];
		if (x == NULL || x->pats.size() > l) return dp[s][l][x] = 0;
		if (s == 0) return dp[s][l][x] = 1;
		int ans = 0;
		for (char c = 'a'; c <= 'z'; c++) {
			ans = (ans + DP(s - 1, l - x->pats.size(), suffix(x, c))) % MOD;
		}
		return dp[s][l][x] = ans;
	}
public:
	int DP(int sz, int lim) {
		return DP(sz, lim, trie);
	}
	void initDP() {
		for (int i = 0; i < MAXK; i++)
			for (int j = 0; j < MAXK; j++)
				dp[i][j].clear();
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