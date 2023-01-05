#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll ip, mask;

bool readIp() {
	int ad[4];
	if(scanf("%d.%d.%d.%d", &ad[3], &ad[2], &ad[1], &ad[0]) == EOF) return false;
	ip = 0;
	ll p = 1;
	for(int i=0; i<4; i++) {
		ip += ad[i]*p;
		p *= (1<<8);
	}
	char c;
	scanf("%c", &c);
	if (c == '/') {
		int x;
		scanf("%d", &x);
		x = 32 - x;
		mask = ((1LL<<32) - 1) - ((1LL << x) - 1);
	}
	else {
		if(scanf("%d.%d.%d.%d", &ad[3], &ad[2], &ad[1], &ad[0]) == EOF) return false;
		mask = 0;
		p = 1;
		for(int i=0; i<4; i++) {
			mask += ad[i]*p;
			p *= (1<<8);
		}
	}
	return true;
}

void printIp(ll i) {
	stack<ll> s;
	while(s.size() < 4u) {
		s.push(i%(1LL<<8));
		i /= (1LL<<8);
	}
	while(!s.empty()) {
		if (s.size() < 4u) printf(".");
		printf("%lld", s.top());
		s.pop();
	}
	printf("\n");
}

int main() {
	while(readIp()) {
		printf("Endereco de rede: ");
		ll ip1 = ip & mask;
		printIp(ip1);
		printf("Endereco de broadcast: ");
		ll ip2 = ip | (((1LL<<32)-1)^mask);
		printIp(ip2);
		printf("Numero de maquinas: ");
		ll num = ip2 - ip1 - 1;
		printf("%lld\n\n", num);
	}
	return 0;
}