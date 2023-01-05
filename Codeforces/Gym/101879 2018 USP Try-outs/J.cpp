#include <bits/stdc++.h>
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;

char search(char c, int sz, int i) {
	//printf("search %c, %d, %d\n", c, sz, i);
	int hsz = sz/2;
	if (i == 1 + hsz) return c;
	if (i > 1 + hsz) i -= 1+hsz;
	return search(c-1, hsz, i);
}

int main() {
	int i;
	scanf("%d", &i);
	printf("%c\n", search('z', (1<<26)-1, i));
	return 0;
}