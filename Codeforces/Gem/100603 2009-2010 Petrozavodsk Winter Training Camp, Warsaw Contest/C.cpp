#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define INF 1000000009
typedef pair<int, int> ii;
typedef long long int ll;

int pesos[1000005], orig[1000005], dest[1000005], t_orig[1000005];
int translate[1000005], rev[1000005];
bool visited[1000005];

vector<int> computed;
void compute(int pos, int st) {
	visited[pos] = true;

	computed.push_back(pesos[rev[pos]]);
	if (pos == st) return;
	compute(t_orig[pos], st);
}

int main() {
	int n;
	scanf("%d", &n);
	ll ans = 0, m = 0, global_min = 1000000, tmp;

	for (int i = 1; i <= n; i++) {
		scanf("%d", &pesos[i]);
		global_min = min((ll) pesos[i], global_min);
	}

	for (int i = 1; i <= n; i++) {
		scanf("%d", &orig[i]);
	}

	for (int i = 1; i <= n; i++) {
		scanf("%d", &dest[i]);
		translate[dest[i]] = i;
	}

	for (int i = 1; i <= n; i++) {
		t_orig[i] = translate[orig[i]];
		rev[i] = orig[i];
	}

	for (int i = 1; i <= n; i++) {
		if(visited[i]) continue;

		computed.clear();
		compute(t_orig[i], i);
		if (computed.size() == 1) continue;

		m = computed[0];
		
		for (int k = 0; k < computed.size(); k++) {
			ans += computed[k];
			m = min(m, (long long) computed[k]);
		}
		ans += min(m*(computed.size() - 2), global_min*(computed.size()+1) + m);
	}

	printf("%I64d\n", ans);
}