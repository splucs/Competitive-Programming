#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int main(){
	char str[60];
	int n;
	while(scanf(" %s", str), strcmp(str, "#")!=0){
		n = strlen(str);
		if (next_permutation(str, str+n)) printf("%s\n", str);
		else printf("No Successor\n");
	}
	return 0;
}