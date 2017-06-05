#define MAXN 110009 // second approach: O(n log n)
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <stack>
using namespace std;

char str[MAXN]; // the input string, up to 100K characters
int n, N; // the length of input string
int RA[MAXN], tempRA[MAXN]; // rank array and temporary rank array
int SA[MAXN], tempSA[MAXN]; // suffix array and temporary suffix array
int c[MAXN], belongto[MAXN]; // for counting/radix sort

void countingSort(int k) { // O(n)
	int i, sum, maxi = max(300, n);
	memset(c, 0, sizeof c);
	for (i = 0; i < n; i++)  c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; i++) {
		int t = c[i];
		c[i] = sum;
		sum += t;
	}
	for (i = 0; i < n; i++)  tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
	for (i = 0; i < n; i++)  SA[i] = tempSA[i];
}

void constructSA() { //O(nlogn)
	int i, k, r;
	for (i = 0; i < n; i++) RA[i] = str[i];
	for (i = 0; i < n; i++) SA[i] = i;
	for (k = 1; k < n; k <<= 1) {
		countingSort(k);
		countingSort(0);
		tempRA[SA[0]] = r = 0;
		for (i = 1; i < n; i++)  tempRA[SA[i]] =
			(RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
		for (i = 0; i < n; i++)  RA[i] = tempRA[i];
		if (RA[SA[n-1]] == n-1) break;
	}
}

int Phi[MAXN];
int LCP[MAXN], PLCP[MAXN];
//Longest Common Prefix
//LCP[i] keeps the size of the longest common prefix between SA[i] and SA[i-1]
void computeLCP() { //O(n)
	int i, L;
	Phi[SA[0]] = -1;
	for (i = 1; i < n; i++)  Phi[SA[i]] = SA[i-1];
	for (i = L = 0; i < n; i++) {
		if (Phi[i] == -1) {
			PLCP[i] = 0; continue;
		}
		while (str[i + L] == str[Phi[i] + L]) L++;
		PLCP[i] = L;
		L = max(L-1, 0);
	}
	for (i = 0; i < n; i++) LCP[i] = PLCP[SA[i]];
}

bool check(int len, bool printflag){
	bool used[109], found = false;
	int times;
	for(int i=0, j; i<n; i=(i==j?j+1:j)){
		j = i+1;
		while(LCP[j]>=len) j++;
		j--;
		if(belongto[SA[i]]!=belongto[SA[i]+len-1] || str[SA[i]]=='$') continue;
		memset(&used, false, sizeof used);
		times = 0;
		for(int k=i; k<=j; k++){
			if (!used[belongto[SA[k]]]){
				times++;
				used[belongto[SA[k]]]=true;
			}
		}
		if (times>N/2) found = true;
		if (times>N/2 && printflag){
			for(int k=0; k<len; k++) printf("%c", str[SA[i]+k]);
			printf("\n");
		}
	}
	return found;
}

void LCS(){
	constructSA();
	computeLCP();
	int a=0, b=MAXN-5, mid;
	while(b>a+1){
		mid = (a+b)/2;
		if (check(mid, false)) a = mid;
		else b = mid;
	}
	if (a==0) printf("?\n");
	else check(a, true);
}

int main(){
	char aux[MAXN];
	int naux;
	bool hasprinted = false;
	while(scanf("%d", &N), N){
		if (N==1){
			scanf(" %s", aux);
			if (hasprinted) printf("\n");
			hasprinted=true;
			printf("%s\n", aux);
			continue;
		}
		strcpy(str, "");
		n = 0;
		for(int i=0; i<N; i++){
			scanf(" %s", aux);
			strcat(str, aux);
			strcat(str, "$");
			naux = strlen(aux);
			for(int j=n; j<n+naux; j++){
				belongto[j]=i;
			}
			belongto[n+naux]=i+1;
			n += naux+1;
		}
		if (hasprinted) printf("\n");
		LCS();
		hasprinted=true;
	}
	return 0;
}