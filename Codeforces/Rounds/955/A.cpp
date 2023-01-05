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

int ceil(int a, int b) {
	if (a % b == 0) return a/b;
	else return a/b + 1;
}

int main() {
	int h, m;
	scanf("%d %d", &h, &m);
	int H, D, C, N;
	scanf("%d %d %d %d", &H, &D, &C, &N);
	double opt1 = ceil(H, N)*C;
	int t = 20*60 - m - h*60;
	if (t < 0) t = 0; 
	double opt2 = ceil(H + t*D, N)*C*0.8;
	printf("%.6f\n", min(opt1, opt2));
	return 0;
}