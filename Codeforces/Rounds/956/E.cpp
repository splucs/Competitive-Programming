#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

struct box {
	int a, b;
} arr[MAXN];
int N, L, R, H;
int dp[2][MAXN];

bool comp(box a, box b) {
	if (a.b != b.b) return a.b < b.b;
	return a.a > b.a;
}

int main() {
	scanf("%d %d %d", &N, &L, &R);
	H = 0;
	FOR(i, N) {
		scanf("%d", &arr[i].a);
		H += arr[i].a;
	}
	FOR(i, N) {
		scanf("%d", &arr[i].b);
	}

	L = H - L;
	R = H - R;
	swap(L, R);
	sort(arr, arr+N, comp);

	for(int i = N; i >= 0; i--) {
		for(int h = H; h >= 0; h--) {
			if (i == N || h + arr[i].a > H) {
				dp[i%2][h] = 0;
			}
			else {
				int cur = 0;
				if (h + arr[i].a >= L && h + arr[i].a <= R && arr[i].b == 1) cur = 1;
				dp[i%2][h] = max(dp[(i+1)%2][h], cur + dp[(i+1)%2][h+arr[i].a]);
			}
		}
	}

	printf("%d\n", dp[0][0]);
	return 0;
}