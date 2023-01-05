#include <vector>
using namespace std;

/*
 * FWHT - Fast Walsh–Hadamard Transform O(nlogn)
 */

//int mat[2][2] = {{1, 1}, {1, -1}}, inv[2][2] = {{1, 1}, {1, -1}}; //xor
int mat[2][2] = {{1, 1}, {1, 0}}, inv[2][2] = {{0, 1}, {1, -1}}; //or
//int mat[2][2] = {{0, 1}, {1, 1}}, inv[2][2] = {{-1, 1}, {1, 0}}; //and

void fwht(vector<double> & a, bool invert) {
	int n = (int)a.size();
	double u, v;
	for (int len = 1; 2 * len <= n; len <<= 1) {
		for (int i = 0; i < n; i += 2 * len) {
			for (int j = 0; j < len; j++) {
				u = a[i + j];
				v = a[i + len + j];
				if (!invert) {
					a[i + j] = mat[0][0]*u + mat[0][1]*v;
					a[i + len + j] = mat[1][0]*u + mat[1][1]*v;
				}
				else {
					a[i + j] = inv[0][0]*u + inv[0][1]*v;
					a[i + len + j] = inv[1][0]*u + inv[1][1]*v;
				}
			}
		}
	}
	//for (int i=0; invert && i<n; ++i) a[i] /= n; //xor
}

void convolution(vector<double> a, vector<double> b, vector<double> & res) {
	int n = 1;
	while(n < max(a.size(), b.size())) n <<= 1;
	a.resize(n), b.resize(n);
	fwht(a, false); fwht(b, false);
	res.resize(n);
	for(int i=0; i<n; ++i) res[i] = a[i]*b[i];
	fwht(res, true);
}

/*
 * TEST MATRIX
 */

void naive(vector<double> a, vector<double> b, vector<double> & res) {
	int n = 1;
	while(n < max(a.size(), b.size())) n <<= 1;
	a.resize(n), b.resize(n);
	res.clear(); res.assign(n, 0);
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			res[i|j] += a[i]*b[j];
		}
	}
}

#define EPS 1e-3
#include <cstdio>
#include <cstdlib>
#include <cmath>
bool test(int nTest) {
	for(int t=1; t<=nTest; t++) {
		vector<double> a(t), b(t), res1(t), res2(t);
		for(int i=0; i<t; i++) {
			a[i] = rand()%10000;
			b[i] = rand()%10000;
		}
		convolution(a, b, res1);
		naive(a, b, res2);
		bool ok = true;
		for(int i=0; i<(int)res1.size(); i++) {
			if (fabs(res1[i]-res2[i]) > EPS) ok = false;
		}
		if (!ok) {
			printf("failed on test %d\n", t);
			printf("a:");
			for(int i=0; i<(int)a.size(); i++) {
				printf(" %.2f", a[i]);
			}
			printf("\n");
			printf("b:");
			for(int i=0; i<(int)b.size(); i++) {
				printf(" %.2f", b[i]);
			}
			printf("\n");
			printf("res1:");
			for(int i=0; i<(int)res1.size(); i++) {
				printf(" %.2f", res1[i]);
			}
			printf("\n");
			printf("res2:");
			for(int i=0; i<(int)res2.size(); i++) {
				printf(" %.2f", res2[i]);
			}
			printf("\n");
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(1000);
}