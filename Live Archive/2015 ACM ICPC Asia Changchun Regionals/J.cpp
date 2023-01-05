#include <bits/stdc++.h>
using namespace std;
#define MAXN 10000009
#define MSK (1LL<<32)

int l[MAXN], r[MAXN], sz, root;

int newnode() {
	l[sz] = -1;
	r[sz] = -1;
	sz++;
	return sz-1;
}

typedef long long ll;
map<int, pair<int, int> > mp;

void insert(ll num, int i, int j) {
	int cur = root;
	//printf("inserting num %lld\n", num);
	for(ll sig = MSK; sig > 0; sig >>= 1) {
		if (sig & num) {
			if (r[cur] == -1) r[cur] = newnode();
			//printf("r[%d] = %d\n", cur, r[cur]);
			cur = r[cur];
		}
		else {
			if (l[cur] == -1) l[cur] = newnode();
			//printf("l[%d] = %d\n", cur, l[cur]);
			cur = l[cur];
		}
	}
	mp[cur] = make_pair(i, j);
}

ll find(ll num, int k, int nd, ll sig) {
	if (nd == -1) return -1;
	//printf("searching %lld in node %d\n", num, nd);
	if (sig == 0) {
		pair<int, int> pa = mp[nd];
		if (k == pa.first || k == pa.second) return -1;
		return 0;
	}
	if (num & sig) {
		ll cur = find(num, k, l[nd], sig >> 1);
		if (cur != -1) return sig + cur;
		cur = find(num, k, r[nd], sig >> 1);
		if (cur != -1) return cur;
		return -1;
	}
	else {
		ll cur = find(num, k, r[nd], sig >> 1);
		if (cur != -1) return sig + cur;
		cur = find(num, k, l[nd], sig >> 1);
		if (cur != -1) return cur;
		return -1;
	}
}

ll s[1009];

int main() {
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		sz = 0;
		root = newnode();
		mp.clear();
		for(int i=0; i<N; i++) {
			scanf("%lld", &s[i]);
			for(int j=0; j<i; j++) {
				insert(s[i] + s[j], i, j);
			}
		}
		ll ans = 0;
		for(int k=0; k<N; k++) {
			ans = max(ans, find(s[k], k, root, MSK));
			//printf("find(%d) = %lld\n", k, find(s[k], k, root, MSK));
		}
		printf("%lld\n", ans);
	}
	return 0;
}