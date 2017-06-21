#include <cstdio>
#include <map>
using namespace std;

map<int, map<int, bool> > mapa;
map<int, char> output;
int valores[40], aux[40], soma[40], original[40];
char det[40];
void mergesort(int a, int b){
    if (a==b) return;
    int med = (a+b)/2;
    mergesort(a, med);
    mergesort(med+1, b);
    int i=a, j=med+1, k=a;
    while(i<=med && j<=b){
        if (valores[i]<valores[j]) aux[k++]=valores[i++];
        else aux[k++]=valores[j++];
    }
    while(i<=med) aux[k++]=valores[i++];
    while(j<=b) aux[k++]=valores[j++];
    for (i=a; i<k; i++) valores[i]=aux[i];
}
bool existe(int n, int quantia){
    if (n==0){
        if (quantia - valores[0] == 0){
            if (det[0]=='+' || det[0]=='\0') det[0]='+';
            else if (det[0]=='-') det[0]='?';
            return true;
        }
        else if (quantia + valores[0] == 0){
            if (det[0]=='-' || det[0]=='\0') det[0]='-';
            else if (det[0]=='+') det[0]='?';
            return true;
        }
        else return false;
    }
    if(mapa.find(n)!=mapa.end() && mapa[n].find(quantia)!=mapa[n].end()) return mapa[n][quantia];
    bool exi=false;
    if (quantia-valores[n]+soma[n]>=0 && existe(n-1, quantia-valores[n])){
        if (det[n]=='+' || det[n]=='\0') det[n]='+';
        else if (det[n]=='-') det[n]='?';
        mapa[n][quantia]=true;
    }
    if (quantia+valores[n]-soma[n]<=0 && existe(n-1, quantia+valores[n])){
        if (det[n]=='-' || det[n]=='\0') det[n]='-';
        else if (det[n]=='+') det[n]='?';
        mapa[n][quantia]=true;
    }
    if (det[n]=='\0') mapa[n][quantia]=false;
    return mapa[n][quantia];
}
int main()
{
    int N, F;
    while(true){
        scanf("%d %d", &N, &F);
        if (N==0 && F==0) break;
        mapa.clear();
        for (int i=0; i<N; i++){
            scanf("%d", valores+i);
            original[i]=valores[i];
            det[i]='\0';
        }
        mergesort(0, N-1);
        soma[0]=0;
        for (int i=1; i<N; i++){
            soma[i]=valores[i-1] + soma[i-1];
        }
        if (!existe(N-1, F)) printf("*\n");
        else {
            output.clear();
            for (int i=0; i<N; i++){
                output[valores[i]]=det[i];
            }
            for (int i=0; i<N; i++){
                printf("%c", output[original[i]]);
            }
            printf("\n");
        }
    }
    return 0;
}
