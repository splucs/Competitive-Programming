#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define MOD 1000000009

string s[4], e[4], w[4];
int ans[4], k;
char p[MAXN];

class KMP{
private:
	char P[MAXN];
	int m, n, b[MAXN];
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
	int match(const char* T){
		n = strlen(T);
		int ans = 0;
		for (int i=0, j=0; i < n;) {
			while (j >= 0 && T[i] != P[j]) j = b[j];
			i++; j++;
			if (j == m) {
				ans++;
				j = b[j];
			}
		}
		return ans;
	}
};

int main() {
	s[0] = e[0] = w[0] = ""; 
	s[1] = e[1] = w[1] = "a";
	s[2] = e[2] = w[2] = "b";
	cin >> p >> k;
	KMP kmp(p);
	int psz = strlen(p);
	ans[0] = ans[1] = ans[2] = 0;
	if (psz == 1) ans[p[0]-'a'+1] = 1;
	bool whole = true;
	for(int i=3; i<=k; i++){
		if (w[(i-1+4)%4].size() >= psz && w[(i-2+4)%4].size() >= psz) whole = false;
		if (whole){
			e[i%4] = s[i%4] = w[i%4] = w[(i-2+4)%4] + w[(i-1+4)%4];
		}
		else{
			e[i%4] = e[(i-1+4)%4];
			s[i%4] = s[(i-2+4)%4];
		}
		ans[i%4] = (ans[(i-2+4)%4] + ans[(i-1+4)%4] +
			kmp.match((e[(i-2+4)%4].substr(max(0, (int)e[(i-2+4)%4].size()-psz+1), psz-1)
			+ s[(i-1+4)%4].substr(0, psz-1)).c_str()))%MOD;
		//printf("ans[%d] = %d\n", i, ans[i%4]);
	}
	printf("%d\n", ans[k%4]);
	return 0;
}