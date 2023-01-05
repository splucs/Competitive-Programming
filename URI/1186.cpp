#include <cstdio>

int main()
{
	double M[12][12], sum=0;
	char T;
	scanf("%c", &T);
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			scanf("%lf", &M[i][j]);
		}
	}
	for (int i = 0; i < 12; ++i)
	{
		for (int j = i+1; j < 12; ++j)
		{
			sum+=M[11-i][j];
		}
	}
	if (T=='M') sum/=66.0;
	printf("%.1f\n", sum);
	return 0;
}
