/*
 * Xor Trie
 */
#define MAXS 60000009
int l[MAXS], r[MAXS], cnt = 0;

class XorTrie {
	int digits = 0, root, ans, limit;
	int newnode() {
		l[cnt] = r[cnt] = -1;
		cnt++;
		return cnt-1;
	}
	bool search(int u, int h, int num, int cur) {
		if (u == -1 || cur > limit) return false;
		if (h == -1) {
			ans = cur; return true;
		}
		if (num & (1<<h)) {
			if (search(l[u], h-1, num, cur)) return true;
			if (search(r[u], h-1, num, cur | (1<<h))) return true;
		}
		else {
			if (search(r[u], h-1, num, cur | (1<<h))) return true;
			if (search(l[u], h-1, num, cur)) return true;
		}
		return false;
	}
public:
	XorTrie(int _digits = 20) : digits(_digits) {
		root = newnode();
	}
	void insert(int num) {
		int u = root;
		for(int i = digits-1; i >= 0; i--) {
			if (num & (1<<i)) {
				if (r[u] == -1) r[u] = newnode();
				u = r[u];
			}
			else {
				if (l[u] == -1) l[u] = newnode();
				u = l[u];
			}
		}
	}
	int search(int _limit, int num) {
		limit = _limit; ans = -1;
		if (!search(root, digits-1, num, 0)) return -1;
		return ans;
	}
};

/*
 * Codeforces 979D
 */

#include <cstdio>
#define MAXN 100309
XorTrie tree[MAXN];

int main() {
	int q;
	scanf("%d", &q);
	while (q --> 0) {
		int t, u, x, k, s;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d", &u);
			for(int i = 1; i*i <= u; i++) {
				if (u % i == 0) {
					tree[i].insert(u);
					if (i*i < u) tree[u/i].insert(u);
				}
			}
		}
		else if (t == 2) {
			scanf("%d %d %d", &x, &k, &s);
			int ans = -1;
			ans = tree[k].search(s-x, x);
			if (x % k != 0) ans = -1;
			printf("%d\n", ans);
		}
	}
	return 0;
}