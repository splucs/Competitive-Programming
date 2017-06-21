#include <cstdio>
#include <cmath>

int main()
{
	double L, W;
	while(scanf("%lf %lf", &L, &W)!=EOF){
		printf("%.3f %.3f %.3f\n", (L+W-sqrt(L*L-L*W+W*W))/6.0, 0.0, (L>W?W:L)/2.0);
	}
	return 0;
}