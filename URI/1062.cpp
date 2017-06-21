#include <cstdio>
#include <stack>
using namespace std;
int main()
{
    int N, atual, counter;
    scanf("%d", &N);
    while (N>0)
    {
        scanf("%d", &atual);
        if (0==atual){
            scanf("%d", &N);
            printf("\n");
            continue;
        }
        counter=1;
        stack<int> fila;
        bool pode=true;
        for (int i=0; i<N; i++)
        {
            if (!pode){}
            else if (atual>=counter){
                while (atual>counter) fila.push(counter++);
                counter++;
            }
            else if(fila.empty()){
                pode=false;
            }
            else if(fila.top()==atual){
                fila.pop();
            }
            else pode=false;
            if (i<N-1) scanf("%d", &atual);
        }
        if (pode) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
