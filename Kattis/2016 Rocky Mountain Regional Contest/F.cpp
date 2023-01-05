#include <bits/stdc++.h>
using namespace std;
#define MAXN 209

char str[MAXN];
int cnt[3];

bool ispow2(int j) {
	return j == (j & -j);
}

int main() {
	int T;
	scanf("%d", &T);
	while(T-->0) {
		scanf(" %s", str);
		cnt[0] = cnt[1] = cnt[2] = 0;
		int len = strlen(str);
		for(int i=0; i<len; i++) {
			int j;
			if (str[i] == '8') j = 2;
			if (str[i] == '4') j = 1;
			if (str[i] == '2') j = 0;
			for(int k=0; k<j; k++) {
				if (cnt[k] % 2 != 0) {
					cnt[k]++;
					if (k == 2) printf("8");
					if (k == 1) printf("4");
					if (k == 0) printf("2");
				}
				cnt[k+1] += cnt[k] / 2;
				cnt[k] = 0;
			}
			printf("%c", str[i]);
			cnt[j]++;
		}
		for(int k=0; k<2; k++) {
			int ks = 0;
			for(int kl=k+1; kl<3; kl++) ks += cnt[kl];
			if (cnt[k] == 1 && ks == 0) {
				break;
			}
			if (cnt[k] % 2 != 0) {
				cnt[k]++;
				if (k == 2) printf("8");
				if (k == 1) printf("4");
				if (k == 0) printf("2");
			}
			cnt[k+1] += cnt[k] / 2;
			cnt[k] = 0;
		}
		while(!ispow2(cnt[2])) {
			cnt[2]++;
			printf("8");
		}
		printf("\n");
	}
	return 0;
}