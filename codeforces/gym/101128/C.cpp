#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

typedef long long ll;
ll vet[MAXN], sum[MAXN];

ll Sum(int i, int j){
	return sum[j-1] - sum[i-1];
}

ll Eq(int i, int m, int j){
	return Sum(m, j) - Sum(i, m);
}

ll solve(const int l, const int r){
	if (r == l+1) return 0;
	if (r == l+2) return Sum(l, r);
	int i = l, j = r, m;
	while(j>i+1){
		m = (i+j)/2;
		if(Eq(l, m, r) < 0) j = m;
		else if (Eq(l, m, r) > 0) i = m;
		else return Sum(l, r) + solve(l, m) + solve(m, r);
	}
	return min(Sum(l, r) + solve(l, j) + solve(j, r), Sum(l, r) + solve(l, i) + solve(i, r));
}

int main()
{
	int T, N;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		for(int i=0; i<N; i++){
			scanf("%I64d", &vet[i]);
			sum[i] = vet[i];
			if (i>0) sum[i] += sum[i-1];
		}
		printf("%I64d\n", solve(0, N));
	}
	return 0;
}