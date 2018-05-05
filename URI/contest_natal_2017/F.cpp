#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

char s1[MAXN], s2[MAXN], ans[MAXN];

int main() {
	int N;
	scanf("%d\n", &N);
	while(N --> 0) {
		gets(s1); scanf("\n");
		gets(s2); scanf("\n");
		int n1 = strlen(s1);
		int n2 = strlen(s2);
		int i1 = 0, i2 = 0;
		for(int i = 0; i < n1+n2; i++) {
			if (i%4 == 0 || i%4 == 1) ans[i] = s1[i1++];
			else ans[i] = s2[i2++];
		}
		ans[n1+n2] = 0;
		printf("%s\n", ans);
	}
	return 0;
}