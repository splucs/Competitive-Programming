#include <cstdio>

int main()
{
	int N, days;
	double C;
	scanf("%d", &N);
	while(N-->0){
		scanf("%lf", &C);
		days=0;
		while(C>1.0){
			days++;
			C/=2.0;
		}
		printf("%d dias\n", days);
	}
	return 0;
}