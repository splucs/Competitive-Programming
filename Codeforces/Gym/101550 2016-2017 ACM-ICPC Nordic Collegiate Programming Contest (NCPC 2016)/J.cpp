#include <bits/stdc++.h>
using namespace std;

int main() {
	int n1, n2;
	while(scanf("%d %d", &n1, &n2) != EOF) {
		int d1 = 0;
		for(int i=n1; i!=n2; i = (i+1)%360) {
			d1++;
		}
		int d2 = 0;
		for(int i=n1; i!=n2; i = (i+359)%360) {
			d2--;
		}
		if (abs(d2) >= abs(d1)) printf("%d\n", d1);
		else printf("%d\n", d2);
	}
	return 0;
}