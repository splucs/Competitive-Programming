#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int a[MAXN], b[MAXN], n;
bool match[MAXN];
vector<int> missing, missingid;

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d", &a[i]);
		match[i] = false;
	}
	for(int i=1; i<=n; i++) {
		scanf("%d", &b[i]);
		if (a[i] != b[i]) {
			missingid.push_back(i);
		}
		else match[a[i]] = true;
	}
	for(int i=1; i<=n; i++){
		if (!match[i]) missing.push_back(i);
	}
	if (missing.size() == 1u){
		for(int i=1; i<=n; i++) {
			if (a[i] != b[i]) {
				a[i] = b[i] = missing[0];
			}
		}
	}
	else{
		if (!match[a[missingid[0]]] && !match[b[missingid[1]]]){
			b[missingid[0]] = a[missingid[0]];
			a[missingid[1]] = b[missingid[1]];
		}
		else if (!match[b[missingid[0]]] && !match[a[missingid[1]]]){
			a[missingid[0]] = b[missingid[0]];
			b[missingid[1]] = a[missingid[1]];
		}
	}
	for(int i=1; i<=n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}