#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;
typedef long long ll;
#define MAXN 100009
#define INF 0x3f3f3f3f3f3f3f3f

int read(ll arr[]) {
	int n = 0;
	while(true) {
		scanf("%lld", &arr[n]);
		n++;
		if (scanf(",") == EOF) return n;
	}
	return 0;
}

void print(ll arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%lld,", arr[i]);
	}
	printf("\n");
}

pair<ll, bool> compute(ll arr[], int n, ll noun, ll verb) {
	arr[1] = noun;
	arr[2] = verb;
	for (int i = 0; true; i += 4) {
		if (i >= n) return make_pair(0LL, false);
		ll op = arr[i];
		if (op == 99) break;
		ll l = arr[i+1], r = arr[i+2], t = arr[i+3];
		if (l < 0 || l >= n) return make_pair(0LL, false);
		if (r < 0 || r >= n) return make_pair(0LL, false);
		if (t < 0 || t >= n) return make_pair(0LL, false);
		if (op == 1) {
			if (arr[l] + arr[r] > INF) return make_pair(0LL, false);
			arr[t] = arr[l] + arr[r];
		}
		else if (op == 2) {
			if (arr[l] > 0 && arr[r] > INF/arr[l]) return make_pair(0LL, false);
			arr[t] = arr[l] * arr[r];
		}
		else return make_pair(0LL, false);
	}
	return make_pair(arr[0], true);
}

ll input[MAXN], arr[MAXN];

int main() {
	int n = read(input);
	for (ll noun = 0; noun < n; noun++) {
		for (ll verb = 0; verb < n; verb++) {
			memcpy(arr, input, n * sizeof(ll));
			auto result = compute(arr, n, noun, verb);
			if (result.second && result.first == 19690720) {
				printf("noun: %lld, verb: %lld, result: %lld\n", noun, verb, result.first);
				return 0;
			}
		}
	}
	printf("No answer\n");
	return 0;
}
