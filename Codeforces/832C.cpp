#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define SZ 1000000

double x[MAXN], v[MAXN], s;
int N, dir[MAXN], id[MAXN];
bool cnt[MAXN];

bool check(double T) {
	double d, b;
	memset(&cnt, false, sizeof cnt);
	int l = -1, r = SZ+1;
	//printf("testing T = %.3f\n", T);
	
	//left headed
	for(int it=0, i; it<N; it++) {
		i = id[it];
		if (dir[i] == 2) continue;
		d = x[i];
		if (d / v[i] <= T) {
			for(int j=0; j<=SZ; j++) cnt[j] = true;
			break;
		}
		b = (s*s*T - v[i]*v[i]*T + v[i]*d) * 1.0 / s;
		if (b < d) continue;
		//printf("updating %g to %g\n", x[i], b);
		if (l < x[i]) l = x[i];
		for(; l<=b && l <= SZ ; l++) cnt[l] = true;
	}
	
	//right headed
	for(int it=N-1, i; it>=0; it--) {
		i = id[it];
		if (dir[i] == 1) continue;
		d = SZ-x[i];
		if (d / v[i] <= T) {
			for(int j=0; j<=SZ; j++) if(cnt[j]) return true;
			break;
		}
		b = (s*s*T - v[i]*v[i]*T + v[i]*d) * 1.0 / s;
		if (b < d) continue;
		//printf("updating %g to %g\n", x[i], SZ-b);
		if (r > x[i]) r = x[i];
		for(; r >= SZ-b && r >= 0; r--) {
			if (cnt[r]) return true;
		}
	}
	
	return false;
}

bool comp(int i, int j) {
	return x[i] < x[j];
}

int main() {
	scanf("%d %lf", &N, &s);
	for(int i=0; i<N; i++) {
		id[i] = i;
		scanf("%lf %lf %d", &x[i], &v[i], &dir[i]);
	}
	sort(id, id+N, comp);
	double lo = 0.0;
	double hi = 1e+18;
	while(hi - lo > 1e-9) {
		double m = (hi + lo) / 2;
		if (check(m)) hi = m;
		else lo = m;
	}
	printf("%.10f\n", hi);
	return 0;
}