#include <bits/stdc++.h>
using namespace std;
#define MAXN 250009
#define MAXC 12
#define MAXLOGN 20
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

class SegmentTree {
	vector<int> a;
	int n;
public:
	SegmentTree(int sz = 0) {
		for(n = 1; n < sz; n <<= 1);
		a.assign(n << 1, INF);
	}
	void update(int i, int x) {
		a[i += n] = x;
		for(i >>= 1; i; i >>= 1)
			a[i] = min(a[i<<1], a[1+(i<<1)]);
	}
	int query(int l, int r) {
		int ans = INF;
		for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = min(ans, a[l++]);
			if (r & 1) ans = min(ans, a[--r]);
		}
		return ans;
	}
};

SegmentTree st;

class SuffixArray {
	int RA[MAXN], tempRA[MAXN];
	int tempSA[MAXN], c[MAXN], n;
	void bucket(int k, int SA[]) {
		int sum = 0, maxi = max(300, n);
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
public:
	void constructSA(char str[], int SA[]) {
		n = strlen(str);
		str[n++] = '$', str[n] = 0;
		FOR(i, n) RA[i] = str[i];
		FOR(i, n) SA[i] = i;
		for(int k = 1, r; k < n; k <<= 1) {
			bucket(k, SA);
			bucket(0, SA);
			tempRA[SA[0]] = r = 0;
			for(int i = 1; i < n; i++)
				tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
			FOR(i, n) RA[i] = tempRA[i];
			if (RA[SA[n-1]] == n-1) break;
		}
	}
};

SuffixArray sads;
char str[MAXN];
int SA[MAXN], nxt[MAXN], prv[MAXN];
int n, ans[MAXN], active[MAXN];
multiset<int> dist[MAXN];

void add(int i) {
	int d = nxt[i] - i;
	dist[d].insert(i);
	st.update(d, *dist[d].begin());
}

void rem(int i) {
	int d = nxt[i] - i;
	dist[d].erase(dist[d].find(i));
	if (dist[d].empty()) st.update(d, INF);
	else st.update(d, *dist[d].begin());
}

void deactivate(int i) {
	assert((i > 0 && i < n) && "pos 0 should always be active");
	printf("deactivating %d\n", i);

	rem(i);
	rem(prv[i]);
	nxt[prv[i]] = nxt[i];
	prv[nxt[i]] = prv[i];
	add(prv[i]);
	active[i] = false;
}

int main() {
	while(scanf(" %s", str) != EOF) {
		sads.constructSA(str, SA);
		n = strlen(str);
		FOR(i, n) {
			printf("%2d %2d %s\n", i, SA[i], str + SA[i]);
			active[i] = 1;
		}

		st = SegmentTree(n);

		FOR(i, n-1) {
			nxt[i] = i+1;
			prv[i] = i-1;
			add(i);
		}

		int l = 1, r = --n;
		mset(ans, INF);
		FOR(i, n) {
			int s = i+1;
			while(SA[l]+i >= n || str[SA[l]+i] != str[i])
				deactivate(SA[l++]);
			while(SA[r]+i >= n || str[SA[r]+i] != str[i])
				deactivate(SA[r--]);
			printf("first %d, [%d,%d]\n", s, l, r);

			int j = st.query(s+1, n);
			if (j == INF) j = n;
			while(j+s > n) j = prv[j];
			j += s;
			printf("pos %d is the last covered with size %d\n", j, s);
			FOR(k, n) printf("%d", active[k]);
			printf("\n");
			ans[j] = min(ans[j], s);
		}

		REP1(i, n-1) ans[i] = min(ans[i], ans[i+1]);
		FOR1(i, n) printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}