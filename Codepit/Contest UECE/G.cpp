#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

bool mirror[MAXN];
char carac[11] = {'A', 'H', 'I', 'M', 'O', 'T', 'U', 'V', 'W', 'X', 'Y'};
char str[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	memset(&mirror, false, sizeof mirror);
	for(int i=0; i<11; i++) {
		mirror[carac[i]] = true;
	}
	while(T-->0) {
		scanf(" %s", str);
		int len = strlen(str);
		bool ok = true;
		for(int i=0; i<len; i++) {
			if (str[i] != str[len-i-1]) ok = false;
			if (!mirror[str[i]]) ok = false;
		}
		if (ok) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}