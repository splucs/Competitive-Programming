#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define MAXM 200009
#define INF 1e+15
#define EPS 1e-9
#define PREC 1e-4

typedef long long ll;

class FenwickTree {
private:
	vector<ll> ft1, ft2;
	ll rsq(vector<ll> & ft, int i) {
		ll sum = 0;
		while(i > 0){
			sum += ft[i];
			i -= (i & -i);
		}
		return sum;
	}
	void update(vector<ll> & ft, int i, ll v) {
		while(i < (int)ft.size()) {
			ft[i] += v;
			i += (i & -i);
		}
	}
public:
	FenwickTree(int n) {
		ft1.assign(n + 1, 0);	//1-indexed
		ft2.assign(n + 1, 0);	//1-indexed
	}
	void update(int i, int j, ll v){
		update(ft1, i, v);
		update(ft1, j+1, -v);
		update(ft2, i, v*(i-1));
		update(ft2, j+1, -v*j);
	}
	ll rsq(int i){
		return rsq(ft1, i)*i - rsq(ft2, i);
	}
	ll rsq(int i, int j){
		return rsq(j) - rsq(i-1);
	}
};

int n, m, x[MAXM], p[MAXM];
int last[MAXN], l[MAXM], r[MAXM], id2x[MAXM];
FenwickTree a(0), b(0), c(0);

int main() {
	freopen("gadgets.in", "r", stdin);
	freopen("gadgets.out", "w", stdout);
	
	scanf("%d %d", &n, &m);
	for(int i=1; i<=m; i++) {
		scanf("%d %d", &x[i], &p[i]);
		x[i] *= 2;
	}
	memset(&last, -1, sizeof last);
	set<int> sx;
	sx.insert(-MAXM);
	sx.insert(MAXM);
	for(int i=1, xm; i<=m; i++){
		if (last[p[i]] < 0) l[i] = -MAXM;
		else {
			xm = (x[last[p[i]]] + x[i])/2;
			l[i] = xm;
			r[last[p[i]]] = xm;
			sx.insert(xm);
		}
		last[p[i]] = i;
	}
	for(int j=1; j<=n; j++) {
		if (last[j] >= 0) r[last[j]] = MAXM;
	}
	int nid = 0;
	map<int, int> x2id;
	while(!sx.empty()) {
		x2id[*sx.begin()] = ++nid;
		id2x[nid] = *sx.begin();
		sx.erase(sx.begin());
	}
	a = FenwickTree(nid);
	b = FenwickTree(nid);
	c = FenwickTree(nid);
	for(int i=1; i<=m; i++) {
		a.update(x2id[l[i]], x2id[r[i]]-1, 1);
		b.update(x2id[l[i]], x2id[r[i]]-1, -x[i]);
		c.update(x2id[l[i]], x2id[r[i]]-1, (x[i]/2ll)*(x[i]/2ll));
	}
	double miny = INF;
	vector<double> ans;
	for(int i=1; i<nid; i++){
		double ci = id2x[i]/2.0;
		double cj = id2x[i+1]/2.0;
		double ca = a.rsq(i, i);
		double cb = b.rsq(i, i);
		double cc = c.rsq(i, i);
		double mx = -cb*0.5/ca;
		if (cj <= mx) mx = cj;
		if (ci >= mx) mx = ci;
		double y = ca*mx*mx + cb*mx + cc;
		if (fabs(y-miny) > PREC && miny > y){
			ans.clear();
			miny = y;
		}
		if (fabs(y-miny) < PREC) {
			if (ans.empty() || fabs(ans.back()-mx) > EPS){
				ans.push_back(mx);
			}
		}
	}
	
	printf("%u\n", ans.size());
	for(int i=0; i<(int)ans.size(); i++) {
		printf("%.11f\n", ans[i]);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}