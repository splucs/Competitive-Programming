#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

int bits[10][7] = {
	{1, 1, 1, 0, 1, 1, 1},
	{0, 0, 1, 0, 0, 1, 0},
	{1, 0, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 0, 1, 1},
	{0, 1, 1, 1, 0, 1, 0},
	{1, 1, 0, 1, 0, 1, 1},
	{1, 1, 0, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1}
};

int hr[MAXN], mn[MAXN], N, rep[10];
int mask[4];

bool check(int h, int m) {
	for(int i=0; i<N; i++) {
		if ((mask[0] & rep[h/10]) != rep[hr[i]/10]) return false;
		if ((mask[1] & rep[h%10]) != rep[hr[i]%10]) return false;
		if ((mask[2] & rep[m/10]) != rep[mn[i]/10]) return false;
		if ((mask[3] & rep[m%10]) != rep[mn[i]%10]) return false;
		m++;
		if (m == 60) m=0, h++;
		if (h == 24) h = 0;
	}
	return true;
}

int main() {
	for(int i=0; i<10; i++) {
		for(int j=0; j<7; j++) {
			rep[i] |= (bits[i][j] << j);
		}
	}
	
	while(scanf("%d", &N) != EOF) {
		memset(&mask, 0, sizeof mask);
		for(int i=0; i<N; i++) {
			scanf("%d:%d", &hr[i], &mn[i]);
			mask[0] |= rep[hr[i]/10];
			mask[1] |= rep[hr[i]%10];
			mask[2] |= rep[mn[i]/10];
			mask[3] |= rep[mn[i]%10];
		}
		bool ok = false;
		for(int h=0; h<24; h++) {
			for(int m=0; m<60; m++) {
				if (check(h, m)) {
					ok = true;
					printf("%02d:%02d ", h, m);
				}
			}
		}
		if (!ok) printf("none");
		printf("\n");
	}
	return 0;
}