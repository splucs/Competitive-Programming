#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXM 100009
#define MAXLOGN 20
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> ii;

int RA[MAXN], tempRA[MAXN];
int tempSA[MAXN], c[MAXN], n;

void bucket(int k, int SA[]) {
	int sum = 0, maxi = max(n, 309);
	mset(c, 0);
	FOR(i, n) c[i+k < n ? RA[i+k] : 0]++;
	FOR(i, maxi) {
		int t = c[i];
		c[i] = sum;
		sum += t;
	}
	FOR(i, n) tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
	FOR(i, n) SA[i] = tempSA[i];
}

void suffixArray(int str[], int SA[]) {
	int r;
	FOR(i, n) RA[i] = str[i];
	FOR(i, n) SA[i] = i;
	for(int k = 1; k < n; k <<= 1) {
		bucket(k, SA);
		bucket(0, SA);
		tempRA[SA[0]] = r = 0;
		for(int i = 1; i < n; i++) {
			tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
		}
		FOR(i, n) RA[i] = tempRA[i];
		if (RA[SA[n-1]] == n-1) break;
	}
}

int index[MAXN];
int arr[MAXN], SA[MAXN], inv[MAXN];
vector<int> ans;

int main() {
	int m;
	scanf("%d", &m);
	n = 0;
	FOR(j, m) {
		int k, x;
		scanf("%d", &k);
		index[j] = n;
		while(k --> 0) {
			scanf("%d", &x);
			arr[n++] = x;
		}
		arr[n++] = 305;
	}
	suffixArray(arr, SA);
	FOR(i, n) inv[SA[i]] = i;
	priority_queue<ii> pq;
	FOR(j, m) {
		int i = index[j];
		assert(arr[i] <= 300);
		pq.push({-inv[i], i});
	}
	while(!pq.empty()) {
		int i = pq.top().se;
		pq.pop();
		ans.pb(arr[i]);
		assert(arr[i] <= 300);
		i++;
		if (arr[i] == 305) continue;
		pq.push({-inv[i], i});
	}
	int sum = 0;
	for(int x : ans) {
		//printf("x = %d\n", x);
		sum = (sum*365ll + x) % MOD;
	}
	sum = (sum*365ll) % MOD;
	printf("%d\n", sum);
	return 0;
}