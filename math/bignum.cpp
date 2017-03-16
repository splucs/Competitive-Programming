#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef vector<int> bignum;
const int base = 1000 * 1000 * 1000;

void print(bignum & a) {
	printf("%d", a.empty() ? 0 : a.back());
	for (int i = (int)a.size() - 2; i >= 0; --i)
		printf("%01d", a[i]);
}
void fix(bignum & a) {
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
}
bool operator < (bignum a, bignum b) {
	fix(a); fix(b);
	if (a.size() != b.size()) return a.size() < b.size();
	for (int i = (int)a.size() - 1; i >= 0; i--) {
		if (a[i] != b[i]) return a[i] < b[i];
	}
	return false;
}
bignum str2bignum(char* s) {
	bignum a;
	for (int i = (int)strlen(s); i>0; i -= 9) {
		s[i] = 0;
		a.push_back(atoi(i >= 9 ? s + i - 9 : s));
	}
	fix(a);
	return a;
}
bignum int2bignum(int n) {
	bignum a;
	if (n == 0) a.push_back(0);
	while (n > 0) {
		a.push_back(n%base);
		n /= base;
	}
	return a;
}
int bignum2int(bignum & a) {
	int ans = 0, p = 1;
	for (int i = 0; i<(int)a.size(); i++) {
		ans += a[i] * p;
		p *= base;
	}
	return ans;
}
bignum operator +(bignum a, bignum b) {
	int carry = 0;
	for (size_t i = 0; i<max(a.size(), b.size()) || carry; ++i) {
		if (i == a.size())
			a.push_back(0);
		a[i] += carry + (i < b.size() ? b[i] : 0);
		carry = a[i] >= base;
		if (carry)  a[i] -= base;
	}
	fix(a);
	return a;
}
bignum operator -(bignum a, bignum & b) {
	int carry = 0;
	for (size_t i = 0; i<b.size() || carry; ++i) {
		a[i] -= carry + (i < b.size() ? b[i] : 0);
		carry = a[i] < 0;
		if (carry)  a[i] += base;
	}
	fix(a);
	return a;
}
bignum operator *(int b, bignum a) {
	int carry = 0;
	for (size_t i = 0; i<a.size() || carry; ++i) {
		if (i == a.size())
			a.push_back(0);
		long long cur = carry + a[i] * 1ll * b;
		a[i] = int(cur % base);
		carry = int(cur / base);
	}
	fix(a);
	return a;
}
bignum operator *(const bignum & a, const bignum & b) {
	bignum c(a.size() + b.size());
	for (size_t i = 0; i<a.size(); ++i)
		for (int j = 0, carry = 0; j<(int)b.size() || carry; ++j) {
			long long cur = c[i + j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
			c[i + j] = int(cur % base);
			carry = int(cur / base);
		}
	fix(c);
	return c;
}
bignum operator /(bignum a, int b) {
	int carry = 0;
	for (int i = (int)a.size() - 1; i >= 0; --i) {
		long long cur = a[i] + carry * 1ll * base;
		a[i] = int(cur / b);
		carry = int(cur % b);
	}
	fix(a);
	return a;
}
bignum operator <<(bignum a, int b) {
	a.resize((int)a.size() + b);
	for (int i = (int)a.size() - 1; i >= 0; i--) {
		if (i >= b) a[i] = a[i - b];
		else a[i] = 0;
	}
	return a;
}
bignum operator >>(bignum a, int b) {
	for (int i = 0; i + b<(int)a.size(); i++) {
		a[i] = a[i + b];
	}
	while (b-->0) a.pop_back();
	return a;
}
bignum operator /(bignum a, bignum b) {
	bignum c, d;
	c = int2bignum(1);
	d = int2bignum(0);
	while (b < a) {
		c = (c << 1); b = (b << 1);
	}
	while (true) {
		while (a < b && int2bignum(0) < c) {
			c = (c >> 1); b = (b >> 1);
		}
		if (!(int2bignum(0) < c)) break;
		a = (a - b); d = (d + c);
	}
	return d;
}
bignum operator %(bignum a, bignum b) {
	bignum c = a / b;
	c = b*c;
	return a - c;
}