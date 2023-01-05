#include <bits/stdc++.h>
using namespace std;
#define ALFA 30
#define MAXN 1000009
#define INF (1LL<<60)

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
	void insert(char* s) {
		int len = strlen(s);
		node *x = trie, *y;
		for (int i = 0; i < len; i++) {
			s[i] -= 'a' - 1;
			y = x->next[s[i]];
			if (y == NULL || y == trie) {
				x->next[s[i]] = new node(size++);
				x->adj.push_back(s[i]);
			}
			x = x->next[s[i]];
		}
		x->pats.push_back(len);
	}
	vector<ii> match(char *s) {
		node* x = trie;
		int len = strlen(s), sz;
		vector<ii> ans;
		for (int i = 0; i < len; i++) {
			s[i] -= 'a' - 1;
			x = suffix(x, s[i]);
			for (int j = 0; j < (int)x->pats.size(); j++) {
				sz = x->pats[j];
				ans.push_back(ii(i - sz + 1, i));
			}
		}
		return ans;
	}
};

AhoCorasick ac;
typedef long long ll;
int N, M;
ll v[MAXN], dp[MAXN];
char txt[MAXN], P[MAXN];

int main(){	
	freopen("cenzura.in", "r", stdin);
	freopen("cenzura.out", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		
		scanf("%d %s", &N, txt);
		for(int i=0; i<N; i++) {
			scanf("%I64d", &v[i]);
		}
		scanf("%d", &M);
		for(int j=0; j<M; j++) {
			scanf(" %s", P);
			ac.insert(P);
		}
		
		ac.setfails();
		vector<ii> app = ac.match(txt);
		ac.clear();
		sort(app.begin(), app.end());
		
		dp[app.size()] = 0;
		for(int i = ((int)app.size())-1; i>=0; i--) {
			dp[i] = INF;
			int lim = app[i].second, it = i+1;
			//printf("(%d,%d)\n", app[i].first, app[i].second);
			for(int j = app[i].first; j<=lim; j++) {
				while (it<(int)app.size() && app[it].first == j) {
					lim = min(lim, app[it].second);
					it++;
				}
				dp[i] = min(dp[i], v[j] + dp[it]);
			}
		}
		
		printf("%I64d\n", dp[0]);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}