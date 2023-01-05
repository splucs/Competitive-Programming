#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef vector<int> bignum;
const int base = 1000*1000*1000;

//Impressão
void print(bignum & a) {
	printf("%d", a.empty() ? 0 : a.back());
	for (int i=(int)a.size()-2; i>=0; --i) {
		printf("%09d", a[i]);
	}
}

//Remover Leading zeros
void fix(bignum & a) {
	while (a.size() > 1u && a.back() == 0) {
		a.pop_back();
	}
}

//Comparador
bool comp(bignum a, bignum b) {
	fix(a); fix(b);
	if (a.size() != b.size()) return a.size() < b.size();
	for(int i=(int)a.size()-1; i>=0; i--) {
		if (a[i] != b[i]) return a[i] < b[i];
	}
	return false;
}

//Leitura
void str2bignum(char* s, bignum & a) {
	a.clear();
	for (int i=(int)strlen(s); i>0; i-=9) {
		s[i] = 0;
		a.push_back (atoi (i>=9 ? s+i-9 : s));
	}
	fix(a);
}

//Construtor a partir de um inteiro
void int2bignum(int n, bignum & a) {
	a.clear();
	if (n == 0) a.push_back(0);
	while(n > 0) {
		a.push_back(n%base);
		n /= base;
	}
}

int bignum2int(bignum & a) {
	int ans = 0, p=1;
	for(int i=0; i<(int)a.size(); i++) {
		ans += a[i]*p;
		p *= base;
	}
	return ans;
}

//Soma a+b=c
void sum(bignum & a, bignum & b, bignum & c) {
	int carry = 0, n = max(a.size(), b.size());
	c.resize(n);
	for (int i=0, ai, bi; i<n; i++) {
		ai = i < (int)a.size() ? a[i] : 0;
		bi = i < (int)b.size() ? b[i] : 0;
		c[i] = carry + ai + bi;
		carry = c[i] / base;
		c[i] %= base;
	}
	if (carry > 0) c.push_back(carry);
	fix(c);
}

//Subtrai a-b=c>=0
void subtract(bignum & a, bignum & b, bignum & c) {
	int carry = 0, n = max(a.size(), b.size());
	c.resize(n);
	for (int i=0, ai, bi; i<n; i++) {
		ai = i < (int)a.size() ? a[i] : 0;
		bi = i < (int)b.size() ? b[i] : 0;
		c[i] = carry + ai - bi;
		carry = c[i] < 0 ? 1 : 0;
		if (c[i] < 0) c[i] += base;
	}
	fix(c);
}

//Shift left por b (multiplica por base^b)
void shiftL(bignum & a, int b, bignum & c) {
	c.resize((int)a.size() + b);
	for(int i=(int)c.size()-1; i>=0; i--) {
		if(i>=b) c[i] = a[i-b];
		else c[i] = 0;
	}
	fix(c);
}

//Shift right por b (multiplica por base^b)
void shiftR(bignum & a, int b, bignum & c) {
	if (((int)a.size()) <= b) {
		c.clear(); c.push_back(0);
		return;
	}
	c.resize((int)a.size() - b);
	for(int i=0; i<(int)c.size(); i++) {
		c[i] = a[i+b];
	}
	fix(c);
}

//Multiplica bignum b por int a<base
void multiply(int a, bignum & b, bignum & c) {
	int carry = 0, bi;
	c.resize(b.size());
	for (int i=0, bi; i<(int)b.size() || carry; i++) {
		if (i == (int)b.size()) c.push_back(0);
		bi = i < (int)b.size() ? b[i] : 0;
		long long cur = carry + a * 1ll * bi;
		c[i] = int(cur % base);
		carry = int(cur / base);
	}
	fix(c);
}

//Multiplica a*b=c
void multiply(bignum a, bignum b, bignum & c) {
	int n = a.size()+b.size();
	long long carry = 0, acum;
	c.resize(n);
	for (int k=0; k<n || carry; k++) {
		if (k == n) c.push_back(0);
		acum = carry; carry = 0;
		for (int i=0, j=k; i <= k && i<(int)b.size(); i++, j--) {
			if (j >= (int)b.size()) continue;
			acum += a[i] * 1ll * b[j];
			carry += acum / base;
			acum %= base;
		}
		c[k] = acum;
	}
	fix(c);
}

//Divide bignum a por int b<base
void divide(bignum & a, int b, bignum & c) {
	int carry = 0;
	c.resize(a.size());
	for (int i=(int)a.size()-1; i>=0; --i) {
		long long cur = a[i] + carry * 1ll * base;
		c[i] = int (cur / b);
		carry = int (cur % b);
	}
	fix(a);
}

//Divide bignum a por bignum b, quociente q, resto r
void divide(bignum a, bignum b, bignum & q, bignum & r) {
	bignum z, p;
	int2bignum(0, z);
	int2bignum(1, p);
	int2bignum(0, q);
	while(comp(b, a)) {
		shiftL(p, max(1u, a.size()-b.size()), p);
		shiftL(b, max(1u, a.size()-b.size()), b);
	}
	while(true) {
		while (comp(a, b) && comp(z, p)) {
			shiftR(p, 1, p); shiftR(b, 1, b);
		}
		if (!comp(z, p)) break;
		subtract(a, b, a);
		sum(q, p, q);
	}
	swap(a, r);
}

bool test() {
	bool toprint = false;
	for(int i=1; i<10000; i++) {
		int na = 1 + rand()%30000;
		int nb = 1 + rand()%30000;
		if (nb > na) {
			int tmp = na;
			na = nb;
			nb = tmp;
		}
		if(toprint) printf("test %d: na = %d, nb = %d, ", i, na, nb);
		bignum a; int2bignum(na, a);
		bignum b; int2bignum(nb, b);
		bignum c, r; int nc, nr;
		sum(a, b, c);
		nc = na + nb;
		if (nc != bignum2int(c)) {
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
		subtract(a, b, c);
		nc = na - nb;
		if (nc != bignum2int(c)) {
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
		multiply(a, b, c);
		nc = na * nb;
		if (nc != bignum2int(c)) {
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
		divide(a, b, c, r);
		nc = na / nb;
		if (nc != bignum2int(c)) {
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
		swap(c, r);
		nc = na % nb;
		if (nc != bignum2int(c)) {
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

char s1[109], s2[109], op;

int main() {
	if(test()) printf("all tests passed\n");
	while (scanf(" %s %c %s", s1, &op, s2) != EOF) {
		bignum a; str2bignum(s1, a);
		bignum b; str2bignum(s2, b);
		bignum c, d;
		if (op == '+') sum(a, b, c);
		if (op == '-') subtract(a, b, c);
		if (op == '*') multiply(a, b, c);
		if (op == '/') divide(a, b, c, d);
		if (op == '%') divide(a, b, d, c);
		print(c);
		printf("\n");
	}
	return 0;
}
