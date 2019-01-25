#include <bits/stdc++.h>
using namespace std;

const int N = 10009;
int trie[N][26], fim[N], link[N];
int cnt = 1;
 
void add(const char* s) {
	int tam = strlen(s);
	int no = 0;
	for(int i = 0; i < tam; ++i) {
		int c = s[i]-'a';
		if(!trie[no][c])
			trie[no][c] = cnt++;
		no = trie[no][c];
	}
	fim[no] += 1;
}
 
void aho() {
	queue<int> q;
	q.push(0);
	while(!q.empty()) {
		int x = q.front(); q.pop();
		fim[x] += fim[link[x]];
		for(int i = 0; i < 26; ++i) {
			if(trie[x][i]) {
				int y = trie[x][i];
				q.push(y);
				link[y] = x ? trie[link[x]][i] : 0;
			} else {
				trie[x][i] = trie[link[x]][i];
			}
		}
	}
}

int match(const char* s) {
	int no = 0, nmatch = 0;
	for(int i = 0; s[i]; i++) {
		int c = s[i]-'a';
		while (no != 0 && !trie[no][c]) no = link[no];
		no = trie[no][c];
		nmatch += fim[no];
	}
	return nmatch;
}

int main() {
	add("a");
	add("aa");
	add("ab");
	aho();
	printf("%d\n", match("aaab"));
}
