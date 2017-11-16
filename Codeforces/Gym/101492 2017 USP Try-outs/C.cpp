#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009

vector<int> primeFac[MAXN], divisors[MAXN];
bitset<MAXN> bs;

void sieve() {
	bs.set();
	bs[0] = bs[1] = 0;
	for (int i = 2; i < MAXN; i++) {
		for (int j = i; j < MAXN; j += i) {
			divisors[j].push_back(i);
			if (bs[i]) primeFac[j].push_back(i);
			if (bs[i] && j>i) bs[j] = 0;
		}
	}
}

vector<int> index[MAXN];

int freq(int d, int l, int r) {
	const vector<int> & v = index[d];
	int ans = upper_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l);
	//printf("between %d and %d, %d factors of %d\n", l, r, ans, d);
	return ans;
}

int compute(int n, int l, int r) {
	const vector<int> & fac = primeFac[n];
	int ans = 0;
	for(int mask = 0; mask < (1<<fac.size()); mask++) {
		int cb = __builtin_popcount(mask);
		int cur = 1;
		for(int j=0; j<(int)fac.size(); j++) {
			if (mask & (1<<j)) {
				cur *= fac[j];
			}
		}
		if (cb % 2 == 0) ans -= freq(cur, l, r);
		else ans += freq(cur, l, r);
	}
	//printf("between %d and %d, %d non-coprimes of %d\n", l, r, ans, n);
	return ans;
}

int nxt[MAXN], arr[MAXN], N, sn, Q;

void computenxt() {
	for(int i=0; i<N; i++) {
		int lo = i;
		int hi = N;
		while(hi > lo + 1) {
			int mid = (hi + lo) / 2;
			if (compute(arr[i], i+1, mid) == mid-i) lo = mid;
			else hi = mid;
		}
		nxt[i] = hi;
		//printf("nxt [%d] = %d\n", i, nxt[i]);
	}
}

struct query {
	int l, r, id;
	bool ans;
	query() { l=r=id=-1; }
	query(int _id, int _l, int _r){
		id = _id; l = _l; r = _r;
	}
} qrs[MAXN];

bool lrcomp(query a, query b){
	if (a.l/sn != b.l/sn) return a.l/sn < b.l/sn;
  	return a.r > b.r;
}

bool idcomp(query a, query b){
	return a.id < b.id;
}

class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	int rsq(int i) { // returns RSQ(1, i)
		i++;
		int sum = 0;
		while(i > 0){
			sum += ft[i];
			i -= (i & -i);
		}
		return sum;
	}
	int rsq(int i, int j){
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, int v) {
		i++;
		while(i < (int)ft.size()) {
			ft[i] += v;
			i += (i & -i);
		}
	}
};

FenwickTree ft(1);
bool appeared[MAXN];

void check(int i) {
	if (i < 0 || i >= N) return;
	if (appeared[i]) {
		ft.update(nxt[i], -1);
	}
	else {
		ft.update(nxt[i], 1);
	}
	appeared[i] = !appeared[i];
}

void mo(){
	sn = sqrt(N);
	sort(qrs, qrs+Q, &lrcomp);
	ft = FenwickTree(N);
	memset(&appeared, false, sizeof appeared);
	int l = 1, r = 0;
	for(int i=0; i<Q; i++){
		query & q = qrs[i];
		while(r > q.r) check(r--);
		while(r < q.r) check(++r);
		while(l < q.l) check(l++);
		while(l > q.l) check(--l);
		//printf("(%d,%d) -> %d, %d\n", l, r, ft.rsq(l, r), r-l+1);
		q.ans = ft.rsq(l, r) != 0;
	}
	sort(qrs, qrs+Q, &idcomp);
}

int main() {
	sieve();
	
	scanf("%d %d", &N, &Q);
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
		for(int j=0; j<(int)divisors[arr[i]].size(); j++) {
			index[divisors[arr[i]][j]].push_back(i);
		}
	}
	
	computenxt();
	
	
	for(int j=0, l, r; j<Q; j++) {
		scanf("%d %d", &l, &r);
		qrs[j] = query(j, l-1, r-1);
	}
	
	mo();
	
	for(int j=0, l, r; j<Q; j++) {
		if (qrs[j].ans) printf("S\n");
		else printf("N\n");
	}
	
	return 0;
}