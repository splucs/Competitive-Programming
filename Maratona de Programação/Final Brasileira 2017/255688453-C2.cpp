#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
typedef pair<int,int> ii;

int n,k;
int freq[1005];

bool isValid(){
	int f = freq[1];
	
	for (int i = 2; i <= k; i++) {
		if (freq[i] != f) return false;
	}
	return true;
}

int main(){
	int a;
	
	scanf("%d%d",&k,&n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		freq[a]++;
	}
	int minus = 1, mais = 1;
	
	for (int i = 1; i <= k; i++) {
		if (freq[i] < freq[minus]) minus = i;
		if (freq[i] > freq[mais]) mais = i;
	}
	
	freq[minus]++;
	if (isValid()) {
		printf("+%d\n", minus);
		return 0;
	}
	freq[minus]--;
	
	freq[mais]--;
	if (isValid()) {
		printf("-%d\n", mais);
		return 0;
	}
	freq[mais]++;
	
	freq[mais]--; freq[minus]++;
	if (isValid()) {
		printf("-%d +%d\n", mais, minus);
		return 0;
	}
	
	printf("*\n");
	return 0;
}
