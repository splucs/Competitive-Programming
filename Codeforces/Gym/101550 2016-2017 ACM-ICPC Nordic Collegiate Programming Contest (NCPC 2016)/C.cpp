#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

int N, val[MAXN];
vector<int> suit[4];

int minsort(vector<int> & arr) {
	int n = arr.size();
	int M[n+1], L=1, l, h, m;
	M[1]=0;
	for(int i=1; i<n; i++){
		if (arr[i]<arr[M[1]]){		//estritamente crescente
		//if (arr[i]<=arr[M[1]]){	//crescente
			M[1]=i; continue;
		}
		l = 1; h = L+1;
		while(h>l+1){
			m = (l+h)/2;
			if (arr[M[m]]<arr[i]) l = m;	//estritamente crescente
			//if (arr[M[m]]<=arr[i]) l = m;	//crescente
			else h = m;
		}
		if (h>L) L=h;
		M[h] = i;
	}
	return n-L;
}

bool comp1(int i, int j) {
	return val[i] > val[j];
}
bool comp2(int i, int j) {
	return val[i] < val[j];
}

bool used[4];
int ans;
void bt(int i, vector<int> & v) {
	
	if (i == 4) {
		ans = min(ans, minsort(v));
		return;
	}
	
	for(int k=0; k<4; k++) {
		if (used[k]) continue;
		used[k] = true;
		int n = v.size();
		
		sort(suit[k].begin(), suit[k].end(), comp1);
		v.insert(v.end(), suit[k].begin(), suit[k].end());
		bt(i+1, v);
		v.resize(n);
		
		sort(suit[k].begin(), suit[k].end(), comp2);
		v.insert(v.end(), suit[k].begin(), suit[k].end());
		bt(i+1, v);
		v.resize(n);
		
		used[k] = false;
	}
}

int main() {
	scanf("%d", &N);
	
	char n, s;
	for(int i=0; i<N; i++) {
		scanf(" %c %c", &n, &s);
		if (n >= '0' && n <= '9') val[i] = n - '0';
		if (n == 'T') val[i] = 10;
		if (n == 'J') val[i] = 11;
		if (n == 'Q') val[i] = 12;
		if (n == 'K') val[i] = 13;
		if (n == 'A') val[i] = 14;
		if (s == 's') suit[0].push_back(i);
		if (s == 'h') suit[1].push_back(i);
		if (s == 'd') suit[2].push_back(i);
		if (s == 'c') suit[3].push_back(i);
	}
	
	vector<int> aux;
	ans = N;
	bt(0, aux);
	
	printf("%d\n", ans);
	
	return 0;
}