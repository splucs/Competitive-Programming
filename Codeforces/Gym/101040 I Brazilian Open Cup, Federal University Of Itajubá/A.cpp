#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

char str[MAXN]; // the input string, up to 100K characters
int n; // the length of input string
int RA[MAXN], tempRA[MAXN]; // rank array and temporary rank array
int SA[MAXN], tempSA[MAXN]; // suffix array and temporary suffix array
int c[MAXN]; // for counting/radix sort

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

typedef long long ll;
ll vet[MAXN];

ll histogram(ll * vet, int n) {
	stack<ll> s;
	ll ans = 0, tp, cur;
	int i = 0;
	while(i < n || !s.empty()) {
		if (i < n && (s.empty() || vet[s.top()] <= vet[i])) s.push(i++);
		else {
			tp = s.top();
			s.pop();
			cur = vet[tp] * ((s.empty() ? i : i - s.top() - 1) + 1);
			if (ans < cur) ans = cur;
		}
	}
	return ans;
}

int main(){
	scanf("%s", str);
	n = strlen(str);
	str[n++] = '$';
	str[n] = '\0';
	constructSA();
	computeLCP();
	for(int i=0; i<n-1; i++){
		vet[i] = LCP[i+1];
	}
	vet[n-1] = 0;
	/*for(int i=0; i<n; i++){
		printf("%2d %I64d %s\n", i, vet[i], &str[SA[i]]);
	}*/
	printf("%I64d\n", max(n-1ll, histogram(vet, n-1)));
	return 0;
}