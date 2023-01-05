#include <cstdio>
using namespace std;
typedef long long ll;
#define MAXN 100009

ll arr[MAXN];
int n = 0;

void read() {
	while(true) {
		scanf("%lld", &arr[n]);
		n++;
		if (scanf(",") == EOF) return;
	}
}

void print() {
	for (int i = 0; i < n; i++) {
		printf("%lld,", arr[i]);
	}
	printf("\n");
}

int main() {
	read();
	arr[1] = 12;
	arr[2] = 2;
	for (int i = 0; arr[i] != 99; i += 4) {
		ll op = arr[i];
		if (op == 1) arr[arr[i+3]] = arr[arr[i+1]] + arr[arr[i+2]];
		else if (op == 2) arr[arr[i+3]] = arr[arr[i+1]] * arr[arr[i+2]];
		else {
			printf("fail\n");
			return 0;
		}
	}
	printf("result: %lld\n", arr[0]);
	return 0;
}
