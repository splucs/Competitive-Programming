#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

class KMP{
private:
	char P[MAXN], T[MAXN];
	int m, n, b[MAXN];
	vector<int> ans;
	int dp(int i, int j) {
		if (j>=0 && T[i] != P[j]){
			dp(i, b[j]);
			return;
		}
		i++; j++;
		if (j == m) {
			j = b[j];
			return 0;
		}
		if (i < n) 1 + dp(i, j);
	}
public:
	KMP(const char* _P){
		strcpy(P, _P);
		b[0] = -1;
		m = strlen(P);
		for(int i = 0, j = -1; i < m;) {
			while (j >= 0 && P[i] != P[j]) j = b[j];
			i++; j++;
			b[i] = j;
		}
	}
	vector<int> match(const char* _T){
		strcpy(T, _T);
		ans.clear();
		n = strlen(T);
		dp(0, 0);
		return ans;
	}
};

void test(){
	string P = "ababa";
	string T = "abababababababa";
	KMP kmp(P.c_str());
	vector<int> index = kmp.match(T.c_str());
	for(int i=0; i<(int)index.size(); i++){
		printf("%d ", index[i]);
	}
	printf("\n");
}

int main(){
	test();
	return 0;
}