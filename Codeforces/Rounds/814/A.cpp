#include <bits/stdc++.h>
using namespace std;
#define MAXN 209

int a[MAXN], b[MAXN], n, k, zid;

int main() {
	scanf("%d %d", &n, &k);
	bool possible = false;
	if (k > 1) possible = true;
	zid = -1;
	for(int i=0; i<n; i++){
		scanf("%d", &a[i]);
		if (a[i] == 0){
			zid = i;
		}
		if (i > 0 && a[i] < a[i-1] && i-1 != zid && i != zid){
			possible = true;
		}
	}
	for(int i=0; i<k; i++){
		scanf("%d", &b[i]);
	}
	a[zid] = b[0];
	if (zid > 0 && a[zid] < a[zid-1]) possible = true;
	if (zid < n-1 && a[zid+1] < a[zid]) possible = true;
	if (possible) printf("Yes\n");
	else printf("No\n");
	return 0;
}