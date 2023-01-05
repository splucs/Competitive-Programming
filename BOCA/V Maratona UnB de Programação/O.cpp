#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
typedef pair<int,int> ii;

ii din[MAXN];
int bleft[MAXN], bright[MAXN], arr[MAXN];
int k;

int neutral = 0;
int comp(int a, int b) {
	return k==0?min(a,b):max(a,b);
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
		st[pos[n]] = num;
		n = parent(pos[n]);
		while (n>0) {
			st[n] = comp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

int main(){
	int T,N,X,R,l,r;
	scanf("%d",&T);
	while (T-->0){
		scanf("%d",&N);
		for (int i=0;i<N;i++){
			scanf("%d%d",&X,&R);
			bleft[i] = bright[i] = i;
			din[i] = ii(X,R);
			arr[i] = X;
		}
		sort(din,din+N);
		sort(arr,arr+N);
		
		neutral = 1000000009;
		k = 0;
		SegmentTree St(bleft,bleft+N);
		for (int i=0;i<N;i++){
			l = din[i].first-din[i].second;
			int pos = lower_bound(arr,arr+N,l)-arr;
			bleft[i] = St.query(pos,i);
			St.update(i,bleft[i]);
		}
		neutral = 0;
		k = 1;
		SegmentTree St1(bright,bright+N);
		for (int i=N-1;i>=0;i--){
			r = din[i].first+din[i].second;
			int pos = upper_bound(arr,arr+N,r)-arr-1;
			//cout<<r<<" "<<pos<<endl;
			bright[i] = St1.query(i,pos);
			St1.update(i,bright[i]);
		}
		//for (int i=0;i<N;i++)cout<<bleft[i]<<" "<<bright[i]<<endl;
		int ans = -1;
		for (int i=0;i<N;i++)ans = max(ans,bright[i]-bleft[i]+1);
		printf("%d\n",ans);
	}
}