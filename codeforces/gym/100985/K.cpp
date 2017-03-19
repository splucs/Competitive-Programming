#include <cstdio>
#include <cstring>
#define MAXN 100009

char str[MAXN];

int main(){
	scanf("%s", str);
	int n = strlen(str);
	for(int i=0, j; i<n; i=j){
		j=i;
		while(str[i] == str[j]) j++;
		printf("%c%d", str[i], j-i);
	}
	printf("\n");
	return 0;
}