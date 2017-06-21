#include <cstdio>
#include <cmath>

int main()
{
	int N, X, S;
	scanf("%d", &N);
	bool prime;
	while(N-->0){
		scanf("%d", &X);
		S = sqrt(X);
		prime = true;
		for (int i = 2; i <= S && prime; ++i)
		{
			if (X%i==0) prime=false;
		}
		if (prime) printf("%d eh primo\n", X);
		else printf("%d nao eh primo\n", X);
	}
	return 0;
}