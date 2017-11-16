#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009

struct STnode{
	map<char, int> sons;
	char carac;
	int fail; int parent;
	int depth;
	int id;
	STnode(int p, char c, int d){
		fail = id = -1;
		parent = p; carac = c;
		depth = d;
	}
};

int ids[MAXN], match[MAXN][MAXN], Ti[MAXN], currow, R1, C1, R2, C2;

void action(int pos, int id){
	match[currow][pos] = id;
}

class SuffixTrie{
private:
	vector<STnode> st;
	char* str;
	void build(int i, int n, int id){
		if (str[i]=='\0'){
			if (st[n].id != -1) id = ids[id] = st[n].id;
			st[n].id = id; return;
		}
		if (!st[n].sons.count(str[i])){
			st[n].sons[str[i]] = (int)st.size();
			st.push_back(STnode(n, str[i], st[n].depth+1));
		}
		build(i+1, st[n].sons[str[i]], id);
	}
	bool find(int i, int n){
		if (str[i]=='\0') return true;
		if (!st[n].sons.count(str[i])) return false;
		return find(i+1, st[n].sons[str[i]]);
	}
	int callids(int pos, int p){
		if (st[p].id != -1) action(pos, st[p].id);
		return st[p].id != -1;
	}
	int match(int i, int n){
		int ans = 0;
		if (str[i] == '\0' || st[n].sons.count(str[i])){
			int p = n;
			ans += callids(i-st[p].depth-1, p);
			if (str[i] == '\0') return ans;
			ans += match(i+1, st[n].sons[str[i]]);
		}
		else if (n != 0){
			ans += callids(i-st[n].depth-1, n);
			ans += match(i, st[n].fail);
		}
		else ans += match(i+1, 0);
		return ans;
	}
public:
	SuffixTrie(){ clear(); }
	void push(char* s, int id){
		str = s;
		build(0, 0, id);
	}
	void clear() {
		st.clear();
		st.push_back(STnode(0, '\0', -1));
	}
	bool count(char* s) {
		str = s;
		return find(0, 0);
	}
	void setfails(){
		st[0].fail = 0;
		queue<int> q; q.push(0);
		map<char, int>::iterator it;
		int n, p; char c;
		while(!q.empty()){
			n = q.front(); q.pop(); c = st[n].carac;
			for(it = st[n].sons.begin(); it != st[n].sons.end(); it++){
				q.push(it->second);
			}
			p = st[st[n].parent].fail;
			while(p != 0 && !st[p].sons.count(c)) p = st[p].fail;
			st[n].fail = (p != st[n].parent && st[p].sons.count(c)? st[p].sons[c] : 0);
		}
	}
	int ahoCorasick(char* s) {
		str = s;
		return match(0, 0);
	}
};

class KMP{
private:
	int P[MAXN];
	int m, n, b[MAXN];
public:
	KMP(const int* _P, int _m){
		m = _m;
		for(int i=0; i<m; i++) P[i] = _P[i];
		b[0] = -1;
		for(int i = 0, j = -1; i < m;) {
			while (j >= 0 && P[i] != P[j]) j = b[j];
			i++; j++;
			b[i] = j;
		}
	}
	vector<int> match(int* T, int _n){
		n = _n;		
		vector<int> ans;
		for (int i=0, j=0; i < n;) {
			while (j >= 0 && P[j] != T[i]) j = b[j];
			i++; j++;			
			if (j == m) {
				ans.push_back(i - j);
				j = b[j];
			}
		}
		return ans;
	}
};


char T[MAXN], P[MAXN];

int main(){
	scanf("%d %d %d %d", &R1, &C1, &R2, &C2);
	SuffixTrie st;
	for(int i=0; i<R1; i++){
		scanf(" %s", P);
		ids[i] = i;
		st.push(P, i);
	}
	st.setfails();
	for(int i=0; i<R2; i++){
		currow = i;
		scanf(" %s", T);
		for(int j=0; j<C2; j++){
			match[currow][j] = -1;
		}
		st.ahoCorasick(T);
	}
	KMP kmp(ids, R1);
	int ans = 0;
	vector<int> indexes;
	for(int j=0; j<C2; j++){
		for(int i=0; i<R2; i++){
			Ti[i] = match[i][j];
		}
		indexes = kmp.match(Ti, R2);
		ans += indexes.size();
	}
	printf("%d\n", ans);
	return 0;
}