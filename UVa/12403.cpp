#include <cstdio>
#include <cstring>

int main()
{
	int T, tot=0, x;
	char str[10];
	scanf("%d", &T);
	while(T-->0){
		scanf(" %s", str);
		if (!strcmp(str, "donate")){
			scanf(" %d", &x);
			tot+=x;
		}
		else printf("%d\n", tot);
	}
	return 0;
}