#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

char str[MAXN];
int arr[MAXN];
typedef long long ll;

int main() {
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %s", &N, str);
		int last = -1, k=0;
		for(int i=0; i<N; i++) {
			if (str[i] == '1') {
				arr[k++] = i - last;
				last = i;
			}
		}
		arr[k++] = N-last;
		ll s[2];
		s[0] = s[1] = 0;
		ll ans = 0;
		for(int i=0; i<k; i++) {
			s[i%2] += arr[i];
			if (i+3 < k) ans += s[i%2]*arr[i+3];
			if (i > 0) ans += (arr[i]-1ll)*1ll*(arr[i-1]-1ll);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}