#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

bool hasCam[MAXN];

int main()
{
	int n, k, r, count, ans;
	memset(&hasCam, false, sizeof hasCam);
	scanf("%d %d %d", &n, &k, &r);
	for(int i=0; i<k; i++){
		scanf("%d", &count);
		hasCam[count] = true;
	}
	count = 0;
	ans = 0;
	for(int i=1; i<r && i<=n; i++){
		if (hasCam[i]) count++;
	}
	for(int i=0, j=r; j<=n; j++, i++){
		if (hasCam[i]) count--;
		if (hasCam[j]) count++;
		while (count < 2){
			if (!hasCam[j]){
				hasCam[j] = true;
			}
			else{
				hasCam[j-1] = true;
			}
			count++;
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}