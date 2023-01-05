#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 500009
using namespace std;

typedef long long ll;
const int neutral = INF;
int comp(int a, int b) {
	return min(a, b);
}

class SegmentTree {
private:
	vector<int> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = A[l];
			pos[l] = p;
		}
		else {
			build(left(p), l, (l + r) / 2, A);
			build(right(p), (l + r) / 2 + 1, r, A);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	int find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int p1 = find(left(p), l, (l + r) / 2, a, b);
		int p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree() {}
	SegmentTree(int* begin, int* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, begin);
	}
	int query(int a, int b) { return find(1, 0, size - 1, a, b); }
	void update(int n, int num) {
		st[pos[n]] = num;
		n = parent(pos[n]);
		while (n>0) {
			st[n] = comp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

int N;

class FenwickTree {
private:
	vector<ll> ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	ll rsq(int i) { // returns RSQ(1, i)
	    i++;
		ll sum = 0;
		while(i > 0){
			sum = (sum + ft[i]);
			i -= (i & -i);
		}
		return sum;
	}
	ll rsq(int i, int j){
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, ll v) {
	    i++;
		while(i < (int)ft.size()) {
			ft[i] = (v + ft[i]);
			i += (i & -i);
		}
	}
};

int vet[MAXN], f[MAXN], b[MAXN];
SegmentTree st1f, st1b, st2f, st2b;
FenwickTree ft(1);

int main(){
    int T, Q, op, i, val;
    T=1;
    for(int t=0; t<T; t++){
        ll h;
        scanf("%d", &N);
        ft = FenwickTree(N);
        for(i=0; i<N; i++){
            scanf("%d", &vet[i]);
            ft.update(i, (ll)vet[i]);
            f[i] = vet[i] - i;
            b[i] = vet[i] - (N-i-1);
        }
        st2f = SegmentTree(f, f+N);
        st2b = SegmentTree(b, b+N);
        f[0] = 1; f[N-1] = 1 - (N-1);
        b[N-1] = 1; b[0] = 1 - (N-1);
        st1f = SegmentTree(f, f+N);
        st1b = SegmentTree(b, b+N);
        scanf("%d", &Q);
        for(int q=0; q<Q; q++){
            scanf("%d %d %d", &op, &i, &val);
            i--;
            if (op == 1){
                ft.update(i, (ll)(val-vet[i]));
                vet[i] = val;
                f[i] = vet[i] - i;
                b[i] = vet[i] - (N-i-1);
                st2f.update(i, f[i]);
                st2b.update(i, b[i]);
                if (i > 0 && i < N-1){
                    st1f.update(i, f[i]);
                    st1b.update(i, b[i]);
                }
            }
            else if (op == 2){
                if (val == 1){
                    h = min(i+st1f.query(0, i), N-1-i+st1b.query(i, N-1));
                }
                else if (val == 0){
                    h = min(i+st2f.query(0, i), N-1-i+st2b.query(i, N-1));
                }
                ll tri = h*h;
                if (i-h+1 < 0){
                    ll d = 0-(i-h+1);
                    tri -= (d*(d+1))/2;
                }
                if (i+h-1 > N-1){
                    ll d = (i+h-1) - (N-1);
                    tri -= (d*(d+1))/2;
                }
                printf("%lld %lld\n", h, ft.rsq(max(0ll, i-h+1ll), min(N-1ll, i+h-1)) - tri);
            }
        }
    }
    return 0;
}
