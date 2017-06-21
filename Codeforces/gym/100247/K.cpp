#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef long long ll;

const int neutral = 0;
int comp(int a, int b){
	return a+b;
}

class FenwickTree2D {
private:
	vector< vector<int> > ft;
public:
	FenwickTree2D(int n, int m) {
		ft.assign(n + 1, vector<int>(m + 1, 0));	//1-indexed
	}
	int rsq(int i, int j) { // returns RSQ((1,1), (i,j))
		i++; j++;
		int sum = 0, _j = j;
		while(i > 0) {
			j = _j;
			while(j > 0) {
				sum = comp(sum, ft[i][j]);
				j -= (j & -j);
			}
			i -= (i & -i);
		}
		return sum;
	}
	void update(int i, int j, int v) {
		i++; j++;
		int _j = j;
		while(i < (int)ft.size()) {
			j = _j;
			while(j < (int)ft[i].size()) {
				ft[i][j] = comp(v, ft[i][j]);
				j += (j & -j);
			}
			i += (i & -i);
		}
	}
};

FenwickTree2D ft(0, 0);
int a[MAXN], b[MAXN], c[MAXN];
int c1[MAXN], c2[MAXN], c3[MAXN], sn;

int query(int n)
{
	int x = b[n], y = c[n];
	int i = x/sn, j = y/sn;
	int ans = ft.rsq(i-1, j-1);
	for(i = x-(x%sn); i<x; i++){
		j = c2[i];
		if (a[j] < a[n] && c[j] < y) ans++;
	}
	x = x-(x%sn);
	for(i = y-(y%sn); i<y; i++){
		j = c3[i];
		if (a[j] < a[n] && b[j] < x) ans++;
	}
	i = x/sn, j = y/sn;
	ft.update(i, j, 1);
	return ans;
}

bool c1comp(int i, int j){
	return a[i] < a[j];
}

bool c2comp(int i, int j){
	return b[i] < b[j];
}

bool c3comp(int i, int j){
	return c[i] < c[j];
}

int main()
{
	int n;
	scanf("%d", &n);
	sn = sqrt(n);
	ll N = n;
	ft = FenwickTree2D(sn+9, sn+9);
	for(int i=0; i<n; i++){
		scanf("%d %d %d", &a[i], &b[i], &c[i]);
		a[i]--; b[i]--; c[i]--;
		c1[i] = c2[i] = c3[i] = i;
	}
	sort(c1, c1+n, &c1comp);
	sort(c2, c2+n, &c2comp);
	sort(c3, c3+n, &c3comp);
	ll ans = 0;
	for(int i = 0; i<n; i++){
		ans += (ll)query(c1[i]);
	}
	printf("%I64d\n", (N*(N-1))/2 - ans);
	return 0;
}