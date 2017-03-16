#include <cstdio>
#include <vector>
using namespace std;

class FenwickTree {
private:
	vector<int> ft1, ft2;
	int rsq(vector<int> & ft, int i) {
		int sum = 0;
		while (i > 0) {
			sum += ft[i];
			i -= (i & -i);
		}
		return sum;
	}
	void update(vector<int> & ft, int i, int v) {
		while (i < (int)ft.size()) {
			ft[i] += v;
			i += (i & -i);
		}
	}
public:
	FenwickTree(int n) {
		ft1.assign(n + 1, 0);	//1-indexed
		ft2.assign(n + 1, 0);	//1-indexed
	}
	void update(int i, int j, int v) {
		update(ft1, i, v);
		update(ft1, j + 1, -v);
		update(ft2, i, v*(i - 1));
		update(ft2, j + 1, -v*j);
	}
	int rsq(int i) {
		return rsq(ft1, i)*i - rsq(ft2, i);
	}
	int rsq(int i, int j) {
		return rsq(j) - rsq(i - 1);
	}
};