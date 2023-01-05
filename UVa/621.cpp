#include <cstdio>
#include <cstring>

int main()
{
	int n, len;
	char str[1009];
	scanf("%d", &n);
	while(n-->0){
		scanf(" %s", str);
		len = strlen(str);
		if (!strcmp(str, "1") || !strcmp(str, "4") || !strcmp(str, "78")) printf("+\n");
		else if (str[len-1]=='5' && str[len-2]=='3') printf("-\n");
		else if (str[0]=='9' && str[len-1]=='4') printf("*\n");
		else if (str[0]=='1' && str[1]=='9' && str[2]=='0') printf("?\n");
	}
	return 0;
}