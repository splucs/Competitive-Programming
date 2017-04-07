#include <cstdio>

int main()
{
	double A;
	for (int i = 0; i < 100; ++i)
	{
		scanf("%lf", &A);
		if(A<=10.0) printf("A[%d] = %.1f\n", i, A);
	}
	return 0;
}