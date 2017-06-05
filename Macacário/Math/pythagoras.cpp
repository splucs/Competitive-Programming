#include <cstdio>
#include <cmath>
#include <set>
#include <iostream>
using namespace std;

typedef pair<int, int> ii;

inline void addSides(set<ii> & ans, int k, int s){
	for(int n=1, m, ms, a, b; n*n<=s/2; n++){
		ms = s - n*n;
		m = floor(sqrt(ms));
		if (m*m == ms && m!=n){
			a = m*m - n*n;
			b = 2*m*n;
			ans.insert(ii(k*a, k*b));
			ans.insert(ii(k*b, k*a));
		}
	}
}

set<ii> tripleFromHypot(int c){
	set<ii> ans;
	for(int k = 1, s; k*k <= c; k++){
		if (c%k != 0) continue;
		s = c/k;
		addSides(ans, s, k);
		addSides(ans, k, s);
	}
	return ans;
}

set<ii> primitiveTripleFromHypot(int c){
	set<ii> ans;
	addSides(ans, 1, c);
	return ans;
}

set<ii> tripleFromSide(int a){
	set<ii> ans;
	for(int n = 1, m, b, c; n < a; n++){
		if (a%n != 0) continue;
		m = a*a/n;
		if (m%2 != n%2) continue;
		b = (m-n)/2;
		c = (m+n)/2;
		ans.insert(ii(b, c));
	}
	return ans;
}

int main(){
	int a, b, c;
	while(scanf("%d", &a), a>0){
		set<ii> sides = tripleFromSide(a);
		set<ii>::iterator it;
		for(it = sides.begin(); it!=sides.end(); it++){
			b = it->first;
			c = it->second;
			printf("%d^2 + %d^2 = %d^2\n", a, b, c);
			if (a*a + b*b != c*c) printf("error\n");
		}
	}
	return 0;
}