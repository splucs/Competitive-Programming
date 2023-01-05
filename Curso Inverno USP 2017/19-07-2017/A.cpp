#include <bits/stdc++.h>
using namespace std;

int main() {
	int a[3], b[3];
	scanf("%d %d %d", &a[0], &a[1], &a[2]);
	scanf("%d %d %d", &b[0], &b[1], &b[2]);
	int pa=0, pb=0;
	for(int i=0; i<3; i++) {
		if (a[i] > b[i]) pa++;
		if (a[i] < b[i]) pb++;
	}
	printf("%d %d\n", pa, pb);
	return 0;
}