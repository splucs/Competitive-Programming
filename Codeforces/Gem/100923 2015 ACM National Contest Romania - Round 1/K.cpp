#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MOD 10000003

int id[MAXN], f[MAXN], g[MAXN];

int main(){	
	freopen("pocnitoare.in", "r", stdin);
	freopen("pocnitoare.out", "w", stdout);
	
	int N, A, B, S, Q, q, X;
	scanf("%d %d %d %d %d %d", &N, &A, &B, &S, &Q, &q);
	
	id[0] = 0;
	int sn = MOD/MAXN + 1, gi = g[0] = 0, fi = f[0] = 1, cnt = 1;
	for(int i=1; i<=MOD; i++) {
		fi = (i*1ll*fi)%N;
		gi = (1 + i*1ll*gi)%N;
		if (i%sn == 0) {
			f[cnt] = fi;
			g[cnt] = gi;
			id[cnt++] = i;
		}
	}
	
	for(int qi=1; qi<=Q; qi++) {
		int n = q-1;
		int i = cnt-1;
		while(id[i] > n) i--;
		fi = f[i];
		gi = g[i];
		i = id[i];
		while(i < n) {
			i++;
			fi = (i*1ll*fi)%N;
			gi = (1 + i*1ll*gi)%N;
		}
		X = (fi*1ll*S + A*1ll*gi)%N;
		printf("%d\n", X);
		q = (qi*1ll*X + B)%MOD + 1;
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}