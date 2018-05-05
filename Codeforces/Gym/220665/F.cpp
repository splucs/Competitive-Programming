#include <bits/stdc++.h>
using namespace std;

int main() {
	int x, y;
	scanf("%d %d", &x, &y);
	bool ok = true;

	if (y == 1 && x != 0) ok = false;
	if (y <= 0) ok = false;
	int d = x - (y-1);
	if (d % 2 != 0 || d < 0) ok = false;
	
	if (ok) printf("Yes\n");
	else printf("No\n");
	return 0;
}