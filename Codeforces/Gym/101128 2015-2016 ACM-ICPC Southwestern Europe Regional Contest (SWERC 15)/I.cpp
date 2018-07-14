#include <algorithm>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
using namespace std;

#define ALFA 26
#define MAXN 1000009
#define MAXS 2000009 //2*MAXN
#define INF 0x3f3f3f3f

/*
 * Suffix Tree by Sergey Kulik
 * Ukkonen's O(n) algorithm
 */

struct node {
	int l, r, pr, link, h, next[ALFA], idx, e;
	void setedge(char c, int nc) {
		if (nc != 0 && next[c] == 0) e++;
		if (nc == 0 && next[c] != 0) e--;
		next[c] = nc;
	}
};

struct state {
	int v, j, h;
	state() {}
	state(int v, int j, int h)
		: v(v), j(j), h(h) {}
};

class SuffixTree {
	state ptr, ptr2;
	vector<node> t;
	queue<int> que;
	long long lenSum;
	int N, sz, endless;
	char ch, s[MAXS];
	inline int rl(int p) { return t[p].r - t[p].l; }
	inline void addLen(int p) {
		lenSum += rl(p);
		endless += (t[p].r == INF);
	}
	inline void remLen(int p) {
		lenSum -= rl(p);
		endless -= (t[p].r == INF);
	}
	state follow(state p, char c) {
		if (p.j > 0){
			if (s[t[p.v].r-p.j] == c)
				return state(p.v, p.j-1, p.h+1);
			else return state(0, 0, 0);
		}
		else {
			int nc = t[p.v].next[c];
			if (!nc) return state(0, 0, 0);
			else return state(nc, rl(nc)-1, p.h+1);
		}
	}
	state go(int k, int l, int r){
		while (l < r){
			k = t[k].next[s[l]];
			int dt = rl(k) - r + l;
			if (dt >= 0) return state(k, dt, t[k].h - dt);
			else l += rl(k);
		}
		return state(k, 0, t[k].h);
	}
	void update(int l, int r, int pr, int cc) {
		t[cc].l = l, t[cc].r = r, t[cc].pr = pr,
		t[cc].h = t[pr].h + r - l;
		t[pr].setedge(s[l], cc);
		if(r == INF) {
			t[cc].idx = INF-t[cc].h,
			t[pr].idx = max(t[cc].idx, t[pr].idx);
		}
	}
	int split(state p) {
		int v = p.v, leng = rl(v) - p.j;
		if (p.j == 0) return v;
		if (leng == 0) return t[v].pr;
		update(t[v].l, t[v].l + leng, t[v].pr, ++sz);
		t[v].pr = sz, t[v].l += leng, t[sz].idx = t[v].idx,
		t[sz].setedge(s[t[v].l], v);
		return sz;
	}
	int getlink(int k) {
		if (t[k].link) return t[k].link;
		state link = go(getlink(t[k].pr), t[k].l + (t[k].pr == 1), t[k].r);
		return t[k].link = split(link);
	}
	char reduce(char c) { return c - 'a'; }
public:
	SuffixTree(int n) {
		t.resize(2*n);
		lenSum = N = endless = 0;
		sz=1; ptr.v=1; t[1].link = 1;
	}
	void extend(char c) {
		c = reduce(c);
		s[N++] = c;
		while(true) {
			state nptr = follow(ptr, c);
			if (nptr.v) { ptr = nptr; break; }
			int mid = split(ptr), leaf=++sz; 
			update(N-1, INF, mid, leaf);
			int new_mid = getlink(mid);
			ptr.v = new_mid, ptr.j = 0, ptr.h = t[new_mid].h;
			que.push(leaf);
			addLen(leaf);
			if(mid == 1) return;
		}
	}
	long long numDiffSubstr() {
		return lenSum-endless*1LL*(INF-N);
	}
	void pop() {
		int td = que.front();
		remLen(td);
		if(td == ptr.v) {
			ptr = go(getlink(t[ptr.v].pr),
				t[ptr.v].l + (t[ptr.v].pr==1), t[ptr.v].r-ptr.j);
			int rr = (rl(ptr.v)-ptr.j);
			t[td].l = que.size() + t[t[td].pr].h;
			t[td].h = t[t[td].pr].h + rl(td);
			t[td].idx = que.size();
			if (ptr.v == td) ptr.j = rl(ptr.v) - rr;
			que.push(td);
			addLen(td);
		}
		else {
			int r = t[td].pr;
			t[r].setedge(s[t[td].l], 0);
			if(r > 1 && t[r].e < 2) {
				int cut = rl(ptr.v) - ptr.j, rr = t[r].pr, ns = 0;
				for(int j = 0; j < ALFA && !ns; j++)
					if(t[r].next[j]) ns = t[r].next[j];
				int nl = rl(r) + rl(ns);
				update(t[ns].idx + t[rr].h,
					t[ns].e ? t[ns].idx + t[rr].h + nl : INF, rr, ns);
				if (ptr.v == r) ptr.v = ns, ptr.j = rl(ns) - cut;
				else if (ptr.v == ns) ptr.j = rl(ns) - cut - rl(r);
			}
		}
		que.pop();
	}
};

/*
 * Codeforces 101128I
 */

#include <cstdio>

int W, Q;
char s[MAXN];
long long ans[MAXN];

int main() {
	while(scanf(" %s %d %d", s, &Q, &W) != EOF) {
		int n = strlen(s);
		SuffixTree st(n);
		memset(&ans, 0, sizeof ans);
		for(int i = 0; i < n; i++) {
			st.extend(s[i]);
			//printf("added character %c\n", s[i]);
			if (i >= W) {
				st.pop();
				//printf("removed character %c\n", s[i-W]);
			}
			if (i - W + 1 >= 0) ans[i - W + 1] = st.numDiffSubstr();
		}
		while(Q --> 0) {
			int i;
			scanf("%d", &i);
			printf("%lld\n", ans[i-1]);
		}
	}
	return 0;
}