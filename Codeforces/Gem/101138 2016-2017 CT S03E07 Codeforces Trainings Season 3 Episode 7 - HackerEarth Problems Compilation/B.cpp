#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

char str[MAXN];

int main() {
	int T, len;
	scanf("%d", &T);
	while(T-->0) {
		scanf(" %s", str);
		len = strlen(str);
		bool possible = true;
		if (len != (len & -len)) possible = false;
		for(int i=1; i<len; i+= 2) {
			if (str[i] != 'P' && str[i-1] != 'P') possible = false;
		}
		if (possible) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}