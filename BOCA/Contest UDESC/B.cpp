#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1e(x,n) for(int x=1; x<=n; x++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

char w[20009];

vector<string> letra;
int main() {
	int n;
	scanf("%d %s", &n, &w);
	letra.pb("***************");
	letra.pb("*.**.**..*.**..");
	letra.pb("*******..*.****");
	letra.pb("*.**.**..*.**..");
	letra.pb("*.*************");

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < n; j++) {
			int st = (w[j] - 'A')*3;
			for (int k = 0; k < 3; k++) {
				printf("%c", letra[i][k+st]);
			}
		}
		printf("\n");
	}
}
