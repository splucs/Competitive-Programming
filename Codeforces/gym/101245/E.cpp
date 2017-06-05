#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

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
	vector<int> match(const char* T){
		n = strlen(T);
		vector<int> ans;
		ans.assign(n, 0);
		for (int i=0, j=0; i < n;) {
			while (j >= 0 && T[i] != P[j]){
				ans[i-j] = max(ans[i-j], j);
				j = b[j];
			}
			i++; j++;
			ans[i-j] = max(ans[i-j], j);
			if (j == m) {
				j = b[j];
			}
		}
		return ans;
	}
};

char s1[MAXN], s2[MAXN];
int k;
KMP kmp("");
vector<int> vd, vr, vp, ans;

int main() {
	scanf(" %s %s %d", s1, s2, &k);
	int n = strlen(s1);
	int m = strlen(s2);
	kmp = KMP(s2);
	vd = kmp.match(s1);
	for(int i=0; i<n/2; i++) swap(s1[n-i-1], s1[i]);
	for(int i=0; i<m/2; i++) swap(s2[m-i-1], s2[i]);
	kmp = KMP(s2);
	vr = kmp.match(s1);
	for(int i=0; i<n/2; i++) {
		swap(vr[i], vr[n-i-1]);
	}
	vp.assign(n, 0);
	for(int i=m-1; i<n; i++) {
		vp[i-m+1] = max(vr[i], vp[i-m+1]);
	}
	
	/*
	for(int i=0; i<n; i++) printf("%d ", vd[i]);
	printf("\n");
	for(int i=0; i<n; i++) printf("%d ", vp[i]);
	printf("\n");
	/**/
	for(int i=0; i<=n-m; i++) {
		if (vd[i]+vp[i]+k >= m) ans.push_back(i);
	}
	printf("%u\n", ans.size());
	for(int i=0; i<(int)ans.size(); i++) {
		 printf("%d ", ans[i]+1);
	}
	printf("\n");
	return 0;
}