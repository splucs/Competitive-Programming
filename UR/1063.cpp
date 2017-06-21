#include <cstdio>
#include <stack>
using namespace std;
int main()
{
    int N;
    scanf("%d", &N);
    while(N>0){
        char entra[N], sai[N];
        for (int i=0; i<N; i++){
            scanf(" %c", entra+i);
        }
        for (int i=0; i<N; i++){
            scanf(" %c", sai+i);
        }
        stack<char> pilha;
        bool ok = true;
        int counter=0;
        for (int i=0; i<N; i++){
            while((pilha.empty() || pilha.top()!=sai[i]) && counter<N){
                pilha.push(entra[counter++]);
                printf("I");
            }
            if (counter>=N && pilha.top()!=sai[i]){
                ok = false;
                break;
            }
            else{
                pilha.pop();
                printf("R");
            }
        }
        if (ok) printf("\n");
        else printf(" Impossible\n");
        scanf("%d", &N);
    }
    return 0;
}
