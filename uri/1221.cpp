#include <cstdio>
#include <cmath>

int main()
{
	int N, X, s;
	bool prime;
	scanf("%d", &N);
	while(N-->0){
		scanf("%d", &X);
		s = sqrt(X);
		prime=true;
		for (int i = 2; i <= s && prime; ++i)
		{
			if (X%i==0) prime = false;
		}
		if (prime) printf("Prime\n");
		else printf("Not Prime\n");
	}
	return 0;
}