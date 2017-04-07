#include <cstdio>
#include <cmath>
#define PI 3.14159
#define g 9.80665
int main()
{
	double h, a, V, dS;
	int p1, p2, n;
	while(scanf("%lf", &h)!=EOF){
		scanf("%d %d %d", &p1, &p2, &n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%lf %lf", &a, &V);
			dS=V*cos(a*PI/180.0)*(V*sin(a*PI/180.0)+sqrt(V*V*sin(a*PI/180.0)*sin(a*PI/180.0) + 2*g*h))/g;
			if (dS>=p1 && dS<=p2) printf("%.5f -> DUCK\n", dS);
			else printf("%.5f -> NUCK\n", dS);
		}
	}
	return 0;
}