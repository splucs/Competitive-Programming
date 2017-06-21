#include <cstdio>
#include <cstring>

int min, max;

void atualizar(int * m, int * tot, int n){
	if (n<=1) return;
	int x, y;
	for(int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			if (m[i]==m[j]) continue;
			x = tot[i]-tot[j];
			y = m[j]-m[i];
			if (x%y==0){
				if (x/y==20){
					min = max = 20;
					return;
				}
				else if (x/y>20){
					if (max==-1 || max > x/y-1) max = x/y-1;
				}
				else if (min<x/y+1) min = x/y+1;
			}
			else{
				if (x/(double)y>20.0){
					if (max==-1 || max > x/y) max = x/y;
				}
				else if (min<x/y+1) min = x/y+1;
			}
		}
	}
}

int main()
{
	int T, P, tot[200], m[200], acertos[200], a, b;
	char str[9];
	while(true){
		scanf("%d %d", &T, &P);
		if (T==0 && P==0) break;
		min=1;
		max=-1;
		for (int t=0; t<T; t++){
			acertos[t]=m[t]=tot[t]=0;
			for (int p=0; p<P; p++){
				scanf(" %s", str);
				if (str[strlen(str)-1]=='-') continue;
				sscanf(str, "%d/%d", &a, &b);
				acertos[t]++;
				tot[t]+=b;
				m[t]+=a;
			}
		}
		for(int i=0; i<T; i++){
			for (int j=0; j<T; j++){
				if (acertos[i]<acertos[j]){
					a=acertos[i];
					acertos[i]=acertos[j];
					acertos[j]=a;
					a=tot[i];
					tot[i]=tot[j];
					tot[j]=a;
					a=m[i];
					m[i]=m[j];
					m[j]=a;
				}
			}
		}
		b=0;
		for(int i=1; i<T; i++){
			if (acertos[i]!=acertos[b]){
				atualizar(m+b, tot+b, i-b);
				b=i;
			}
		}
		atualizar(m+b, tot+b, T-b);
		printf("%d ", min);
		if (max!=-1) printf("%d\n", max);
		else printf("*\n");
	}
	return 0;
}