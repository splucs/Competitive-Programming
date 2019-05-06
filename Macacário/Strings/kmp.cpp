#include <string>
#include <vector>
#include <cstring>
using namespace std;

/*
 * Knuth-Morris-Pratt's Algorithm
 */

class KMP {
	string P;
	vector<int> b;
public:
	KMP(const char _P[]) : P(_P) {
		int m = P.size();
		b.assign(m + 1, -1);
		for(int i = 0, j = -1; i < m;) {
			while (j >= 0 && P[i] != P[j]) j = b[j];
			b[++i] = ++j;
		}
	}
	vector<int> match(const char T[]) {
		vector<int> ans;
		for (int i = 0, j = 0, n = strlen(T); i < n;) {
			while (j >= 0 && T[i] != P[j]) j = b[j];
			i++; j++;
			if (j == (int)P.size()) {
				ans.push_back(i - j);
				j = b[j];
			}
		}
		return ans;
	}
	int repetend() {
		int n = P.size();
		int ans = n - b[n];
		if (n % ans) ans = n;
		return ans;
	}
};

/*
 * TEST MATRIX
 */

#include <cstdio>

void test() {
	string P = "ababa";
	string T = "abababababababa";
	KMP kmp(P.c_str());
	vector<int> index = kmp.match(T.c_str());
	for(int i=0; i<(int)index.size(); i++) {
		printf("%d ", index[i]);
	}
	printf("\n");
}

int main() {
	test();
	return 0;
}
