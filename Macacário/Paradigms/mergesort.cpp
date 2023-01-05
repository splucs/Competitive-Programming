#include <cstdio>
#define MAXN 100009

/*
 * Merge-sort with inversion count in O(nlogn)
 */

long long inv;
int aux[MAXN];

void mergesort(int arr[], int l, int r) {
	if (l == r) return;
	int m = (l + r) / 2;
	mergesort(arr, l, m);
	mergesort(arr, m+1, r);
	int i = l, j = m + 1, k = l;
	while(i <= m && j <= r) {
		if (arr[i] > arr[j]) {
			aux[k++] = arr[j++];
			inv += j - k;
		}
		else aux[k++] = arr[i++];
	}
	while(i <= m) aux[k++] = arr[i++];
	for(i = l; i < k; i++) arr[i] = aux[i];
}

/*
 * TEST MATRIX
 */

int main() {
	int N, vet[MAXN];
	inv = 0;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", vet+i);
	}
	mergesort(vet, 0, N-1);
	printf("inv = %lld:", inv);
	for(int i=0; i<N; i++) {
		printf(" %d", vet[i]);
	}
	printf("\n");
	return 0;
}