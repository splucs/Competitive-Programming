#include <bits/stdc++.h>
using namespace std;

int main() {
	int P;
	scanf("%d", &P);
	if (P % 3 == 0) printf("Tiangua\n");
	if (P % 3 == 1) printf("Sobral\n");
	if (P % 3 == 2) printf("Ubajara\n");
	return 0;
}