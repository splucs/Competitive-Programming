#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T, N;
	double D, K, S, t, mt, ans;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++){
		scanf("%lf %d", &D, &N);
		mt = 0.0;
		while(N--){
			scanf("%lf %lf", &K, &S);
			t = (D-K)/S;
			mt = max(mt, t);
		}
		ans = D/mt;
		printf("Case #%d: %.6f\n", caseNo, ans);
	}
	return 0;
}