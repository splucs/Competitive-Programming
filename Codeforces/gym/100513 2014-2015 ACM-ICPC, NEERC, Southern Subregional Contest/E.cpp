#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

bool merged[MAXN];
int bal[MAXN];

int main()
{
    int N, m, r, vic, Naux;
    scanf("%d", &N);
	vic = 0;
	merged[0] = true;
    for(int i=1; i<=N; i++){
        scanf("%d %d", &m, &r);
		merged[i] = false;
        bal[i] = m - r;
        if (bal[i] > 0) vic++;
    }
	Naux = N;
	for(int i=2; i<=N; i++) {
		if (!merged[i] && !merged[i-1] && (bal[i-1] <= 0 || bal[i] <= 0) && bal[i] + bal[i-1] > 0 && 2*vic <= Naux) {
			merged[i-1] = merged[i] = true;
			Naux--;
		}
		if (!merged[i] && !merged[i-1] && bal[i-1] <= 0 && bal[i] <= 0 && 2*vic <= Naux) {
			merged[i-1] = merged[i] = true;
			Naux--;
		}
	}
    if (2*vic <= Naux) printf("-1\n");
	else {
		printf("%d\n", N - Naux);
		for(int i=1; i<=N; i++) {
			if (merged[i]) {
				printf("%d %d\n", i, i+1);
				i++;
			}
		}
	}
    return 0;
}
