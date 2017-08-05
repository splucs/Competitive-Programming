#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define INF (1LL<<60)

typedef long long int ll;
typedef pair<ll, int> ii;

const ii neutralMin = ii(INF, -1); //comp(x, neutral) = x
const ii neutralMax = ii(-INF, -1); //comp(x, neutral) = x

class SegmentTree {
private:
	vector<ll> lazyS, lazyP;
	vector<ii> stMax, stMin;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r) {
		if (l == r) {
			st[p] = ii(1, l);
		}
		else {
			build(left(p), l, (l + r) / 2, A);
			build(right(p), (l + r) / 2 + 1, r, A);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	void push(int p, int l, int r) {
		st[p].first += lazyS[p]; 		    //Caso RMQ
		if (l != r) {
			lazyS[right(p)] += lazyS[p];
			lazyS[left(p)] += lazyS[p];
		}
		lazyS[p] = 0;
		st[p].first += lazyP[p]; 		    //Caso RMQ
		if (l != r) {
			lazyP[right(p)] += lazyP[p];
			lazyP[left(p)] += lazyP[p];
		}
		lazyP[p] = 0;
	}
	void updateS(int p, int l, int r, int a, int b, int k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazyS[p] = k; push(p, l, r);
		}
		else {
			update(left(p), l, (l + r) / 2, a, b, k);
			update(right(p), (l + r) / 2 + 1, r, a, b, k);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	void updateP(int p, int l, int r, int a, int b, int k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazyP[p] = k; push(p, l, r);
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
	SegmentTree(int N) {
		size = N;
		st.assign(4 * size, neutral);
		lazyS.assign(4 * size, 0);
		lazyP.assign(4 * size, 0);
		build(1, 0, size - 1);
	}
	int query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void updateS(int a, int b, int k) { updateS(1, 0, size - 1, a, b, k); }
	void updateP(int a, int b, int k) { updateP(1, 0, size - 1, a, b, k); }
};

SegmentTree st(MAXN);


/*
 * ALGORITMO DE MO
 */
int arr[MAXN], N, sn, Q;
bool appeared[MAXN];

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

ll freq[MAXN], curAns;
void check(int i) {
	if (i < 0 || i >= N) return;
	if (appeared[i]) {
		freq[arr[i]]--;
		if (freq[arr[i]] == 0) curAns--;
	}
	else {
		st.updateS(i+1, N-1, arr[i]);
		st.updateP(i, i, arr[i]);
		if (freq[arr[i]] == 0) curAns++;
		freq[arr[i]]++;
	}
	appeared[i] = !appeared[i];			//mo array
}

void mo(){
	sn = sqrt(N);
	sort(qrs, qrs+Q, &lrcomp);
	memset(&freq, 0, sizeof freq);
	memset(&appeared, false, sizeof appeared);
	int l = 1, r = 0;
	curAns = 0;
	for(int i=0; i<Q; i++){
		query & q = qrs[i];
		while(r > q.r) check(r--);
		while(r < q.r) check(++r);
		while(l < q.l) check(l++);
		while(l > q.l) check(--l);
		q.ans = curAns;
	}
	sort(qrs, qrs+Q, &idcomp);
}

int main() {
}