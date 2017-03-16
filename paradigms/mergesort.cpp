#include <cstdio>
#define MAXN 100009

typedef long long int ll;
ll inv;
int N, vet[MAXN], aux[MAXN];

void mergesort(int a, int b) {
	if (a == b) return;
	int mid = (a + b) / 2;
	mergesort(a, mid);
	mergesort(mid + 1, b);
	int p = a, q = mid + 1, k = a;
	while (p <= mid && q <= b) {
		if (vet[p]>vet[q]) {
			aux[k++] = vet[q++];
			inv += (ll)(q - k);
		}
		else aux[k++] = vet[p++];
	}
	while (p <= mid) aux[k++] = vet[p++];
	while (q <= b) aux[k++] = vet[q++];
	for (int i = a; i <= b; i++) vet[i] = aux[i];
}