#include <bits/stdc++.h>
using namespace std;
#define MAXN 2000009

struct node {
	map<char, node*> adj;
	int cnt;
	char carac; 
} nds[MAXN];

int sz;

node* newnode(char carac) {
	nds[sz].adj.clear();
	nds[sz].cnt = 0;
	nds[sz].carac = carac;
	sz++;
	return &nds[sz-1];
}

void insert(node *p, char *str) {
	p->cnt++;
	if (str[0] == 0) return;
	if (!p->adj.count(str[0])) {
		p->adj[str[0]] = newnode(str[0]);
	}
	insert(p->adj[str[0]], str+1);
}

int search(node *p, char *str) {
	if (str[0] == 0) return p->cnt;
	if (!p->adj.count(str[0])) return 0;
	return search(p->adj[str[0]], str+1);
}

char buffer[109];

int main() {
	int N;
	scanf("%d\n", &N);
	node *root = newnode(0);
	for(int i = 0; i < N; i++) {
		fgets(buffer, 109, stdin);
		int len = strlen(buffer);
		while (len > 0 && buffer[len-1] == '\n') len--;
		buffer[len] = 0;
		//printf("bufer = |%s|\n", buffer);
		if (buffer[0] == 'a') insert(root, buffer + 4);
		else printf("%d\n", search(root, buffer + 5));
	}
	return 0;
}