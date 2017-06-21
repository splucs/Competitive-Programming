#include <cstdio>
#include <cstdlib>
#include <map>
using namespace std;
double adj[301][301];
class node{
public:
    node(){
        filho1=NULL;
        filho2=NULL;
        pai=NULL;
    }
    node* filho1;
    node* filho2;
    node* pai;
    map<int, double> prob;
};
void calcular(node* no){
    if (no->filho1==NULL || no->filho2==NULL) return;
    calcular(no->filho1);
    calcular(no->filho2);
    map<int, double>::iterator it1;
    map<int, double>::iterator it2;
    double x;
    for (it1=no->filho1->prob.begin(); it1!=no->filho1->prob.end(); it1++){
        x=0.0;
        for (it2=no->filho2->prob.begin(); it2!=no->filho2->prob.end(); it2++){
            x+=adj[it1->first][it2->first]*it2->second;
        }
        x*=it1->second;
        no->prob[it1->first]=x;
    }
    for (it1=no->filho2->prob.begin(); it1!=no->filho2->prob.end(); it1++){
        x=0.0;
        for (it2=no->filho1->prob.begin(); it2!=no->filho1->prob.end(); it2++){
            x+=adj[it1->first][it2->first]*it2->second;
        }
        x*=it1->second;
        no->prob[it1->first]=x;
    }
}
int main()
{
    int N, x, y;
    while(true){
        scanf("%d", &N);
        if (N==0) break;
        node* corridas;
        corridas = new node[2*N]();
        for (int i=1; i<=N; i++){
            for (int j=1; j<=N; j++){
                scanf("%lf", &adj[i][j]);
            }
            corridas[i].prob[i]=1.0;
        }
        for (int i=N+1; i<2*N; i++){
            scanf("%d %d", &x, &y);
            corridas[x].pai=&corridas[i];
            corridas[y].pai=&corridas[i];
            corridas[i].filho1=&corridas[x];
            corridas[i].filho2=&corridas[y];
        }
        for (int i=1; i<2*N; i++){
            if (corridas[i].pai==NULL){
                calcular(&corridas[i]);
                printf("%.6f\n", corridas[i].prob[1]);
                break;
            }
        }
        delete[] corridas;
    }
    return 0;
}
