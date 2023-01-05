#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF (1LL<<60)

typedef long long ll;
typedef pair<ll, int> ii;

const ii neutral = ii(-INF, -1); //comp(x, neutral) = x
ii comp(ii a, ii b) {
	if (a.first > 0) return a;
	if (b.first > 0) return b;
	return max(a, b);
}

class SegmentTree {
private:
	vector<ll> lazy;
	vector<ii> st;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r) {
		if (l == r) {
			st[p] = ii(-1, l);
		}
		else {
			build(left(p), l, (l + r) / 2);
			build(right(p), (l + r) / 2 + 1, r);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	void push(int p, int l, int r) {
		st[p].first += lazy[p]; 		    //Caso RMQ
		if (l != r) {
			lazy[right(p)] += lazy[p];
			lazy[left(p)] += lazy[p];
		}
		lazy[p] = 0;
	}
	void update(int p, int l, int r, int a, int b, ll k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazy[p] = k; push(p, l, r);
		}
		else {
			update(left(p), l, (l + r) / 2, a, b, k);
			update(right(p), (l + r) / 2 + 1, r, a, b, k);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	ii query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		ii p1 = query(left(p), l, (l + r) / 2, a, b);
		ii p2 = query(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree(int _size) {
		size = _size;
		st.assign(4 * size, neutral);
		lazy.assign(4 * size, 0);
		build(1, 0, size - 1);
	}
	ii query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, ll k) { update(1, 0, size - 1, a, b, k); }
};

SegmentTree st(MAXN);


/*
 * ALGORITMO DE MO
 */
int N, sn, Q, sz;
bool appeared[MAXN];
map<ll, int> pos, freq;
ll inv[MAXN], arr[MAXN];

struct query {
	int l, r, id;
	ll ans;
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

void check(int i) {
	if (i < 0 || i >= N) return;
	if (appeared[i]) {
		freq[arr[i]]--;
		if(freq[arr[i]] == 0) st.update(pos[arr[i]], pos[arr[i]], -arr[i]);
		st.update(pos[arr[i]]+1, sz, arr[i]);
		//printf("removed %lld\n", arr[i]);
	}
	else {
		freq[arr[i]]++;
		if(freq[arr[i]] == 1) st.update(pos[arr[i]], pos[arr[i]], arr[i]);
		st.update(pos[arr[i]]+1, sz, -arr[i]);
		//printf("added %lld\n", arr[i]);
	}
	/*for(int j=0; j<sz; j++) {
		printf("%d(%lld): %lld   ", j, inv[j], st.query(j, j));
	}
	printf("\n");*/
	appeared[i] = !appeared[i];
}

void mo(){
	sn = sqrt(N);
	sort(qrs, qrs+Q, &lrcomp);
	memset(&appeared, false, sizeof appeared);
	int l = 1, r = 0;
	for(int i=0; i<Q; i++){
		query & q = qrs[i];
		while(r > q.r) check(r--);
		while(r < q.r) check(++r);
		while(l < q.l) check(l++);
		while(l > q.l) check(--l);
		ii cur = st.query(0, sz);
		if (cur.first >= 1) q.ans = inv[cur.second] - cur.first;
		else q.ans = -st.query(sz, sz).first;
	}
	sort(qrs, qrs+Q, &idcomp);
}

int main() {
	scanf("%d %d", &N, &Q);
	for(int i=0; i<N; i++) {
		scanf("%lld", &arr[i]);
		pos[arr[i]] = -1;
	}
	sz = 0;
	for(map<ll, int>::iterator it = pos.begin(); it != pos.end(); it++) {
		it->second = sz;
		inv[sz] = it->first;
		freq[it->first] = 0;
		sz++;
	}
	inv[sz] = 0;
	pos[0] = sz++;
	int l, r;
	for(int i=0; i<Q; i++) {
		scanf("%d %d", &l, &r);
		qrs[i] = query(i, l-1, r-1);
	}
	mo();
	for(int i=0; i<Q; i++) {
		printf("%lld\n", qrs[i].ans);
	}
	return 0;
}