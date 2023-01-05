#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

char str[MAXN];

int getlimit(int rnk) {
	if (rnk >= 21) return 2;
	if (rnk >= 16) return 3;
	if (rnk >= 11) return 4;
	return 5;
}

int main() {
	while(scanf(" %s", str) != EOF) {
		int n = strlen(str);
		int rnk = 25;
		int stars = 0;
		int streak = 0;
		for(int i=0; i<n; i++) {
			if (rnk == 0) break;
			if (str[i] == 'W') {
				stars++;
				streak++;
				if (rnk >= 6 && streak >= 3) stars++;
				if (stars > getlimit(rnk)) {
					stars -= getlimit(rnk);
					rnk--;
				}
			}
			else {
				streak = 0;
				if (rnk < 20 || (rnk == 20 && stars > 0)) {
					stars--;
					if (stars < 0) {
						rnk++;
						stars += getlimit(rnk);
					}
				}
			}
		}
		if (rnk == 0) printf("Legend\n");
		else printf("%d\n", rnk);
	}
	return 0;
}