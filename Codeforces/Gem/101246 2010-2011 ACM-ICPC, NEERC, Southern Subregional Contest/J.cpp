#include <bits/stdc++.h>
using namespace std;
#define MAXN 409
#define INF 1e+18

double x[MAXN], xa[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%lf", &x[i]);
	}
	
	double x0, dx;
	double ans = INF, curans;
	for(int i=0; i<N; i++){
		for(int j=i+1; j<N; j++){
			dx = (x[j]-x[i])/(j-i);
			x0 = x[i] - i*dx;
			curans = 0.0;
			for(int k=0; k<N; k++){
				curans += fabs(x[k] - (x0 + k*dx));
			}
			if (ans > curans){
				ans = curans;
				for(int k=0; k<N; k++){
					xa[k] = x0 + k*dx;
				}
			}
		}
	}
	printf("%.10f\n", ans);
	for(int k=0; k<N; k++){
		printf("%.10f ", xa[k]);
	}
	printf("\n");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}