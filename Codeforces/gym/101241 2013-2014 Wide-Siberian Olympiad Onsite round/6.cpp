#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

struct mset {
	int par, col, cha, men;
	mset() { par = col = cha = men = 0; }
	bool count(char c) {
		if (c == '(' || c == ')') return par > 0;
		if (c == '{' || c == '}') return cha > 0;
		if (c == '[' || c == ']') return col > 0;
		if (c == '<' || c == '>') return men > 0;
		return false;
	}
	void insert(char c) {
		if (c == '(' || c == ')') par++;
		if (c == '{' || c == '}') cha++;
		if (c == '[' || c == ']') col++;
		if (c == '<' || c == '>') men++;
	}
	void erase(char c) {
		if (c == '(' || c == ')') par--;
		if (c == '{' || c == '}') cha--;
		if (c == '[' || c == ']') col--;
		if (c == '<' || c == '>') men--;
	}
	bool empty() {
		return par==0 && cha==0 && col==0 && men==0;
	}
	void clear() { par = col = cha = men = 0; }
};

stack<mset> open;
mset close;
bool possible;

inline char match(char c) {
	if (c == '[') return ']';
	if (c == ']') return '[';
	if (c == '{') return '}';
	if (c == '}') return '{';
	if (c == '<') return '>';
	if (c == '>') return '<';
	if (c == '(') return ')';
	if (c == ')') return '(';
	return 0;
}

char findexistant() {
	if (close.count(')') && open.top().count('(')) return '(';
	if (close.count('>') && open.top().count('<')) return '<';
	if (close.count(']') && open.top().count('[')) return '[';
	if (close.count('}') && open.top().count('{')) return '{';
	return 0;
}

void refresh() {
	while(!close.empty() && possible) {
		while(!open.empty() && open.top().empty()) open.pop();
		if(open.empty()){
			possible = false;
			return;
		}
		char u = findexistant();
		if (u == 0) {
			possible = false;
			return;
		}
		char v = match(u);
		close.erase(v);
		open.top().erase(u);
	}
}

char str[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int T, len;
	char c;
	scanf("%d ", &T);
	
	while(T-->0) {
		scanf(" %s", str);
		len = strlen(str);
		possible = true;
		for(int i=0; i<len && possible; i++) {
			c = str[i];
			//printf("%c", c);
			if (c == '(' || c == '<'  || c == '['  || c == '{'){
				bool insertnew = !close.empty();
				refresh();
				if (insertnew || open.empty()) open.push(mset());
				open.top().insert(c);
			}
			else close.insert(c);
		}
		refresh();
		while(!open.empty() && open.top().empty()) open.pop();
		if (!open.empty()) possible = false;
		if (possible) printf("T\n");
		else printf("NIL\n");
		close.clear();
		while(!open.empty()) open.pop();
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}