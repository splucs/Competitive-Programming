#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

int n;
char s1[MAXN], s2[MAXN];

int main()
{
	scanf("%d %s %s", &n, s1, s2);
	int ans = 0;
	for(int i=0; i<n; i++){
		if (s1[i] != s2[i]){
			ans++;
			if (i > 0 && s1[i-1] != s2[i-1]) ans--;
		}
	}
	printf("%d\n", ans);
	return 0;
}