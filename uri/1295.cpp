#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef struct vetor{
	double x;
	double y;
} vetor;

bool menorX(vetor a, vetor b){
	if (a.x<b.x) return true;
	else return false;
}
bool menorY(vetor* a, vetor* b){
	if (a->y<b->y) return true;
	else return false;
}

double dist(vetor* a, vetor* b){
	return sqrt((a->x-b->x)*(a->x-b->x) + (a->y-b->y)*(a->y-b->y));
}

vetor vet[10009], *aux[10009];

double trmin(double a, double b, double c){
	c = (c>a?a:c);
	return (c>b?b:c);
}

double twmin(double a, double b){
	return (a>b?b:a);
}

double menorDist(int a, int b){
	if (a+2==b){
		return trmin(dist(&vet[a], &vet[a+1]), dist(&vet[a], &vet[a+2]), dist(&vet[a+1], &vet[a+2]));
	}
	if (a+1==b) return dist(&vet[a], &vet[b]);
	if (a==b) return 10009.0;
	int med = (a+b)/2, pdivisa=0;
	double d = twmin(menorDist(a, med), menorDist(med+1, b));
	double p = (vet[med].x + vet[med+1].x)/2.0;
	for (int i=med; i>=a && p - vet[i].x < d; i--) aux[pdivisa++]=&vet[i];
	for (int i=med+1; i<=b && vet[i].x - p < d; i++) aux[pdivisa++]=&vet[i];
	sort(aux, aux+pdivisa, &menorY);
	for(int i=0; i<pdivisa; i++){
		for(int j=i+1; j<pdivisa && aux[j]->y - aux[i]->y < d; j++){
			d = twmin(d, dist(aux[i], aux[j]));
		}
	}
	return d;
}

int main()
{
	int N;
	double Dmin;
	while(true){
		scanf("%d", &N);
		if (N==0) break;
		for(int i=0; i<N; i++){
			scanf("%lf %lf", &vet[i].x, &vet[i].y);
		}
		sort(vet, vet+N, &menorX);
		Dmin = menorDist(0, N-1);
		if (Dmin>10000.0) printf("INFINITY\n");
		else printf("%.4f\n", Dmin);
	}
	return 0;
}
