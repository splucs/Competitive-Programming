#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define EPS 1e-9
#define FOR(x, n) for(int x = 0; x < n; x++)

long long arr[MAXN];

int main() {
	int n;
	long long ans = 0;
	scanf("%d", &n);
	FOR(x, n) {
		scanf("%I64d", &arr[x]);
	}
	sort(arr,arr+n);
	if (n<=2)cout<<arr[n-1]<<endl;
	else {
		long long a0 = arr[0], a1 = arr[1];
		int i = n-1;
		while (i>2 && arr[i-1]+a0>2*a1)ans+=a0+2*a1+arr[i],i-=2;
		while (i>1)ans+=a0+arr[i--];
		ans+=a1;
		cout<<ans<<endl;
	}
	
}