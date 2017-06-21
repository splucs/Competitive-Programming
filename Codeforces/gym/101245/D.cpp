#include <bits/stdc++.h>
using namespace std;
#define MAXN 50009

int n, b[MAXN];
char s1[MAXN], s2[MAXN];

class KMP{
private:
	char P[MAXN];
	int m, n, b[MAXN];
public:
	KMP(const char* _P){
		strcpy(P, _P);
		b[0] = -1;
		m = strlen(P);
		for(int i = 0, j = -1; i < m;) {
			while (j >= 0 && P[i] != P[j]) j = b[j];
			i++; j++;
			b[i] = j;
		}
	}
	int match(const char* T){
		n = strlen(T);
		int i, j;
		for (i=0, j=0; i < n;) {
			while (j >= 0 && T[i] != P[j]) j = b[j];
			i++; j++;
		}
		return j;
	}
};

int main() {
	scanf(" %s %s", s1, s2);
	n = strlen(s1);
	if (n != strlen(s2)){
		printf("No\n");
		return 0;
	}
	KMP kmp(s2);
	int m = kmp.match(s1);
	bool possible = true;
	for(int i=0; i<n-m; i++){
		if (s1[i] != s2[n-1-i]) possible = false;
	}
	if (possible) printf("Yes\n%d\n", n-m);
	else printf("No\n");
	return 0;
	
}