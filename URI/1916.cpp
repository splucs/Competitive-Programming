#include <cstdio>

int abs(int x){
	if (x>0) return x;
	return -x;
}

int main()
{
	int QT, A1, B1, A2, B2, C1, C2, D1, D2, N;
	int e1, s1, e2, s2, saldo;
	scanf("%d", &QT);
	for (int qt = 0; qt<QT; qt++){
		scanf("%d", &N);
		saldo=0;
		for (int i = 0; i < N; ++i)
		{
			scanf("%d:%d %d:%d | %d:%d %d:%d", &A1, &B1, &A2, &B2, &C1, &D1, &C2, &D2);
			e1 = A1*60+B1;
			s1 = A2*60+B2;
			e2 = C1*60+D1;
			s2 = C2*60+D2;
			if (abs(e1 - 480)>5) saldo+=480-e1;
			if (abs(s1 - 720)>5) saldo+=s1-720;
			if (abs(e2 - 840)>5) saldo+=840-e2;
			if (abs(s2 - 1080)>5) saldo+=s2-1080;
		}
		if (saldo<0){
			printf("- ");
			saldo*=-1;
		}
		else printf("+ ");
		printf("%02d:%02d\n", saldo/60, saldo%60);
	}
	return 0;
}