#include <cstdio>

int M, N;

class star{
public:
    star(){
        planes = new bool[M]();
    }
    virtual ~star(){
        delete[] planes;
    }
    bool* planes;
};

bool isGreater(star *a, star *b){
    for (int i=0; i<M; i++){
        if (a->planes[i]!=b->planes[i] && a->planes[i]) return true;
        else if (a->planes[i]!=b->planes[i]) return false;
    }
    return true;
}

bool isEqual(star *a, star *b){
    for (int i=0; i<M; i++){
        if (a->planes[i]!=b->planes[i]) return false;
    }
    return true;
}

void mergesort(star** stars, star** aux, int a, int b){
    if (a==b) return;
    int med = (a+b)/2;
    mergesort(stars, aux, a, med);
    mergesort(stars, aux, med+1, b);
    int i=a, j=med+1, k=a;
    while (i<=med && j<=b){
        if (isGreater(stars[i], stars[j])) aux[k++]=stars[j++];
        else aux[k++]=stars[i++];
    }
    while (i<=med)
    {
        aux[k++]=stars[i++];
    }
    while (j<=b){
        aux[k++]=stars[j++];
    }
    for (i=a; i<=b; i++){
        stars[i]=aux[i];
    }
}

int main()
{
    scanf("%d %d", &M, &N);
    long long int A[M], B[M], C[M], D[M];
    int X, Y, Z;
    for(int i=0; i<M; i++){
        scanf("%lld %lld %lld %lld", A+i, B+i, C+i, D+i);
    }
    star **stars, **aux;
    stars = new star*[N]();
    aux = new star*[N]();
    for (int i=0; i<N; i++){
        stars[i] = new star();
        scanf("%d %d %d", &X, &Y, &Z);
        for (int j=0; j<M; j++){
            if (A[j]*X + B[j]*Y + C[j]*Z > D[j]) stars[i]->planes[j]=true;
            else stars[i]->planes[j]=false;
        }
    }
    mergesort(stars, aux, 0, N-1);
    int cont=1, atual=1;
    for (int i=1; i<N; i++){
        if (isEqual(stars[i], stars[i-1])){
            atual++;
        }
        else {
            if(cont<atual) cont = atual;
            atual=1;
        }
    }
    if(cont<atual) cont = atual;
    printf("%d\n", cont);
    for (int i=0; i<N; i++){
        delete stars[i];
    }
    delete[] stars;
    delete[] aux;
    return 0;
}
