#include <cstdio>
#include <cstring>

int main(){
	int N;
	char str[10];
	scanf("%d", &N);
	while(N-->0){
		scanf(" %s", str);
		if (strlen(str)==5) printf("3\n");
		else if (((int)(str[0]=='t')) + ((int)(str[1]=='w')) + ((int)(str[2]=='o')) >= 2) printf("2\n");
		else printf("1\n");
	}
	return 0;
}