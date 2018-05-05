#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

char str[MAXN];

int main() {
	int N, M, l, r;
	char c1, c2;
	scanf("%d %d %s", &N, &M, str);
	for(int j=0; j<M; j++) {
		scanf("%d %d %c %c", &l, &r, &c1, &c2);
		l--; r--;
		for(int i=l; i<=r; i++) {
			if (str[i] == c1) str[i] = c2;
		}
	}
	printf("%s\n", str);
	return 0;
}