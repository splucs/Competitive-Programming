#include <bits/stdc++.h>
using namespace std;
#define MAXN 409
#define INF (1ll<<60)

typedef long long ll;

char op[MAXN];
ll vet[MAXN], mi[MAXN][MAXN], ma[MAXN][MAXN];

ll MA(const int i, const int j);

ll MI(const int i, const int j){
	if (mi[i][j] < INF) return mi[i][j];
	if (i == j) return mi[i][j] = vet[i];
	for(int k=i; k<j; k++){
		if(op[k] == '-' || op[k] == '?'){
			mi[i][j] = min(mi[i][j], MI(i, k)-MA(k+1,j));
		}
		if(op[k] == '+' || op[k] == '?'){
			mi[i][j] = min(mi[i][j], MI(i, k)+MI(k+1,j));
		}
		if(op[k] == '*' || op[k] == '?'){
			mi[i][j] = min(mi[i][j], MI(i, k)*MI(k+1,j));
			mi[i][j] = min(mi[i][j], MI(i, k)*MA(k+1,j));
			mi[i][j] = min(mi[i][j], MA(i, k)*MI(k+1,j));
			mi[i][j] = min(mi[i][j], MA(i, k)*MA(k+1,j));
		}
	}
	return mi[i][j];
}

ll MA(const int i, const int j){
	if (ma[i][j] > -INF) return ma[i][j];
	if (i == j) return ma[i][j] = vet[i];
	for(int k=i; k<j; k++){
		if(op[k] == '-' || op[k] == '?'){
			ma[i][j] = max(ma[i][j], MA(i, k)-MI(k+1,j));
		}
		if(op[k] == '+' || op[k] == '?'){
			ma[i][j] = max(ma[i][j], MA(i, k)+MA(k+1,j));
		}
		if(op[k] == '*' || op[k] == '?'){
			ma[i][j] = max(ma[i][j], MI(i, k)*MI(k+1,j));
			ma[i][j] = max(ma[i][j], MI(i, k)*MA(k+1,j));
			ma[i][j] = max(ma[i][j], MA(i, k)*MI(k+1,j));
			ma[i][j] = max(ma[i][j], MA(i, k)*MA(k+1,j));
		}
	}
	return ma[i][j];
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf(" %I64d %c", &vet[i], &op[i]);
		vet[i+n] = vet[i];
		op[i+n] = op[i];
	}
	for(int i=0; i<MAXN; i++){
		for(int j=0; j<MAXN; j++){
			mi[i][j] = INF;
			ma[i][j] = -INF;
		}
	}
	for(int i=0; i<n; i++){
		printf("%I64d%I64d", abs(MI(i, i+n-1)), abs(MA(i, i+n-1)));
	}
	printf("\n");
	return 0;
}