#include <cstdio>
#include <algorithm>
using namespace std;

void quicksort(int* arr, int l, int r) {
	if (l >= r) return;
	int mid = l + (r - l) / 2;
	int pivot = arr[mid];
	swap(arr[mid], arr[l]);
	int i = l + 1, j = r;
	while (i <= j) {
		while (i <= j && arr[i] <= pivot) i++;
		while (i <= j && arr[j] > pivot) j--;
		if (i < j) swap(arr[i], arr[j]);
	}
	swap(arr[i - 1], arr[l]);
	quicksort(arr, l, i - 2);
	quicksort(arr, i, r);
}