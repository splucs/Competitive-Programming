/*
 * Mo's Algorithm O(n^(3/2))
 */

#include <algorithm>
using namespace std;
#define SQ 500

int curans; // current ans
void add(int v) { /* add value */ }
void rem(int v) { /* remove value */ }

struct query {
	int i, l, r, ans;
};

bool qcomp(query a, query b) {
	return a.l/SQ == b.l/SQ ? a.r < b.r : a.l < b.l;
}
bool icomp(query a, query b) { return a.i < b.i; }

void mo(int v[], query qs[], int Q) {
	int l = 0, r = -1;
	sort(qs, qs + Q, qcomp);
	for (int i = 0; i < Q; i++) {
		query & q = qs[i];
		while (r < q.r) add(v[++r]);
		while (r > q.r) rem(v[r--]);
		while (l < q.l) rem(v[l++]);
		while (l > q.l) add(v[--l]);
		q.ans = curans;
	}
	sort(qs, qs + Q, icomp);
}

/*
 * COMPILATION TEST
 */

int main() {}