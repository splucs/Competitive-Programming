#include <bits/stdc++.h>
using namespace std;
#define ALFA 256
#define MAXN 35000
#define INF (1<<30)

typedef pair<int, int> ii;

struct node {
	node *fail, *next[ALFA];
	vector<char> adj;
	int mask;
	bool good;
	char c;
	node(char _c) {
		fail = NULL;
		good = false;
		mask = 0;
		c = _c;
		memset(&next, 0, sizeof next);
	}
};

class AhoCorasick
{
	//Automaton build
private:
	node *trie;
	node *suffix(node *x, char c) {
		while (x != trie && x->next[c] == 0) x = x->fail;
		return (x->next[c] ? x->next[c] : trie);
	}
public:
	AhoCorasick() { trie = new node('$'); }
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
				y->good = y->good || y->fail->good;
				y->mask |= y->fail->mask;
				q.push(y);
			}
		}
	}
	void insert(const char* s, int mask, bool good) {
		int len = strlen(s);
		node *x = trie, *y;
		for (int i = 0; i < len; i++) {
			y = x->next[s[i]];
			if (y == NULL || y == trie) {
				x->next[s[i]] = new node(s[i]);
				x->adj.push_back(s[i]);
			}
			x = x->next[s[i]];
		}
		x->good = x->good || good;
		x->mask |= mask;
	}

	//Dynamic Programming
private:
	map<node*, int> dp[MAXN];
	map<node*, char> A[MAXN];
	int DP(const int mask, node* x, const int fullmask) {
		if (dp[mask].count(x)) return dp[mask][x];
		
		if (x==NULL || x->good){
			A[mask][x] = '$';
			return dp[mask][x] = INF;
		}
		int nmask = mask | x->mask;
		if (nmask == fullmask){
			A[mask][x] = '$';
			return dp[mask][x] = 0;
		}
		
		int ans = INF, nans;
		char next = '$';
		dp[mask][x] = INF;
		A[mask][x] = '$';
		for (char c = 'a'; c <= 'j'; c++) {
			nans = DP(nmask, suffix(x, c), fullmask);
			if(ans > 1 + nans){
				ans = 1 + nans;
				next = c;
			}
		}
		A[mask][x] = next;
		return dp[mask][x] = ans;
	}
public:
	int DP(int N) {
		return DP(0, trie, (1<<N)-1);
	}
	void initDP() {
		for (int i = 0; i < MAXN; i++)
			dp[i].clear(), A[i].clear();
	}
	void printDP(int N){
		node *x = trie;
		int mask = 0;
		char next;
		while(true){
			next = A[mask][x];
			if (next == '$') break;
			printf("%c", next);
			mask = mask | x->mask;
			x = suffix(x, next);
		}
		printf("\n");
	}
};

AhoCorasick ac;
char buffer[309];

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++){
		scanf(" %s", buffer);
		ac.insert(buffer, (1<<i), false);
	}
	for(int i=0; i<M; i++){
		scanf(" %s", buffer);
		ac.insert(buffer, 0, true);
	}
	ac.setfails();
	ac.initDP();
	if(ac.DP(N) == INF) printf("-\n");
	else ac.printDP(N);
	return 0;
}