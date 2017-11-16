#include <bits/stdc++.h>
using namespace std;
#define INF 1e+18
#define EPS 1e-9

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	double s, p, a, b, curx, curs;
	int m, n;
	scanf("%lf %d %lf", &s, &m, &p);
	double hi = INF;
	double lo = 0;
	while (fabs(hi-lo) > EPS) {
		curx = (hi+lo)/2;
		curs = s;
		for(n=1; n<=m; n++) {
			a = curs*p/100.0;
			b = curx - a;
			curs -= b;
		}
		if (curs < 0) hi = curx;
		else lo = curx;
	}
	printf("%.5f\n", hi);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}