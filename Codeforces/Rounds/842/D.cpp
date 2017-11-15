#include <bits/stdc++.h>
using namespace std;
#define MAXN 2000009

int l[MAXN], r[MAXN], h[MAXN], lazy[MAXN], root, sz, size[MAXN];

void push(int p) {
	if (lazy[p] & (1<<h[p])) swap(l[p], r[p]);
	if (l[p] != -1) lazy[l[p]] ^= lazy[p];
	if (r[p] != -1) lazy[r[p]] ^= lazy[p];
	lazy[p] = 0;
}

int newnode(int mh) {
	l[sz] = -1;
	r[sz] = -1;
	h[sz] = mh;
	lazy[sz] = 0;
	size[sz] = 0;
	return sz++;
}

void insert(int p, int num) {
	if (h[p] == -1) {
		size[p] = 1;
		return;
	}
	if (num & (1<<h[p])) {
		if (r[p] == -1) r[p] = newnode(h[p]-1);
		insert(r[p], num);
	}
	else {
		if (l[p] == -1) l[p] = newnode(h[p]-1);
		insert(l[p], num);
	}
	size[p]++;
}

bool search(int p, int & num) {
	if (p == -1) return true;
	push(p);
	if (size[p] == (1<<(h[p]+1))) {
		return false;
	}
	if (search(l[p], num)) return true;
	num = num | (1<<h[p]);
	search(r[p], num);
	return true;
}

int main() {
	sz = 0;
	root = newnode(23);
	int N, Q, x;
	scanf("%d %d", &N, &Q);
	set<int> app;
	for(int i=0; i<N; i++) {
		scanf("%d", &x);
		if (!app.count(x)) {
			insert(root, x);
		}
		app.insert(x);
	}
	int ans;
	while(Q--) {
		scanf("%d", &x);
		lazy[root] ^= x;
		ans = 0;
		search(root, ans);
		printf("%d\n", ans);
	}
	return 0;
}