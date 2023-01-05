#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

int LIS(int* arr, int n){
	int M[n+1], L=1, l, h, m;
	M[1]=0;
	for(int i=1; i<n; i++){
		if (arr[i]<arr[M[1]]){		//estritamente crescente
		//if (arr[i]<=arr[M[1]]){	//crescente
			M[1]=i; continue;
		}
		l = 1; h = L+1;
		while(h>l+1){
			m = (l+h)/2;
			if (arr[M[m]]<arr[i]) l = m;	//estritamente crescente
			//if (arr[M[m]]<=arr[i]) l = m;	//crescente
			else h = m;
		}
		if (h>L) L=h;
		M[h] = i;
	}
	return L;
}

int arr[MAXN];

int main() {
	int N;
	while(scanf("%d", &N) != EOF) {
		for(int i=0; i<N; i++) {
			scanf("%d", &arr[i]);
			arr[i] *= -1;
		}
		printf("%d\n", LIS(arr, N)-1);
	}
	return 0;
}