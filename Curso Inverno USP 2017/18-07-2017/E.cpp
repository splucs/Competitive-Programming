#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define ALFA 2
#define MOD 1000000007LL
#define MAXN 409
#define MAXK 10009
#define state dp[n][x->id]

typedef long long ll;

struct node {
	node *fail, *next[ALFA];
	int pal, id;
	node(int u) {
		fail = NULL;
		pal = false;
		id = u;
		memset(&next, 0, sizeof next);
	}
};

class AhoCorasick
{
	//Automaton build
private:
	node *trie;
	int size;
	node *suffix(node *x, int c) {
		while (x != trie && x->next[c] == 0) x = x->fail;
		return (x->next[c] ? x->next[c] : trie);
	}
public:
	AhoCorasick() { trie = new node(0); size = 1; }
	void clear() {
		node *x, *y;
		queue<node*> q;
		q.push(trie);
		while (!q.empty()) {
			x = q.front(); q.pop();
			for (int i = 0; i < ALFA; i++) {
				y = x->next[i];
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
			for (int i = 0; i < ALFA; i++) {
				y = x->next[i];
				if (y == NULL) continue;
				y->fail = suffix(x->fail, i);
				y->pal = y->pal || y->fail->pal;
				q.push(y);
			}
		}
	}
	void insert(const int* s, int len) {
		node *x = trie, *y;
		for (int i = 0; i < len; i++) {
			y = x->next[s[i]];
			if (y == NULL || y == trie) {
				x->next[s[i]] = new node(size++);
			}
			x = x->next[s[i]];
		}
		x->pal = true;
	}

private:
	ll dp[MAXN][MAXK];
	ll DP(const int n, node* x) {
		if (state >= 0) return state;
		if (x == NULL) return state = 0;
		ll ans;
		if (x->pal) ans = 0;
		else if (n == 0) ans = 1;
		else ans = (DP(n-1, suffix(x, 0)) + DP(n-1, suffix(x, 1))) % MOD;
		//printf("dp[%d][%d] = %lld\n", n, x, ans);
		return state = ans;
	}
public:
	ll DP(int n) {
		return DP(n, trie);
	}
	void initDP() {
		for (int i = 0; i < MAXN; i++)
			for(int j=0; j<size; j++)
				dp[i][j] = -1;
	}
};

AhoCorasick ac;

void generate(int* buffer, int i, int j, int K) {
	if (i > j){
		ac.insert(buffer, K);
		return;
	}
	buffer[i] = buffer[j] = 0;
	generate(buffer, i+1, j-1, K);
	buffer[i] = buffer[j] = 1;
	generate(buffer, i+1, j-1, K);
}


void generate(int K) {
	int buffer[MAXN];
	generate(buffer, 0, K-1, K);
}

int main() {
	int T, N, K;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d", &N, &K);
		generate(K);
		generate(K+1);
		ac.setfails();
		ac.initDP();
		printf("%lld\n", ac.DP(N));
		ac.clear();
	}
	return 0;
}