#include <cstdio>

int main()
{
	int soma=0, n=0, x;
	do{
		scanf("%d", &x);
		if (x>=0){
			soma+=x;
			n++;
		}
	}while(x>=0);
	printf("%.2f\n", soma/((double)n));
	return 0;
}