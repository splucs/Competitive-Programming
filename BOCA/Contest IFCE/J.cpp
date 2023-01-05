#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

bool s2[MAXN];

int main() {
	memset(&s2, false, sizeof s2);
	for(int i=0; i*i<MAXN; i++) {
		for(int j=0; i*i + j*j < MAXN; j++) {
			s2[i*i + j*j] = true;
		}
	}
	int P;
	scanf("%d", &P);
	bool ok = false;
	for(int i=0; i*i<=P; i++) {
		if (s2[P - i*i]) ok = true;
	}
	if (ok) printf("YES\n");
	else printf("NO\n");
	return 0;
}