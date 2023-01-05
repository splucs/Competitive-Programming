#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 100009
using namespace std;

typedef pair<int, int> ii;

int det[MAXN], a11, a12, a21, a22;
int nxt[MAXN];

const ii neutral = ii(-1, -INF); //comp(x, neutral) = x
ii comp(ii a, ii b) {
	if (a.second == b.second) return a.first < b.first ? a : b;
	return a.second > b.second ? a : b;
}

class SegmentTree {
private:
	vector<ii> st;
	vector<int> lazy;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = ii(l, A[l]);
		}
		else {
			build(left(p), l, (l + r) / 2, A);
			build(right(p), (l + r) / 2 + 1, r, A);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	void push(int p, int l, int r) {
		st[p].second += lazy[p]; 		    //Caso RMQ
		if (l != r) {
			lazy[right(p)] += lazy[p];
			lazy[left(p)] += lazy[p];
		}
		lazy[p] = 0;
	}
	void update(int p, int l, int r, int a, int b, int k) {
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
	SegmentTree(int* begin, int* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		lazy.assign(4 * size, 0);
		build(1, 0, size - 1, begin);
	}
	ii query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, int k) { update(1, 0, size - 1, a, b, k); }
};

int startweek, startyear;

ii getDate(int a) {
	a += startweek;
	return ii((a-1)%52 + 1, (a-1)/52 + startyear);
}
SegmentTree st(det, det+1);

inline int getNxt(int i){
	return st.query(i, i).second;
}

class SegmentTreeS {
private:
	vector<int> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = A[l] > 0 ? 1 : A[l] == 0 ? 0 : -1;
			pos[l] = p;
		}
		else {
			build(left(p), l, (l + r) / 2, A);
			build(right(p), (l + r) / 2 + 1, r, A);
			st[p] = st[left(p)] * st[right(p)];
		}
	}
	int find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return 1;
		if (l >= a && r <= b) return st[p];
		int p1 = find(left(p), l, (l + r) / 2, a, b);
		int p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return p1*p2;
	}
public:
	SegmentTreeS(int* begin, int* end) {
		size = (int)(end - begin);
		st.assign(4 * size, 1);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, begin);
	}
	int query(int a, int b) { return find(1, 0, size - 1, a, b); }
	void update(int n, int num) {
		st[pos[n]] = num > 0 ? 1 : num == 0 ? 0 : -1;
		n = parent(pos[n]);
		while (n>0) {
			st[n] = st[left(n)] * st[right(n)];
			n = parent(n);
		}
	}
};

SegmentTreeS prod(det, det+1);

int main() {
	int T, N, Q;
	char op;
	scanf("%d", &T);
	for(int exp = 1; exp <= T; exp++) {
		if (exp > 1) printf("\n");
		printf("Experimento #%d:\n", exp);
		scanf("%d %d", &startweek, &startyear);
		scanf("%d", &N);
		for(int i=0; i<N; i++){
			scanf("%d %d %d %d", &a11, &a12, &a21, &a22);
			det[i] = a11*a22 - a12*a21;
		}
		det[N] = 0;
		nxt[N] = 0;
		for(int i=N-1; i>=0; i--) {
			if (det[i] == 0) nxt[i] = 0;
			else nxt[i] = 1 + nxt[i+1];
		}
		st = SegmentTree(nxt, nxt+N+1);
		prod = SegmentTreeS(det, det+N+1);
		scanf("%d", &Q);
		while(Q-->0) {
			/*printf("Q=%d nxt:", Q);
			for(int i=0; i<=N; i++) {
				printf(" %d", getNxt(i));
			}
			printf("\n");*/
			scanf(" %c", &op);
			if (op == 'M'){
				ii ans = st.query(0, N-1);
				//printf("ans = (%d,%d)\n", ans.first, ans.second);
				int s = ans.first;
				int t = s + ans.second - 1;
				ii d1 = getDate(s);
				ii d2 = getDate(t);
				printf("Maior periodo consistente: %02d/%04d a %02d/%04d\n", d1.first, d1.second, d2.first, d2.second);
			}
			else if (op == 'U'){
				int t, nwd;
				scanf("%d %d %d %d %d", &t, &a11, &a12, &a21, &a22);
				t--;
				nwd = a11*a22 - a12*a21;
				if ((nwd == 0 && det[t] != 0) || (nwd != 0 && det[t] == 0)){
					int lo = 0;
					int hi = t;
					int sum = t + getNxt(t);
					if (lo + st.query(lo, lo).second == sum) hi = lo;
					else{
						while(hi > lo+1){
							int mid = (hi + lo)/2;
							if (mid + getNxt(mid) == sum) hi = mid;
							else lo = mid;
						}
					}
					int dnxt = st.query(t, t).second;
					if (det[t] == 0) dnxt = 1 + getNxt(t+1);
					else dnxt = -getNxt(t);
					st.update(hi, t, dnxt);
				}
				det[t] = nwd;
				prod.update(t, nwd);
			}
			else{
				int a, b;
				scanf("%d %d", &a, &b);
				a--; b--;
				ii d1 = getDate(a);
				ii d2 = getDate(b);
				int dn = getNxt(a);
				printf("%02d/%04d a %02d/%04d: ", d1.first, d1.second, d2.first, d2.second);
				if (a + dn > b) printf("dados consistentes (D %c 0)\n", prod.query(a, b) > 0 ? '>' : '<');
				else printf("dados corrompidos\n");
			}
		}
	}
	return 0;
}