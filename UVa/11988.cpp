#include <cstdio>
#include <list>
#include <cstring>
using namespace std;
#define MAXN 100009

int main(){
	char str[MAXN];
	int n;
	list<char> l;
	list<char>::iterator it;
	while(gets(str)){
		l.clear();
		n = strlen(str);
		it = l.end();
		for(int i=0; i<n; i++){
			if (str[i]=='['){
				it = l.begin();
			}
			else if (str[i]==']'){
				it = l.end();
			}
			else l.insert(it, str[i]);
		}
		strcpy(str, "");
		n = l.size();
		for(int i=0; i<n; i++){
			str[i] = l.front();
			l.pop_front();
		}
		str[n]='\0';
		printf("%s\n", str);
	}
	return 0;
}