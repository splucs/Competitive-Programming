#include <cstdio>
#include <cmath>

int main(){
	double x1, x2, y1, y2, a, b;
	while(scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &a, &b)!=EOF){
		a*=M_PI/180.0;
		b*=M_PI/180.0;
		printf("%.3f\n", sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))*(1/tan(a) + 1/tan(b)));
	}
	return 0;
}