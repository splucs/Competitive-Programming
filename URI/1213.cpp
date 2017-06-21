#include <cstdio>

int main()
{
	int n;
	int cont, aux, p;
	while(scanf("%d", &n)!=EOF){
		cont=0;
		aux=n;
		while(aux>0){
			cont++;
			aux/=10;
		}
		cont++;
		p=0;
		for (int i = 0; i < cont; ++i)
		{
			p=p*10 + 1;
		}
		p%=n;
		while(p%n>0){
			p = (p%n)*10+1;
			cont++;
		}
		printf("%d\n", cont);
	}
	return 0;
}