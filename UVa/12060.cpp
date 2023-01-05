#include <cstdio>
#define max(a,b) (a>b?a:b)

int gdc(int a, int b){
	if (b==0) return a;
	else return gdc(b, a%b);
}

int numalg(int n){
	int res=0;
	while(n>0){
		n/=10;
		res++;
	}
	return res;
}

int main(){
	int a, b, c, alga, algb, algc, aux, caseNo = 1;
	bool isneg, isfrac;
	while(scanf("%d", &c), c){
		b=0;
		for(int i=0; i<c; i++){
			scanf("%d", &aux);
			b += aux;
		}

		isneg = false;
		if (b<0){
			b*=-1;
			isneg=true;
		}

		aux = gdc(b, c);
		c /= aux;
		b /= aux;

		a = b/c;
		b %= c;

		isfrac = (b!=0);

		alga = numalg(a);
		algc = numalg(c);
		algb = numalg(b);

		printf("Case %d:\n", caseNo++);

		if (a==0 && b==0) {
			printf("0\n");
			continue;
		}

		if (isfrac){
			if (isneg) printf("  ");
			for(int i=0; i<alga; i++) printf(" ");
			for(int i=0; i<max(algb, algc) - algb; i++) printf(" ");
			printf("%d\n", b);
		}

		if (isneg) printf("- ");
		if (a>0) printf("%d", a);
		if (isfrac){
			for(int i=0; i<max(algb, algc); i++) printf("-");
		}
		printf("\n");

		if (isfrac){
			if (isneg) printf("  ");
			for(int i=0; i<alga; i++) printf(" ");
			for(int i=0; i<max(algb, algc) - algc; i++) printf(" ");
			printf("%d\n", c);
		}

	}
	return 0;
}