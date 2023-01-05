#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef vector<int> bignum;
const int base = 1000*1000*1000;

//Impressão
void print(bignum & a){
	printf ("%d", a.empty() ? 0 : a.back());
	for (int i=(int)a.size()-2; i>=0; --i)
		printf ("%09d", a[i]);
}

//Remover Leading zeros
void fix(bignum & a){
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
}

//Leitura
bignum str2bignum(char* s){
	bignum a;
	for (int i=(int)strlen(s); i>0; i-=9) {
		s[i] = 0;
		a.push_back (atoi (i>=9 ? s+i-9 : s));
	}
	fix(a);
	return a;
}

//Soma a+b
bignum operator +(bignum a, bignum b){
	int carry = 0;
	for (size_t i=0; i<max(a.size(),b.size()) || carry; ++i) {
		if (i == a.size())
			a.push_back (0);
		a[i] += carry + (i < b.size() ? b[i] : 0);
		carry = a[i] >= base;
		if (carry)  a[i] -= base;
	}
	fix(a);
	return a;
}

//Subtrai a-b>0
bignum operator -(bignum a, bignum & b){
int carry = 0;
	for (size_t i=0; i<b.size() || carry; ++i) {
		a[i] -= carry + (i < b.size() ? b[i] : 0);
		carry = a[i] < 0;
		if (carry)  a[i] += base;
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
	fix(a);
	return a;
}

//Multiplica bignum a por int b<base
bignum operator *(int b, bignum a){
	int carry = 0;
	for (size_t i=0; i<a.size() || carry; ++i) {
		if (i == a.size())
			a.push_back (0);
		long long cur = carry + a[i] * 1ll * b;
		a[i] = int (cur % base);
		carry = int (cur / base);
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
	fix(a);
	return a;
}

//Construtor a partir de um inteiro
bignum fromInt(int n){
	bignum a;
	a.push_back(1);
	return n*a;
}

//Multiplica a*b
bignum operator *(const bignum & a, const bignum & b){
	bignum c (a.size()+b.size());
	for (size_t i=0; i<a.size(); ++i)
		for (int j=0, carry=0; j<(int)b.size() || carry; ++j) {
			long long cur = c[i+j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
			c[i+j] = int (cur % base);
			carry = int (cur / base);
		}
	while (c.size() > 1 && c.back() == 0)
		c.pop_back();
	fix(c);
	return c;
}

//Divide bignum a por int b<base
bignum operator /(bignum a, int b){
	int carry = 0;
	for (int i=(int)a.size()-1; i>=0; --i) {
		long long cur = a[i] + carry * 1ll * base;
		a[i] = int (cur / b);
		carry = int (cur % b);
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
	fix(a);
	return a;
}

typedef vector< vector< bignum > > matrix;

matrix operator *(matrix a, matrix b){
	int n = (int)a.size();
	if (a[0].size() != b.size()) printf("fail\n");
	int m = (int)b.size();
	int p = (int)b[0].size();
	matrix c;
	c.resize(n);
	for(int i=0; i<n; i++){
		c[i].assign(p, fromInt(0));
		for(int j=0; j<p; j++){
			for(int k=0; k<m; k++){
				c[i][j] = c[i][j] + (a[i][k]*b[k][j]);
			}
		}
	}
	return c;
}

matrix id(int n){
	matrix c; c.resize(n);
	for(int i=0; i<n; i++){
		c[i].assign(n, fromInt(0));
		c[i][i] = fromInt(1);
	}
	return c;
}

matrix matrixExp(matrix a, int n){
	if (n == 0) return id(a.size());
	matrix c = matrixExp(a, n/2);
	c = c*c;
	if (n%2 != 0) c = c*a;
	return c;
}

matrix fibo(){
	matrix c; c.resize(2);
	c[0].assign(2, fromInt(1));
	c[1].assign(2, fromInt(1));
	c[1][1] = fromInt(0);
	return c;
}

bignum fibo(int n){
	matrix f = matrixExp(fibo(), n);
	return f[0][1];
}

int main(){
	int X, Mf;
	bignum ans;
	while(scanf("%d %d", &X, &Mf), (X || Mf)){
		ans = X*fibo(Mf+2);
		print(ans);
		printf("\n");
	}
	return 0;
}