#include <bits/stdc++.h>
using namespace std;

double arr[7], D;

int main() {
	int T;
	scanf("%d", &T);
	for(int t=1; t<=T; t++) {
		scanf("%lf", &D);
		for(int i=0; i<7; i++) scanf("%lf", &arr[i]);
		sort(arr, arr+7);
		double ans = 0;
		for(int i=1; i<=5; i++) ans += arr[i];
		ans /= 5.0;
		ans *= D;
		printf("Caso %d: %.1f\n", t, ans);
	}
	return 0;
}