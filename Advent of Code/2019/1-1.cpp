#include <cstdio>
using namespace std;
typedef long long ll;

int main() {
	ll ans = 0, cur;
	while(scanf(" %lld", &cur) != EOF) {
		ans += cur/3 - 2;
	}
	printf("%lld\n", ans);
}
