#include <bits/stdc++.h>
using namespace std;
#define ALFA 256

typedef pair<int, int> ii;

struct node {
	node *next[ALFA];
	int cnt, maxsz;
	node() {
		cnt = 0;
		maxsz = 0;
		memset(&next, 0, sizeof next);
	}
};

class AhoCorasick
{
	//Automaton build
private:
	node *trie;
public:
	AhoCorasick() { trie = new node(); }
	void clear() {
		queue<node*> q;
		q.push(trie);
		while(!q.empty()){
			node *p = q.front();
			q.pop();
			for(int i=0; i<ALFA; i++){
				q.push(p->next[i]);
			}
			delete p;
		}
		trie = new node();
	}
	void insert(const char* s) {
		int len = strlen(s);
		node *x = trie;
		for (int i = 0; i < len; i++) {
			if (x->next[s[i]] == NULL) {
				x->next[s[i]] = new node();
			}
			x = x->next[s[i]];
			x->cnt++;
			x->maxsz = max(x->maxsz, len);
		}
	}
	ii match(const char *s) {
		node* x = trie;
		int len = strlen(s), id;
		vector<ii> ans;
		for (int i = 0; i < len; i++) {
			if (x->next[s[i]] == NULL) return ii(-1, 0);
			else x = x->next[s[i]];
		}
		return ii(x->cnt, x->maxsz);
	}
};

AhoCorasick ac;
char buffer[109];

int main() {
	int N, Q;
	while(scanf("%d", &N) != EOF) {
		ac = AhoCorasick();
		while(N-->0) {
			scanf(" %s", buffer);
			ac.insert(buffer);
		}
		scanf("%d", &Q);
		while(Q-->0) {
			scanf(" %s", buffer);
			ii ans = ac.match(buffer);
			if (ans.first == -1) printf("-1\n");
			else printf("%d %d\n", ans.first, ans.second);
		}
	}
	return 0;
}