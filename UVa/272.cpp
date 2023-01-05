#include <cstdio>

int main()
{
	bool close=false;
	char c;
	while(scanf("%c", &c)!=EOF){
		if (c=='"' && !close){
			printf("``");
			close=true;
		}
		else if (c=='"'){
			printf("''");
			close=false;
		}
		else printf("%c", c);
	}
	return 0;
}