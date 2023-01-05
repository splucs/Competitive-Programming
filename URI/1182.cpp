#include <cstdio>

int main()
{
	double M[12][12], sum=0;
	int L;
	char T;
	scanf("%d %c", &L, &T);
	for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < 12; ++j)
		{
			scanf("%lf", &M[i][j]);
		}
	}
	for (int i = 0; i < 12; ++i)
	{
		sum+=M[i][L];
	}
	if (T=='M') sum/=12.0;
	printf("%.1f\n", sum);
	return 0;
}
