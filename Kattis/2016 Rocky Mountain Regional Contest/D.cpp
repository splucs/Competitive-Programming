#include <bits/stdc++.h>
using namespace std;

int main() {
	int X, Y, N;
	while(scanf("%d %d %d", &X, &Y, &N) != EOF) {
		for(int i=1; i<=N; i++) {
			if (i % X == 0 && i % Y == 0) printf("FizzBuzz\n");
			else if (i % X == 0) printf("Fizz\n");
			else if (i % Y == 0) printf("Buzz\n");
			else printf("%d\n", i);
		}
	}
	return 0;
}