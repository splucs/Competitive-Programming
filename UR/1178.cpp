#include <cstdio>

int main()
{
	double X;
	scanf("%lf", &X);
	for (int i = 0; i < 100; ++i)
	{
		printf("N[%d] = %.4f\n", i, X);
		X/=2.0;
	}
	return 0;
}