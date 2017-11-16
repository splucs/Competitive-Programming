#include <bits/stdc++.h>
using namespace std;
#define MAXN 70009

struct entry1 {
	int a, b, t, c;
	entry1() {}
	entry1(int _a, int _b, int _t, int _c) {
		a = _a;
		b = _b;
		t = _t;
		c = _c;
	}
	bool operator < (entry1 other) {
		if (a != other.a) return a < other.a;
		if (b != other.b) return b < other.b;
		return t < other.t;
	}
	bool operator ==(entry1 other) {
		return a==other.a && b==other.b && t==other.t;
	}
} t1[MAXN];

struct entry2 {
	int a, b, t, c, d;
	entry2() {}
	entry2(int _a, int _b, int _c, int _t, int _d) {
		a = _a;
		b = _b;
		t = _t;
		c = _c;
		d = _d;
	}
} t2[MAXN];

struct entry3 {
	int a, b, t1, c1, t2, c2, d2;
	entry3() {}
	entry3(int _a, int _b, int _t1, int _c1, int _c2, int _t2, int _d2) {
		a = _a;
		b = _b;
		t1 = _t1;
		t2 = _t2;
		c1 = _c1;
		c2 = _c2;
		d2 = _d2;
	}
	bool operator < (entry3 other) {
		if (c1 != other.c1) return c1 < other.c1;
		if (a != other.a) return a < other.a;
		if (b != other.b) return b < other.b;
		if (t1 != other.t1) return t1 < other.t1;
		if (c2 != other.c2) return c2 < other.c2;
		return t2 < other.t2;
	}
};
vector<entry3> ans;

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	int a, b, c, d, t;
	for(int i=0; i<N; i++) {
		scanf("%d %d %d %d", &a, &b, &t, &c);
		t1[i] = entry1(a, b, t, c);
	}
	for(int i=0; i<M; i++) {
		scanf("%d %d %d %d %d", &a, &b, &c, &t, &d);
		t2[i] = entry2(a, b, c, t, d);
	}
	sort(t1, t1+N);
	for(int i=0; i<M; i++) {
		entry2 p = t2[i];
		entry1 q = entry1(p.a, p.b, p.t, 0);
		int lo = 0;
		if (!(t1[lo] < q)) continue;
		int hi = N;
		int mid;
		while(hi > lo+1) {
			mid = (hi+lo)/2;
			if (t1[mid] < q) lo = mid;
			else hi = mid;
		}
		if (t1[lo].a == q.a && t1[lo].b == q.b){
			q = t1[lo];
			while(lo >= 0 && t1[lo] == q){
				ans.push_back(entry3(p.a, p.b, t1[lo].t, t1[lo].c, p.c, p.t, p.d));
				lo--;
			}
		}
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for(int i=0; i<(int)ans.size(); i++) {
		printf("%d %d %d %d %d %d %d\n", ans[i].a, ans[i].b, ans[i].t1, ans[i].c1, ans[i].c2, ans[i].t2, ans[i].d2);
	}
	return 0;
}