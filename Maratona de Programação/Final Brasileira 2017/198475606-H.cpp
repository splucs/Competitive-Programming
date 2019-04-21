#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, b, c;
	int n1, n2, n3;
	scanf("%d %d %d %d %d %d", &a, &b, &c, &n1, &n2, &n3);
	int sum = 0;
	sum += max(0, n1-a);
	sum += max(0, n2-b);
	sum += max(0, n3-c);
	printf("%d\n", sum);
}
