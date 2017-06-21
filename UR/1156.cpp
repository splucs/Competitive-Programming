#include <cstdio>

int main()
{
	double S=0;
	for (int i = 1, j=1; i <= 39; i+=2, j*=2)
	{
		S+=i/((double)j);
	}
	printf("%.2f\n", S);
	return 0;
}