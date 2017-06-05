#include <vector>
#include <cstdio>
using namespace std;

struct SuTnode{
	map<char, int> sons;
	int endhere;
};

class SuffixTrie{
private:
	int size, nwords;
	SuTnode st[MAXN];
	void build(char* str, int n){
		if (str[0]=='\0'){
			st[n].endhere = nwords++;
			return;
		}
		if (!st[n].sons.count(str[0])){
			st[size].endhere=-1;
			st[size].sons.clear();
			st[n].sons[str[0]]=size++;
		}
		build(str+1, st[n].sons[str[0]]);
	}
	bool find(char* str, int n){
		if (str[0]=='\0') return true;
		if (!st[n].sons.count(str[0])) return false;
		return find(str+1, st[n].sons[str[0]]);
	}
public:
	SuffixTrie(){ size=1; nwords=0; }
	void push(char* str){ build(str, 0); }
	void clear() {
		size = 1; nwords=0;
		st[1].sons.clear();
	}
	bool count(char* str) { return find(str, 0); }
};
