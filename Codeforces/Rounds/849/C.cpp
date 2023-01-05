#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int main() {
	int k;
	scanf("%d", &k);
	int ans = 0;
	for(int c=0; c<26 && (ans < k || k == 0); c++) {
		int i=1;
		while (ans + i <= k) {
			ans += i;
			i++;
		}
		for(int j=0; j<i; j++) printf("%c", c+'a');
	}
	printf("\n");
	return 0;
}