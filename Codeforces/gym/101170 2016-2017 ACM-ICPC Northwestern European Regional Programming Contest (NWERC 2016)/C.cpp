#include <bits/stdc++.h>
using namespace std;
#define MAXN 209
#define EPS 1e-12
#define INF 1e+18

typedef pair<double, double> dd;
vector<dd> sh;
double tx, ty;

double simulate(double vx) {
	double y = 0, x = 0;
	for(int i=0; i<(int)sh.size(); i++) {
		double dt = sh[i].first-y;
		x += vx*dt;
		y = sh[i].first;
		vx *= sh[i].second;
		//printf("dt = %.3f, x = %.3f, y = %.3f, vx = %.3f, f = %.3f\n", dt, x, y, vx, sh[i].second);
		if (fabs(y-ty) < EPS) return x;
	}
	return INF;
}

int main() {
	scanf("%lf %lf", &tx, &ty);
	int n;
	scanf("%d", &n);
	sh.push_back(dd(ty, 1));
	for(int i=0; i<n; i++) {
		double y1, y2, f;
		scanf("%lf %lf %lf", &y1, &y2, &f);
		sh.push_back(dd(y1, f));
		sh.push_back(dd(y2, 1.0/f));
	}
	sort(sh.begin(), sh.end());
	
	double lo = -INF;
	double hi = INF;
	while(fabs(hi-lo) > EPS) {
		double mid = (hi+lo)/2;
		double x = simulate(mid);
		if (x < tx) lo = mid;
		else hi = mid;
	}
	
	printf("%.11f\n", (lo+hi)/2);
	return 0;
}