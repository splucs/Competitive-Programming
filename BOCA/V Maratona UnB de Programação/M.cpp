#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int arr[MAXN];
int ans[MAXN];

int gcd(int a,int b){
	if (b==0)return a;
	return gcd(b,a%b);
}

int neutral = 0;
int comp(int a, int b) {
	return gcd(a,b);
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
	int T,N,M,a,b;
	cin>>T;
	
	while(T-->0){
		cin>>N>>M;
		for (int i=0;i<N;i++)cin>>arr[i];
		SegmentTree sT(arr,arr+N);
		for (int i=0;i<M;i++){
			cin>>a>>b;
			ans[i] = sT.query(a-1,b-1);
		}
		cout<<ans[0];
		for (int i=1;i<M;i++)cout<<" "<<ans[i];
		cout<<endl;
	}
}