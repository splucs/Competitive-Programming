#include <bits/stdc++.h>
using namespace std;

int main() {
	int N;
	scanf("%d", &N);

	for(int i = 1; i < N; i++) printf("9");
	printf("8");
	for(int i = 0; i < N; i++) printf("9");
	printf("\n");

	for(int i = 1; i < N; i++) printf("9");
	for(int i = 0; i < N; i++) printf("9");
	printf("8");
	printf("\n");

	return 0;
}