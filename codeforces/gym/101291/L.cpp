#include <bits/stdc++.h>
using namespace std;

int main()
{
	int x[3], y[3];
	for (int i = 0; i < 3; i++) {
		scanf("%d %d", &x[i], &y[i]);
	}
	bool found = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) continue;
			if (x[i] == x[j]) {
				if (y[i] + y[j] == x[3 - i - j] && x[3 - i - j] == x[i] + y[3 - i - j]) found = true;
				if (y[i] + y[j] == y[3 - i - j] && y[3 - i - j] == x[i] + x[3 - i - j]) found = true;
			}
			if (x[i] == y[j]) {
				if (y[i] + x[j] == x[3 - i - j] && x[3 - i - j] == x[i] + y[3 - i - j]) found = true;
				if (y[i] + x[j] == y[3 - i - j] && y[3 - i - j] == x[i] + x[3 - i - j]) found = true;
			}
			if (y[i] == x[j]) {
				if (x[i] + y[j] == x[3 - i - j] && x[3 - i - j] == y[i] + y[3 - i - j]) found = true;
				if (x[i] + y[j] == y[3 - i - j] && y[3 - i - j] == y[i] + x[3 - i - j]) found = true;
			}
			if (y[i] == y[j]) {
				if (x[i] + x[j] == x[3 - i - j] && x[3 - i - j] == y[i] + y[3 - i - j]) found = true;
				if (x[i] + x[j] == y[3 - i - j] && y[3 - i - j] == y[i] + x[3 - i - j]) found = true;
			}
		}
	}
	if (x[0] == x[1] && x[0] == x[2] && y[0] + y[1] + y[2] == x[0]) found = true;
	if (x[0] == x[1] && x[0] == y[2] && y[0] + y[1] + x[2] == x[0]) found = true;
	if (x[0] == y[1] && x[0] == x[2] && y[0] + x[1] + y[2] == x[0]) found = true;
	if (x[0] == y[1] && x[0] == y[2] && y[0] + x[1] + x[2] == x[0]) found = true;
	if (y[0] == x[1] && y[0] == x[2] && x[0] + y[1] + y[2] == y[0]) found = true;
	if (y[0] == x[1] && y[0] == y[2] && x[0] + y[1] + x[2] == y[0]) found = true;
	if (y[0] == y[1] && y[0] == x[2] && x[0] + x[1] + y[2] == y[0]) found = true;
	if (y[0] == y[1] && y[0] == y[2] && x[0] + x[1] + x[2] == y[0]) found = true;
	if (found) printf("YES\n");
	else printf("NO\n");
	return 0;
}