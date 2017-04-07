#include <cstdio>

int abs(int x){
	return (x>=0?x:-x);
}

int main()
{
	int N, B, balls[91];
	bool dif[91], ans;
	while(true){
		scanf("%d %d", &N, &B);
		if (N==0 && B==0) break;
		for (int i = 0; i <= N; ++i)
		{
			dif[i]=false;
		}
 		for (int i = 0; i < B; ++i)
 		{
 			scanf("%d", balls+i);
 		}
 		for (int i = 0; i < B; ++i)
 		{
 			for (int j = 0; j <= i; ++j)
 			{
 				dif[abs(balls[i]-balls[j])]=true;
 			}
 		}
 		ans = true;
 		for (int i = 0; i <= N; ++i)
 		{
 			if (!dif[i]){
 				ans = false;
 				break;
 			}
 		}
 		if (ans) printf("Y\n");
 		else printf("N\n");
	}
	return 0;
}