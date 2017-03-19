#include <bits/stdc++.h>
using namespace std;

int dice[10];

int main()
{
	int winpos = 0, tiepos = 0, d;
	for (int i = 0; i < 6; i++) {
		scanf("%d", &dice[i]);
	}
	for (int i = 0; i < 6; i++) {
		scanf("%d", &d);
		for (int j = 0; j < 6; j++) {
			if (dice[j] > d) winpos++;
			if (dice[j] == d) tiepos++;
		}
	}
	double ans = winpos*1.0 / (36.0 - tiepos);
	printf("%.5f\n", ans);
	return 0;
}