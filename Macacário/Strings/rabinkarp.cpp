#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define d 256 //Tamanho do alfabeto
#define MOD 40031

vector<int> rabinkarp(const char* P, const char* T){
	vector<int> ans;
	int n = strlen(T);
	int m = strlen(P);
	int p = 0, t = 0, h = 1;
	for (int i = 0; i < m-1; i++) h = (h*d)%MOD;
	for (int i = 0; i < m; i++){
		p = (d*p + P[i])%MOD;
		t = (d*t + T[i])%MOD;
	}
	for (int i = 0; i <= n-m; i++){
		if (p == t && strncmp(T+i, P, m) == 0){
			ans.push_back(i);
		}
		if (i+m < n){
			t = (d*(t - T[i]*h) + T[i+m])%MOD;
			if (t < 0) t += MOD;
		}
	}
	return ans;
}

void test(){
	string P = "ababa";
	string T = "abababababababa";
	vector<int> index = rabinkarp(P.c_str(), T.c_str());
	for(int i=0; i<(int)index.size(); i++){
		printf("%d ", index[i]);
	}
	printf("\n");
}

int main(){
	test();
	return 0;
}