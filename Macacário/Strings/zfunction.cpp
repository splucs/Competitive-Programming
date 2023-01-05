#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
 * Z-function
 */

void zfunction(char s[], int z[]) {
	int n = strlen(s);
	fill(z, z+n, 0);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r) z[i] = min(r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
}

/*
 * TEST MATRIX
 */

void naivez(char* s, int* z) {
	int n = strlen(s);
	fill(z, z+n, 0);
	for(int i=1; i<n; i++) {
		while(i+z[i] < n && s[z[i]]==s[i+z[i]]) z[i]++;
	}
}
int main() {
	char str[309];
	int z1[309], z2[309];
	for(int n=1; n<10; n++) {
		for(int i=0; i<n; i++) {
			str[i] = 'a' + rand()%2;
		}
		str[n] = 0;
		naivez(str, z1);
		printf("test #%d: %s\n", n, str);
		zfunction(str, z2);
		printf("naive:");
		for(int i=0; i<n; i++) {
			printf(" %2d", z1[i]);
		}
		printf("\n");
		printf("zfunc:");
		for(int i=0; i<n; i++) {
			printf(" %2d", z2[i]);
		}
		printf("\n");
	}
}