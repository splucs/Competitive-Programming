#include <cstdio>
#define MAXN 100009


int aux[MAXN];
long long mergesort(int arr[], int l, int r) {
	if (l == r) return 0;
	int mid = (l + r)/2;
	long long inv = 0;
	inv += mergesort(arr, l, mid);
	inv += mergesort(arr, mid+1, r);
	int i = l, j = mid + 1, k = l;
	while(i <= mid && j <= r) {
		if (arr[i] > arr[j]) {
			aux[k++] = arr[j++];
			inv += j - k;
		}
		else aux[k++] = arr[i++];
	}
	while(i <= mid) aux[k++] = arr[i++];
	for(i = l; i < k; i++) arr[i] = aux[i];
	return inv;
}

long long int inv;

int main()
{
	int N, vet[MAXN];
	inv=0;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", vet+i);
	}
	inv = mergesort(vet, 0, N-1);
	printf("inv = %lld:", inv);
	for(int i=0; i<N; i++) {
		printf(" %d", vet[i]);
	}
	printf("\n");
	return 0;
}