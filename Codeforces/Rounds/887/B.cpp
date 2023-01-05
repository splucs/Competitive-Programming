#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

#define FOR(i, n) for(int (i) = 0; (i)<(n); (i)++)

int arr[18];
bool ok[MAXN];

int main() {
	int N;
	scanf("%d", &N);
	FOR(i, N*6) scanf("%d", &arr[i]);
	memset(&ok, false, sizeof ok);
	FOR(i, N*6) FOR(j, N*6) FOR(k, N*6){
		if (i/6 != j/6 && i/6 != k/6 && j/6 != k/6) ok[arr[i]*100 + arr[j]*10 + arr[k]] = true;
		if (j/6 != k/6) ok[arr[j]*10 + arr[k]] = true;
		ok[arr[k]] = true;
	}
	int cnt = 1;
	while(ok[cnt]) cnt++;
	cnt--;
	printf("%d\n", cnt);
	return 0;
}