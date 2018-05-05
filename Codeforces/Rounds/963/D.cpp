#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

struct node {
	node *fail, *next[ALFA];
	vector<char> adj;
	vector<int> pats;
	int nid;
	node(vector<node*> & st) {
		fail = NULL;
		nid = st.size();
		memset(&next, 0, sizeof next);
		st.push_back(this);
	}
};

class AhoCorasick {
	//Automaton build
private:
	node *trie;
	map<int, int> sizes;
	vector<node*> st;
	node *suffix(node *x, char c) {
		while (x != trie && x->next[c] == 0) x = x->fail;
		return (x->next[c] ? x->next[c] : trie);
	}
public:
	AhoCorasick() { clear(); }
	void clear() {
		for(int i=0; i<(int)st.size(); i++) delete st[i];
		st.clear();
		sizes.clear();
		trie = new node(st);
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
				x->next[s[i]] = new node(st);
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
};

int main() {
	
}