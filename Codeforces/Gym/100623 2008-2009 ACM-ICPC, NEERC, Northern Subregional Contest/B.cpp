#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
#define MAXN 200009

const int neutral = -INF;
int comp(int a, int b) {
	return max(a, b);
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
	SegmentTree(int* begin, int* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, begin);
	}
	int query(int a, int b) { return find(1, 0, size - 1, a, b); }
	void update(int n, int num) {
		st[pos[n]] -= num;
		n = parent(pos[n]);
		while (n>0) {
			st[n] = comp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

int v[MAXN], h, n, w, q;

int main() {
    freopen("billboard.in", "r", stdin);
    freopen("billboard.out", "w", stdout);

    scanf("%d %d %d", &h, &w, &n);
    h = min(h, n);
    for(int i=0; i<h; i++){
        v[i] = w;
    }
    SegmentTree st(v, v+h);
    while(n--){
        scanf("%d", &q);
        int lo = 0;
        int hi = h;
        if (st.query(0, 0) >= q){
            hi = 0;
        }
        else{
            int mid;
            while(hi > lo+1) {
                mid = (hi+lo)/2;
                if (st.query(0, mid) < q) lo = mid;
                else hi = mid;
            }
        }

        if (hi >= h) {
            printf("-1\n");
        }
        else{
            printf("%d\n", hi+1);
            st.update(hi, q);
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}