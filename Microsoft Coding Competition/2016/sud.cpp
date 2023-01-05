#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 10009

struct lex_compare {
    bool operator() (const string& a, const string& b) const{
        for(int i=0; i<(int)min(a.size(), b.size()); i++){
        	if (a[i]==b[i]) continue;
        	if (a[i]==';') return true;
        	if (b[i]==';') return false;
        	if (a[i]=='.') return true;
        	if (b[i]=='.') return false;
        	return a[i]<b[i];
        }
        return true;
    }
};

int main()
{
	string line;
	set<string, lex_compare> toprint;
	bool toadd;
	set<string, lex_compare>::iterator it;
	int i=0;
	while(getline(cin, line)){
		toprint.clear();
		if (line == "//----") break;
		if (line.substr(line.size()-6, 6) == "//Used"){
			toprint.insert(line);
		}
		while(true){
			getline(cin, line);
			if (line == "//----") break;
			if (line.substr(line.size()-6, 6) == "//Used"){
				toprint.insert(line);
			}
		}
		for(it=toprint.begin(); it!=toprint.end(); it++){
			printf("%s\n", it->c_str());
		}
		printf("//----\n");
	}
	return 0;
}