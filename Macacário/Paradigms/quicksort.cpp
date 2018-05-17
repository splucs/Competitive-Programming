#include <cstdio>
#include <algorithm>
using namespace std;

void quicksort(int* arr, int l, int r) {
    if (l >= r) return;
    int mid = rand()%(r-l+1) + l;
    int pivot = arr[mid];
    swap(arr[mid],arr[l]);
    int i = l + 1, j = r;
    while (i <= j) {
        while(i <= j && arr[i] <= pivot) i++;
        while(i <= j && arr[j] > pivot) j--;
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[i-1], arr[l]);
    quicksort(arr, l, i-2);
    quicksort(arr, i, r);
}

void quicksort(int* arr, int l, int r) {
    if (l >= r) return;
    int i, m = rand()%(r-l+1) + l;
	swap(arr[l], arr[m]);
	for(m = l, i = l + 1; i <= r; i++) {
		if (x[i] < x[l]) swap(arr[++m], arr[i]);
	}
    swap(arr[l], arr[m]);
    quicksort(arr, l, m-1);
    quicksort(arr, i, m+1);
}

int main() {
    int arr[8] = {110, 5, 10, 3 ,10, 100, 1, 23};
    quicksort(arr, 0, 7);
    for(int i=0; i<8; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}