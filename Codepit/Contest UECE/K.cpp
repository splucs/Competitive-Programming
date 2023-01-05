#include <bits/stdc++.h>
using namespace std;

char buffer[20];

int main() {
	int T, C, N;
	scanf("%d", &T);
	double v;
	while(T-->0) {
		map<string, double> conv;
		scanf("%d %d", &C, &N);
		for(int i=0; i<C; i++) {
			scanf(" %s %lf", buffer, &v);
			conv[string(buffer)] = v;
		}
		conv["JD"] = 1.0;
		double ans = 0.0;
		for(int i=0; i<N; i++) {
			scanf("%lf %s", &v, buffer);
			ans += v*conv[string(buffer)];
		}
		printf("%.6f\n", ans);
	}
	return 0;
}