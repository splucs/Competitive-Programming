#include <cstdio>

int main()
{
	int A, B;
	int carry;
	int cont;
	while(true){
		scanf("%d %d", &A, &B);
		if(A==0 && B==0) break;
		carry=0;
		cont=0;
		while ((A>0 && B>0) || carry>0){
			if (A%10+B%10+carry>=10){
				cont++;
			}
			carry = (A%10+B%10+carry)/10;
			A/=10;
			B/=10;
		}
		if (cont==0) printf("No carry operation.\n");
		else if (cont==1) printf("1 carry operation.\n");
		else printf("%d carry operations.\n", cont);
	}
	return 0;
}