#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
#define MAXN 100009

class KMP{
private:
	char P[MAXN];
	int m, n, b[MAXN];
public:
	KMP(const char* _P) {
		strcpy(P, _P);
		b[0] = -1;
		m = strlen(P);
		for(int i = 0, j = -1; i < m;) {
			while (j >= 0 && P[i] != P[j]) j = b[j];
			i++; j++;
			b[i] = j;
		}
	}
	vector<int> match(const char* T) {
		n = strlen(T);
		vector<int> ans;
		for (int i=0, j=0; i < n;) {
			while (j >= 0 && T[i] != P[j]) j = b[j];
			i++; j++;
			if (j == m) {
				ans.push_back(i - j);
				j = b[j];
			}
		}
		return ans;
	}
};

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