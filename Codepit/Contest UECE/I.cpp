#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	double L, A;
	while(T-->0) {
		scanf("%lf %lf", &L, &A);
		double cir = M_PI*L*L*A/360.0;
		double tri = L*L*sin(A*M_PI/180.0)/2;
		printf("%.6f\n", cir - tri);
	}
	return 0;
}