#include <map>
#include <stdio.h>
#include <algorithm>
using namespace std;

long long arr[4000005];

int main() {
	int n;
	long long tmp;
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%I64d", &arr[i]);
	}

	sort(arr, arr + n);
	
	for (int i = 0; i < n; i++) {
		if ((i == 0 || arr[i] != arr[i-1]) && (i == n-1 || arr[i] != arr[i+1])) {
			printf("%I64d\n", arr[i]);
		}
	}
	return 0;
}