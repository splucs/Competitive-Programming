#include <cstdio>
#include <cmath>

double s(double x){
	return x*x;
}

int main()
{
	double X, Y, Dx, Dy, A, B, a, b, lambda, lambdal, D, Dxl, Dyl, DN, N, al, bl;
	while(scanf("%lf %lf %lf %lf %lf %lf", &X, &Y, &Dx, &Dy, &A, &B)!=EOF){
		lambda=(sqrt(s(Dx/A)+s(Dy/B)-s((Y*Dx-X*Dy)/(A*B))) - (X*Dx)/s(A) - (Y*Dy)/s(B))/(s(Dx/A)+s(Dy/B));
		a=X+lambda*Dx;
		b=Y+lambda*Dy;
		printf("%.3f %.3f\n", a, b);
		D = sqrt(s(Dx)+s(Dy));
		N=sqrt(s(a/s(A))+s(b/s(B)));
		DN=(Dx*a)/s(A)+(Dy*b)/s(B);
		if (Dx*b*s(A)==Dy*a*s(B)){
			Dxl=-Dx;
			Dyl=-Dy;
		}
		else{
			Dxl=(Dy*DN - b*(s(D)/s(B))*(2*s(DN/(N*D))-1))/(Dx*b/s(B)-Dy*a/s(A));
			Dyl=(a*(s(D)/s(A))*(2*s(DN/(N*D))-1) - Dx*DN)/(Dx*b/s(B)-Dy*a/s(A));
		}
		lambdal=(sqrt(s(Dxl/A)+s(Dyl/B)-s((b*Dxl-a*Dyl)/(A*B))) - (a*Dxl)/s(A) - (b*Dyl)/s(B))/(s(Dxl/A)+s(Dyl/B));
		al=a+lambdal*Dxl;
		bl=b+lambdal*Dyl;
		printf("%.3f %.3f\n", al, bl);
	}
	return 0;
}