#include <cstdio>
#include <vector>
using namespace std;

const int neutral = 0;
int comp(int a, int b) {
	return a+b;
}

class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	int rsq(int i) { // returns RSQ(1, i)
		int sum = neutral;
		while(i > 0) {
			sum = comp(sum, ft[i]);
			i -= (i & -i);
		}
		return sum;
	}
	int rsq(int i, int j) {
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, int v) {
		while(i < (int)ft.size()) {
			ft[i] = comp(v, ft[i]);
			i += (i & -i);
		}
	}
};