#include <cstdio>
#include <cmath>

int main()
{
	double a, b, c, sa, sb, sc, p;
	while(scanf("%lf %lf %lf", &a, &b, &c)!=EOF){
		sa = 2*b*b + 2*c*c - a*a;
		sb = 2*a*a + 2*c*c - b*b;
		sc = 2*b*b + 2*a*a - c*c;
		if (sa<=0 || sb<=0 || sc<=0 || a<=0 || b<=0 || c<=0){
			printf("-1.000\n");
			continue;
		}
		a = sqrt(sa)/1.5;
		b = sqrt(sb)/1.5;
		c = sqrt(sc)/1.5;
		if (a>=b+c || b>=a+c || c>=a+b){
			printf("-1.000\n");
			continue;
		}
		p = (a+b+c)/2.0;
		p = sqrt(p*(p-a)*(p-b)*(p-c));
		printf("%.3f\n", p);
	}
	return 0;
}