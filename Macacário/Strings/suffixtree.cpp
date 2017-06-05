#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#define MAXN 100009
using namespace std;

struct SuTnode{
	int i, j;
	map<char, int> sons;
};

class SuffixTree{
private:
	SuTnode nds[MAXN];
	char str[MAXN];
	int strsize, size;
public:
	SuffixTree(){ clear(); strcpy(str, ""); }
	SuffixTree(char* s){
		clear(); strcpy(str, s);
		strsize = strlen(str);
		for(int i=0; i<strsize; i++){
			build(str+i, 0);
		}
	}
	void clear(){
		
	}
}