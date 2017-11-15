#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
char word[1000009];

int main() {
	long long n;
	scanf("%I64d", &n);
	word[n] = '\0';
	
	if ((n*(n+1))%4 != 0) { printf("%d\n", -1); return 0; }
	
	long long sum = 0, obj = (n*(n+1))/4;
	for (int i = n; i >= 1; i--) {
		if (sum + i <= obj) { word[i-1] = '-'; sum += i; }
		else word[i-1] = '+';
	}
	printf("%s\n", word);
}