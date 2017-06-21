#include <cstdio>

int main()
{
	char c;
	int d, soma=0, n=0;
	while(scanf(" %c", &c)!=EOF){
		do{
			scanf("%c", &c);
		}while(c!='\n');
		scanf("%d", &d);
		n++;
		soma+=d;
	}
	printf("%.1f\n", soma/(double)n);
	return 0;
}