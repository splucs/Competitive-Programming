#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

typedef vector<int> bignum;
const int base = 1000*1000*1000;

void print(bignum & a){
	printf ("%d", a.empty() ? 0 : a.back());
	for (int i=(int)a.size()-2; i>=0; --i)
		printf ("%09d", a[i]);
}

void fix(bignum & a){
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
}

void int2bignum(int n, bignum & a){
	a.clear();
	if (n == 0) a.push_back(0);
	while(n > 0){
		a.push_back(n%base);
		n /= base;
	}
}

void add(bignum a, bignum & b, bignum & c){
	int carry = 0;
	for (size_t i=0; i<max(a.size(),b.size()) || carry; ++i) {
		if (i == a.size())
			a.push_back (0);
		a[i] += carry + (i < b.size() ? b[i] : 0);
		carry = a[i] >= base;
		if (carry)  a[i] -= base;
	}
	fix(a);
	swap(a, c);
}

void subtract(bignum a, bignum & b, bignum & c){
	int carry = 0;
	for (size_t i=0; i<b.size() || carry; ++i) {
		a[i] -= carry + (i < b.size() ? b[i] : 0);
		carry = a[i] < 0;
		if (carry)  a[i] += base;
	}
	fix(a);
	if (a.empty()) a.push_back(0);
	swap(a, c);
}

int N, mi[MAXN][MAXN], arr[MAXN];
bignum dp[MAXN][MAXN], A[MAXN][MAXN];
bool inc[MAXN][MAXN];

int main() {
	scanf("%d", &N);
	//N = 8;
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
		//arr[i] = i+1;
		mi[i][N] = 0;
		inc[i][i] = true;
	}
	//random_shuffle(arr, arr+N);
	//for(int i=0; i<N; i++) printf("%d ", arr[i]);
	//printf("\n");
	for(int i=N-1; i>=0; i--) {
		for(int j=N-1; j>i; j--) {
			if (arr[i] < arr[j]) {
				mi[i][j] = 1;
				if (arr[j] < arr[j+1] && arr[i] < arr[i+1]) mi[i][j] += mi[i+1][j+1];
			}
			else mi[i][j] = 0;
			inc[i][j] = (arr[i] < arr[i+1]) && inc[i+1][j];
			//printf("inc[%d][%d]=%d\n", i, j, arr[i+1] - arr[i]);
		}
	}
	for(int i=0; i<N; i++) {
		if (inc[i][N-1]) int2bignum(1, dp[i][N]);
		else int2bignum(0, dp[i][N]);
		A[i][N] = dp[i][N];
	}
	for(int i=N-1; i>=0; i--) {
		for(int j=N-1; j>i; j--) {
			int ma = min(j-i, mi[i][j]);
			if (inc[i][j-1]) subtract(A[j][j+1], A[j][j+ma+1], dp[i][j]);
			else int2bignum(0, dp[i][j]);
			//printf("dp[%d][%d] = ", i, j);
			//print(dp[i][j]);
			//printf("\n");
			add(dp[i][j], A[i][j+1], A[i][j]);
		}
	}
	bignum ans;
	ans.push_back(0);	
	for(int i=0; i<N; i++) {
		add(ans, dp[0][i+1], ans);
	}
	print(ans);
	return 0;
}