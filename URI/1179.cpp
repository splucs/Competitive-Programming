#include <cstdio>

int main()
{
	int par[5], impar[5], pa=0, im=0, x;
	for (int i = 0; i < 15; ++i)
	{
		scanf("%d", &x);
		if (x%2==0){
			par[pa++]=x;
			if (pa==5){
				for (int j = 0; j < 5; ++j)
				{
					printf("par[%d] = %d\n", j, par[j]);
				}
				pa=0;
			}
		}
		else{
			impar[im++]=x;
			if (im==5){
				for (int j = 0; j < 5; ++j)
				{
					printf("impar[%d] = %d\n", j, impar[j]);
				}
				im=0;
			}
		}
	}
	for (int j = 0; j < im; ++j)
	{
		printf("impar[%d] = %d\n", j, impar[j]);
	}
	for (int j = 0; j < pa; ++j)
	{
		printf("par[%d] = %d\n", j, par[j]);
	}
	return 0;
}