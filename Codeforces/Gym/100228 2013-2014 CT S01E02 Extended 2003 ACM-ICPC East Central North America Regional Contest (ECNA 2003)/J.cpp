#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

char s1[MAXN], s2[MAXN];
int freq1[MAXN], freq2[MAXN];

int main() {
	while(gets(s1) && gets(s2)) {
		memset(&freq1, 0, sizeof freq1);
		memset(&freq2, 0, sizeof freq2);
		int n1 = strlen(s1);
		for(int i=0; i<n1; i++) {
			freq1[s1[i]]++;
		}
		int n2 = strlen(s2);
		for(int i=0; i<n2; i++) {
			freq2[s2[i]]++;
		}
		for(int i=0; i<256; i++) {
			while(freq1[i] > 0 && freq2[i] > 0) {
				freq1[i]--;
				freq2[i]--;
				printf("%c", (char)i);
			}
		}
		printf("\n");
	}
	return 0;
}