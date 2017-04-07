#include <cstdio>
#include <cmath>

int main()
{
	double a, b, c, A, p, r, R;
	while(scanf("%lf %lf %lf", &a, &b, &c)!=EOF){
		p = 0.5*(a+b+c);
		A = sqrt(p*(p-a)*(p-b)*(p-c));
		r = A/p;
		R = a*b*c/(4*A);
		printf("%.4f %.4f %.4f\n", M_PI*R*R - A, A - M_PI*r*r, M_PI*r*r);
	}
	return 0;
}