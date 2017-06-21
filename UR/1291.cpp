#include <cstdio>
#include <cmath>

int main(){
	double a, A1, A2, A3;
	A1 = 1.0-sqrt(3.0)+M_PI/3.0;
	A2 = M_PI-2-2*A1;
	A3 = 1-A2-A1;
	while(scanf("%lf", &a)!=EOF){
		printf("%.3f %.3f %.3f\n", a*a*A1, a*a*A2, a*a*A3);
	}
	return 0;
}