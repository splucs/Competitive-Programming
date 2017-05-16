#include <bits/stdc++.h>
using namespace std;
#define MAXN 50009

struct node {
	map<char, node*> next;
	bool pats;
	char c;
	node() {
		pats = false;
		c = '$';
	}
};

bool ans;

class AhoCorasick
{
	//Automaton build
private:
	node *trie;
	map<node*, set<node*> > dp;
	vector<node> nds;
	int size;
	node* newnode(char c) {
		nds[size].pats = false;
		nds[size].c = c;
		nds[size].next.clear();
		size++;
		return &nds[size-1];
	}
public:
	AhoCorasick() {
		size = 0;
		nds.resize(MAXN);
		trie = newnode('$');
	}
	void insert(const char* s) {
		int len = strlen(s);
		node *x = trie;
		for (int i = 0; i < len && len > 0; i++) {
			if (!x->next.count(s[i])) {
				x->next[s[i]] = newnode(s[i]);
			}
			x = x->next[s[i]];
		}
		x->pats = true;
	}
	void dfs() { dfs(trie); }
private:
	void dfs(node* x) {
		if (x == NULL) return;
		if (x->pats) DP(x, trie);
		for(map<char, node*>::iterator it = x->next.begin(); it!=x->next.end(); it++) {
			dfs(it->second);
		}
	}
	void DP(node* x, node* y) {
		if (ans || !x || !y) return;
		//if (dp.count(x) && dp[x].count(y)) return;
		//dp[x].insert(y);
		//dp[y].insert(x);
		//printf("dp(%c,%c)\n", x->c, y->c);
		if (x->pats && y->pats) {
			ans = true;
			return;
		}
		if (x->pats && y != trie){
			//printf(" ->dp(%c,%c)\n", trie->c, y->c);
			DP(trie, y);
		}
		if (y->pats && x != trie){
			//printf(" ->dp(%c,%c)\n", x->c, trie->c);
			DP(x, trie);
		}
		for(map<char, node*>::iterator it = x->next.begin(); it!=x->next.end(); it++) {
			char c = it->first;
			//if (y->next[c]) printf(" ->dp(%c,%c)\n", x->next[c]->c, y->next[c]->c);
			if (y->next.count(c)) DP(x->next[c], y->next[c]);
		}
	}
};

char str[MAXN];
AhoCorasick ac;

int main() 
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int N;
	scanf("%d", &N);
	while(N-->0) {
		scanf(" %s", str);
		ac.insert(str);
	}
	ans = false;
	ac.dfs();
	if (ans) printf("YES\n");
	else printf("NO\n");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}