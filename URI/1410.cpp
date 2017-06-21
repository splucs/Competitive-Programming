#include <cstdio>

int main()
{
	int A, D, A1, D1, D2, b;
	while(true){
		scanf("%d %d", &A, &D);
		if (A==0 && D==0) break;
		A1=D1=D2=10000;
		for(int i=0; i<A; i++){
			scanf("%d", &b);
			if (b<A1) A1=b;
		}
		for(int i=0; i<D; i++){
			scanf("%d", &b);
			if (b<=D1){
				D2=D1;
				D1=b;
			}
			else if (b<D2) D2=b;
		}
		if (D2>A1) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}