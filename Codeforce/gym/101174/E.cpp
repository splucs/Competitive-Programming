#include <cstdio>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define ALFA 256
#define state dp[lo][up][nu][sz][x]
#define MOD 1000003
#define MAXSZ 22
#define MAXN 1009

struct node
{   node *suff;
    node *next[256];
    bool allowed;
    vector<char> out;

    node() {
        suff = 0;
		allowed = true;
		for(int i=0; i<ALFA; i++) next[i] = 0;
		out = vector<char>();
    }
};

class AhoCorasick
{
	node *trie;
	map<node*, int> dp[2][2][2][MAXSZ];
	map<node*, char> ptr2id;

    node *suffix(node *x, char c) {
		while(x != trie && x->next[c] == 0) x = x->suff;
		return x->next[c];
    }

    public:
    AhoCorasick() {
		trie = new node();
		ptr2id[trie] = '$';
	}
	
	void setfails() {
		queue<node *> q;
        for(int i = 0; i < ALFA; i++) {
			if(trie->next[i]) {
				trie->next[i]->suff = trie;
                q.push(trie->next[i]);
			}
            else {
				trie->next[i] = trie;
            }
        }

        while(!q.empty()) {
			node *x = q.front(); q.pop();
            for(int i = 0; i < (int)x->out.size(); i++) {
				node *y = x->next[x->out[i]];
                y->suff = suffix(x->suff, x->out[i]);
                y->allowed = (y->allowed && y->suff->allowed);
                q.push(y);
            }
        }
		
		for(int lo=0; lo<2; lo++) for(int up=0; up<2; up++) for(int nu=0; nu<2; nu++) {
			for(int sz=0; sz<MAXSZ; sz++) dp[lo][up][nu][sz].clear();
		}
	}
	
	void insert(const char* s) {
		int len = strlen(s);
		node* x = trie;
		for(int i = 0; i < len; i++) {
			if(x->next[s[i]] == NULL) {
				x->next[s[i]] = new node();
				ptr2id[x->next[s[i]]] = s[i];
                x->out.push_back(s[i]);
            }
            x = x->next[s[i]];
        }
        x->allowed = false;
	}
	
	char tolower(char c) {
		if (c >= 'A' && c <='Z') return c - 'A' + 'a';
		if (c == '3') return 'e';
		if (c == '0') return 'o';
		if (c == '1') return 'i';
		if (c == '5') return 's';
		if (c == '7') return 't';
		return c;
	}

    int DP(int lo, int up, int nu, int sz, node* x) {
		if (dp[lo][up][nu][sz].count(x)) return state;
		if (x == NULL || !x->allowed) return state = 0;
		if (sz == 0) return state = (lo == 1 && up == 1 && nu == 1);
		int ans = 0;
		for(char c = 'a'; c <= 'z'; c++) {
			ans += DP(1, up, nu, sz-1, suffix(x, tolower(c)));
			ans %= MOD;
		}
		for(char c = 'A'; c <= 'Z'; c++) {
			ans += DP(lo, 1, nu, sz-1, suffix(x, tolower(c)));
			ans %= MOD;
		}
		for(char c = '0'; c <= '9'; c++) {
			ans += DP(lo, up, 1, sz-1, suffix(x, tolower(c)));
			ans %= MOD;
		}
		return state = ans;
	}
	int DP(int sz) {
		return DP(0, 0, 0, sz, trie);
	}
	bool match(const char *s){    
		node *x = trie;
        int cnt = 0, len = strlen(s);
        for(int i = 0; i < len; i++) {
			printf("%c to %c(%c)\n", ptr2id[x], ptr2id[suffix(x, tolower(s[i]))], s[i]);
			x = suffix(x, tolower(s[i]));
			if (!x->allowed) return false;
        }
		return true;
    }
};

char str[MAXSZ];
AhoCorasick ac;

int main()
{
	int N, A, B;
	scanf("%d %d %d", &A, &B, &N);
	while(N--) {
		scanf(" %s", str);
		ac.insert(str);
	}
	ac.setfails();
	//if (ac.match("aA9")) printf("allowed\n");
	//else printf("not allowed\n");
	int ans = 0;
	for(int i=A; i<=B; i++){
		ans = (ans + ac.DP(i)) % MOD;
	}
	printf("%d\n", ans);
	return 0;
}