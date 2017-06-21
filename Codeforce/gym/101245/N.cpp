#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

typedef long long ll;
int s, p;

double f(int n){
	return pow(s*1.0/n, n);
}

bool check(int n){
	double v = f(n);
	return (v >= p || fabs(v-p) < EPS);
}

int main() {
	scanf("%d %d", &s, &p);
	int hi = 1+(int)floor(s/exp(1.0));
	int lo = 1;
	if (s == p) printf("1\n");
	else if (!check(hi) && !check(hi-1)) printf("-1\n");
	else {
		while(hi > lo+1){
			int mid = (hi+lo)/2;
			double v = f(mid);
			if (check(mid)) hi = mid;
			else lo = mid;
		}
		if (hi == 1) hi++;
		printf("%d\n", hi);
	}
	return 0;
}