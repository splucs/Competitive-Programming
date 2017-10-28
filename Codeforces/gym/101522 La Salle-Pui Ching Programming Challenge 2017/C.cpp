#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

char str[MAXN];

int main() {
	scanf(" %s", str);
	int ca = 0, cb = 0;
	int N  =strlen(str);
	for(int i=0; i<N; i++) {
		if (strncmp(str+i, "LSC", 3) == 0) ca++;
		if (strncmp(str+i, "PCMS", 4) == 0) cb++;
	}
	if (ca > cb) printf("LSC\n");
	else if (ca < cb) printf("PCMS\n");
	else printf("Tie\n");
	return 0;
}