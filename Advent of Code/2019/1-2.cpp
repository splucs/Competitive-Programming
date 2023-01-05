#include <cstdio>
using namespace std;
typedef long long ll;

int main() {
	ll ans = 0, cur;
	while(scanf(" %lld", &cur) != EOF) {
		do {
			cur = cur/3 - 2;
			if (cur <= 0) cur = 0;
			ans += cur;
		} while (cur > 0);
	}
	printf("%lld\n", ans);
}
