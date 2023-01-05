#include <bits/stdc++.h>
#define MAXN 100009
using namespace std;
typedef long long ll;

char color[MAXN];
int freq[MAXN];

void go(ll& nw, ll& nb, ll& tw, ll& tb, int& i, int& ans, int w, int b) {
	if (nw == -1) {
		tw += freq[i];
	} else if (nw > freq[i]) {
		nw -= freq[i];
		tw += freq[i];
	} else if (nw == freq[i]) {
		ans++;
		nw = -1; nb = -1; tw = 0; tb = 0;
		return;
	} else { // freq[i] > nw
		ans++;

		freq[i] -= nw;
		nw = -1; nb = -1; tw = 0; tb = 0;
		i--; return;
	}

	// Compute nb
	if (tw%w != 0) {
		nb = -1; return;
	} else {
		ll need = (tw/w) * b;
		assert(need != tb);

		if (need > tb) {
			nb = need - tb;
		} else {
			nb = -1;
		}
	}
}
int main() {
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int w = 0, b = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %c", &freq[i], &color[i]);
			if (color[i] == 'W') w += freq[i];
			else b += freq[i];
		}
		if (w == 0 || b == 0) {
			printf("%d\n", max(w, b)); continue;
		}
		int g = __gcd(w, b);
		w /= g, b /= g;

		ll nw = -1, nb = -1, tw = 0, tb = 0;

		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (color[i] == 'W') {
				go(nw, nb, tw, tb, i, ans, w, b);
			} else {
				go(nb, nw, tb, tw, i, ans, b, w);		
			}
		}
		printf("%d\n", ans);	
	}
}