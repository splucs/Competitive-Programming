#include <cstdio>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

/*
 * 2D BIT
 */

class FenwickTree {
private:
	vector<int> ft1, ft2;
	int rsq(vector<int> & ft, int i) {
		int sum = 0;
		for(; i; i -= (i & -i)) sum += ft[i];
		return sum;
	}
	void update(vector<int> & ft, int i, int v) {
		for(; i < (int)ft.size(); i += (i & -i))
			ft[i] += v;
	}
public:
	FenwickTree(int n) {
		ft1.assign(n + 1, 0); //1-indexed
		ft2.assign(n + 1, 0); //1-indexed
	}
	void update(int i, int j, int v) {
		update(ft1, i, v);
		update(ft1, j+1, -v);
		update(ft2, i, v*(i-1));
		update(ft2, j+1, -v*j);
	}
	int rsq(int i) {
		return rsq(ft1, i)*i - rsq(ft2, i);
	}
	int rsq(int i, int j) {
		return rsq(j) - rsq(i-1);
	}
};

/*
 * TEST MATRIX
 */

int vet[10009];
int sum(int a, int b) {
	int ans = vet[a];
	for(int i=a+1; i<=b; i++) ans += vet[i];
	return ans;
}

void update(int a, int b, int k) {
	for(int i=a; i<=b; i++) vet[i] += k;
}


int main() {
	int N = 10000, a, b, k;
	srand(time(NULL));
	FenwickTree ft(N);
	for(int i=1; i<=N; i++) {
		vet[i] = rand()%N;
		ft.update(i, i, vet[i]);
	}
	for(int q=0; q<100; q++) {

		printf("test #%d:", q+1);
		a = (rand()%N) + 1;
		b = (rand()%N) + 1;
		if (a>b) swap(a, b);
		k = rand()%100;
		printf(" %d to %d plus %d\n", a, b, k);

		update(a, b, k);
		ft.update(a, b, k);

		a = (rand()%N) + 1;
		b = (rand()%N) + 1;
		if (a>b) swap(a, b);

		if (sum(a, b) != ft.rsq(a, b)) printf("test failed\n");
	}
	return 0;
}