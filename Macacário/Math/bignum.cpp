#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef vector<int> bignum;
const int base = 1000*1000*1000;

//Impressão
void print(bignum & a){
	printf ("%d", a.empty() ? 0 : a.back());
	for (int i=(int)a.size()-2; i>=0; --i)
		printf ("%01d", a[i]);
}

//Remover Leading zeros
void fix(bignum & a){
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
}

//Comparador
bool operator < (bignum a, bignum b){
	fix(a); fix(b);
	if (a.size() != b.size()) return a.size() < b.size();
	for(int i=(int)a.size()-1; i>=0; i--){
		if (a[i] != b[i]) return a[i] < b[i];
	}
	return false;
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

//Construtor a partir de um inteiro
bignum int2bignum(int n){
	bignum a;
	if (n == 0) a.push_back(0);
	while(n > 0){
		a.push_back(n%base);
		n /= base;
	}
	return a;
}

int bignum2int(bignum & a){
	int ans = 0, p=1;
	for(int i=0; i<(int)a.size(); i++){
		ans += a[i]*p;
		p *= base;
	}
	return ans;
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
	fix(a);
	return a;
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
	fix(a);
	return a;
}

//Shift left por b (multiplica por base^b)
bignum operator <<(bignum a, int b){
	a.resize((int)a.size() + b);
	for(int i=(int)a.size()-1; i>=0; i--){
		if(i>=b) a[i] = a[i-b];
		else a[i] = 0;
	}
	return a;
}

//Shift right por b (multiplica por base^b)
bignum operator >>(bignum a, int b){
	for(int i=0; i+b<(int)a.size(); i++){
		a[i] = a[i+b];
	}
	while(b-->0) a.pop_back();
	return a;
}

//Divide bignum a por bignum b
bignum operator /(bignum a, bignum b){
	bignum c, d;
	c = int2bignum(1);
	d = int2bignum(0);
	while(b < a){
		c = (c<<1);
		b = (b<<1);
	}
	while(true){
		while (a < b && int2bignum(0) < c){
			c = (c>>1);
			b = (b>>1);
		}
		if (!(int2bignum(0) < c)) break;
		a = (a-b);
		d = (d+c);
	}
	return d;
}

//Resto de bignum a por bignum b
bignum operator %(bignum a, bignum b){
	bignum c = a/b;
	c = b*c;
	return a-c;
}

bool test(){
	bool toprint = false;
	for(int i=1; i<10000; i++){
		int na = 1 + rand()%30000;
		int nb = 1 + rand()%30000;
		if (nb > na){
			int tmp = na;
			na = nb;
			nb = tmp;
		}
		if(toprint) printf("test %d: na = %d, nb = %d, ", i, na, nb);
		bignum a = int2bignum(na);
		bignum b = int2bignum(nb);
		bignum c; int nc;
		c = a+b;
		nc = na + nb;
		if (nc != bignum2int(c)){
			printf("failed test %d, n: %d+%d=%d, b: ", i, na, nb, nc);
			print(a);
			printf("+");
			print(b);
			printf("=");
			print(c);
			printf("\n");
			return false;
		}
		if(toprint) printf("+ ok ");
		c = a-b;
		nc = na - nb;
		if (nc != bignum2int(c)){
			printf("failed test %d, n: %d-%d=%d, b: ", i, na, nb, nc);
			print(a);
			printf("-");
			print(b);
			printf("=");
			print(c);
			printf("\n");
			return false;
		}
		if(toprint) printf("- ok ");
		c = a*b;
		nc = na * nb;
		if (nc != bignum2int(c)){
			printf("failed test %d, n: %d*%d=%d, b: ", i, na, nb, nc);
			print(a);
			printf("*");
			print(b);
			printf("=");
			print(c);
			printf("\n");
			return false;
		}
		if(toprint) printf("* ok ");
		c = a/b;
		nc = na / nb;
		if (nc != bignum2int(c)){
			printf("failed test %d, n: %d/%d=%d, b: ", i, na, nb, nc);
			print(a);
			printf("/");
			print(b);
			printf("=");
			print(c);
			printf("\n");
			return false;
		}
		if(toprint) printf("/ ok\n");
		c = a%b;
		nc = na % nb;
		if (nc != bignum2int(c)){
			printf("failed test %d, n: %d%%%d=%d, b: ", i, na, nb, nc);
			print(a);
			printf("%%");
			print(b);
			printf("=");
			print(c);
			printf("\n");
			return false;
		}
		if(toprint) printf("% ok\n");
	}
	return true;
}

int main(){
	if(test()) printf("all tests passed\n");
	return 0;
}