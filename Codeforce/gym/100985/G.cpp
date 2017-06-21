#include <cstdio>
#include <cstring>
#define MAXN 100009

char str[MAXN];

int main(){
	while(scanf(" %s", str) != EOF){
		int n = strlen(str);
		int b = 0;
		bool possible = true;
		for(int i=0; i<n && possible; i++){
			if (str[i] == 'A') b++;
			else if (str[i] == 'B') b--;
			if (b < 0) possible = false;
		}
		if (b != 0) possible = false;
		if (possible) printf("Sim\n");
		else printf("Nao\n");
	}
	return 0;
}