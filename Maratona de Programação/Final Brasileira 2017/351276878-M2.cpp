#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009
#define MOD 1000000007
typedef pair<int, int> ii;

int str[MAXN];
int n;
int RA[MAXN], tempRA[MAXN];
int SA[MAXN], tempSA[MAXN];
int c[MAXN];

void countingSort(int k) {
	int i, sum, maxi = max(302, n);
	memset(c, 0, sizeof(c));
	for (i = 0; i < n; i++) c[i+k < n ? RA[i+k] : 0]++;
	for (i = sum = 0; i < maxi; i++) {
		int t = c[i];
		c[i] = sum;
		sum += t;
	}
	for (i = 0; i < n; i++) tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
	for (i = 0; i < n; i++) SA[i] = tempSA[i];
}

void constructSA() {
	int i, k, r;
	for (i = 0; i < n; i++) RA[i] = str[i];
	for (i = 0; i < n; i++) SA[i] = i;
	for (k = 1; k < n; k <<= 1) {
		countingSort(k);
		countingSort(0);
		tempRA[SA[0]] = r = 0;
		for (i = 1; i < n; i++) tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i] + k] == RA[SA[i-1]+k]) ? r : ++r;
		for (i = 0; i < n; i++) RA[i] = tempRA[i];
		if (RA[SA[n-1]] == n-1) break;
	}
}

vector<int> re[100009];
vector<int> ans;

int main() {
	int col, k, val;
	scanf("%d", &col);
	
	n = 0;
	for (int c = 0; c < col; c++) {
		scanf("%d", &k);
		for (int i = 0; i < k; i++) {
			scanf("%d", &val);
			str[n] = val;
			
			re[c].push_back(n++);
		}
		str[n++] = 301;
		reverse(re[c].begin(), re[c].end());
	}
	
	constructSA();
	
	priority_queue<pair<int, ii> > pq;
	for(int i=0; i<col; i++) {
		pq.push(make_pair(-RA[re[i].back()], ii(i, str[re[i].back()])));
	//	printf("%d %d\n", str[re[i].back()], RA[re[i].back()]);
		re[i].pop_back();
	}
	
	while(!pq.empty()) {
		ans.push_back(pq.top().second.second);
		//printf("%d\n", ans.back());
		int i = pq.top().second.first;
		pq.pop();
		if (!re[i].empty()) {
			pq.push(make_pair(-RA[re[i].back()], ii(i, str[re[i].back()])));
			re[i].pop_back();
		}
	}
	
	
	long long p = 1;
	
	long long res = 0;
	for(int i=int(ans.size())-1; i>=0; i--) {
		p = (p*365)%MOD;
		long long v = ans[i];
		res += v*p;
		res %= MOD;
	}
	
	printf("%lld\n", res);
	return 0;
}
