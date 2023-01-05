#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int arr[MAXN];

int main() {
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++) scanf("%d", &arr[i]);
	if (N % 2 == 0 || arr[0] % 2 == 0 || arr[N-1] % 2 == 0) printf("No\n");
	else printf("Yes\n");
	return 0;
}