#include <vector>
using namespace std;
#define MOD 1000000007LL
#define MAXV 1009

typedef long long ll;
vector<ll> buf[MAXV];
int nBuf = 0;

void karatsuba(vector<ll>& x, vector<ll>& y, vector<ll>& res) {
	int n = 1;
	while(n < x.size() || n < y.size()) n <<= 1; 
	x.resize(n); y.resize(n);
	res.assign(2*n, 0);
	
	if (n == 1) {
		res[0] = ((x[0]%MOD)*(y[0]%MOD))%MOD;
		return;
	}
	int k = n / 2;
	
	vector<ll>& Xr = buf[nBuf++]; Xr.clear();
	Xr.insert(Xr.begin(), x.begin(), x.begin() + k);
	
	vector<ll>& Xl = buf[nBuf++]; Xl.clear();
	Xl.insert(Xl.begin(), x.begin() + k, x.end());
	
	vector<ll>& Yr = buf[nBuf++]; Yr.clear();
	Yr.insert(Yr.begin(), y.begin(), y.begin() + k);
	
	vector<ll>& Yl = buf[nBuf++]; Yl.clear();
	Yl.insert(Yl.begin(), y.begin() + k, y.end());
	/*
	vector<long long> Xr (x.begin(), x.begin() + k);
    vector<long long> Xl (x.begin() + k, x.end());
    vector<long long> Yr (y.begin(), y.begin() + k);
    vector<long long> Yl (y.begin() + k, y.end());*/
	
	vector<ll>& P1 = buf[nBuf++]; karatsuba(Xl, Yl, P1);
	vector<ll>& P2 = buf[nBuf++]; karatsuba(Xr, Yr, P2);
	vector<ll>& Xlr = buf[nBuf++]; Xlr.resize(k);
	vector<ll>& Ylr = buf[nBuf++]; Ylr.resize(k);
	
	for (int i = 0; i < k; i++) {
		Xlr[i] = (Xl[i] + Xr[i]) % MOD;
		Ylr[i] = (Yl[i] + Yr[i]) % MOD;
	}
	
	vector<ll>& P3 = buf[nBuf++]; karatsuba(Xlr, Ylr, P3);
	for (int i = 0; i < n; i++) {
		P3[i] = (P3[i] - (P2[i] + P1[i])%MOD + MOD) % MOD;
		res[i] = P2[i];
	}
	for (int i = n; i < 2 * n; i++) res[i] = P1[i - n];
	for (int i = k; i < n + k; i++) res[i] = (res[i] + P3[i - k]) % MOD;
	nBuf -= 9;
}

/*
 * TEST MATRIX
 */

#include <cstdio>
#include <ctime>
#include <cstdlib>

void naive(vector<ll>& x, vector<ll>& y, vector<ll>& res) {
	res.assign(x.size()+y.size(), 0);
	int n = res.size();
	for(int k=0; k<n; k++) {
		for(int i=max(0, k-(int)y.size()+1), j; i<min((int)x.size(), k+1); i++) {
			j = k-i;
			res[k] = (res[k] + x[i]*y[j])%MOD;
		}
	}
}

#define DEBUG false

bool test(int nTests) {
	int N = 10000;
	vector<ll> a(N), b(N), res1, res2;
	srand(time(NULL));
	double t1 = 0, t2 = 0;
	for(int t=1; t<=nTests; t++) {
		for(int i=0; i<N; i++) {
			a[i] = rand()%MOD;
			b[i] = rand()%MOD;
		}
		printf("test %d\n", t);
		clock_t m1, m2;
		
		//naive
		m1 = clock();
		naive(a, b, res1);
		m2 = clock();
		t1 += (m2-m1)*1.0/CLOCKS_PER_SEC;
		
		//karatsuba
		m1 = clock();
		karatsuba(a, b, res2);
		m2 = clock();
		t2 += (m2-m1)*1.0/CLOCKS_PER_SEC;
		
		if(DEBUG) {
			printf("a:");
			for(int i=0; i<N; i++) printf(" %lld", a[i]);
			printf("\n");
			printf("b:");
			for(int i=0; i<N; i++) printf(" %lld", b[i]);
			printf("\n");
			printf("res1:");
			for(int i=0; i<(int)res1.size(); i++) printf(" %lld", res1[i]);
			printf("\n");
			printf("res2:");
			for(int i=0; i<(int)res2.size(); i++) printf(" %lld", res2[i]);
			printf("\n");
		}
		
		//test
		for(int i=0; i<(int)min(res1.size(), res2.size()); i++) {
			if (res1[i] != res2[i]) {
				printf("Failed test %d\n", t);
				return false;
			}
		}
		for(int i=min(res1.size(), res2.size()); i<(int)res1.size(); i++) {
			if (res1[i] != 0) {
				printf("Failed test %d\n", t);
				return false;
			}
		}
		for(int i=min(res1.size(), res2.size()); i<(int)res2.size(); i++) {
			if (res2[i] != 0) {
				printf("Failed test %d\n", t);
				return false;
			}
		}
	}
	t1 /= nTests;
	t2 /= nTests;
	printf("all tests passed, naive time %.6f, karatsuba time %.6f\n", t1, t2);
	return true;
}

int main() {
	if(!test(1)) return 0;
	int n, m;
	while(true) {
		scanf("%d", &n);
		if (n <= 0) return 0;
		vector<ll> a(n);
		for(int i=0; i<n; i++) scanf("%lld", &a[i]);
		
		scanf("%d", &m);
		if (m <= 0) return 0;
		vector<ll> b(m);
		for(int i=0; i<m; i++) scanf("%lld", &b[i]);
		
		vector<ll> res;
		karatsuba(a, b, res);
		for(int i=0; i<(int)res.size(); i++) printf("%lld ", res[i]);
		printf("\n");
	}
	return 0;
}