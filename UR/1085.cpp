#include <iostream>
#include <map>
using namespace std;
typedef struct node{
    int d[2];
    char a[2];
    bool vis[2];
} node;
typedef struct aresta{
    int dist;
    char a;
} aresta;
map<string, node> idiomas;
map< string, map<string, map<string, aresta> > > mapa;
int main()
{
    string O, D, I1, I2, P, pivot;
    int minD, M, caminho;
    node aux;
    node* p;
    while (true)
    {
        idiomas.clear();
        mapa.clear();
        cin >> M;
        if (M==0) break;
        cin >> O >> D;
        aux.a[0] = aux.a[1] = '1';
        aux.d[0] = aux.d[1] = -1;
        aux.vis[0] = aux.vis[1] = false;
        idiomas[O]=idiomas[D]=aux;
        while (M-->0){
            cin>> I1 >> I2 >> P;
            idiomas[I1]=idiomas[I2]=aux;
            mapa[I1][I2][P].dist = mapa[I2][I1][P].dist = P.size();
            mapa[I1][I2][P].a = mapa[I2][I1][P].a = P[0];
        }
        caminho = 0;
        pivot = O;
        idiomas[O].d[0]=0;
        do{
            aux = idiomas[pivot];
         //   cout << "verificando no " << pivot << " no caminho " << aux.a[caminho] <<endl;
            idiomas[pivot].vis[caminho]=true;
            map<string, map<string, aresta> >::iterator it;
            map<string, aresta>::iterator it2;
            for (it=mapa[pivot].begin(); it!=mapa[pivot].end(); it++){
                for (it2=it->second.begin(); it2!=it->second.end(); it2++){
                 //   cout << "  olhando aresta de "<< pivot <<" para "<<it->first<<" it2->second.a="<< it2->second.a<<endl;
                    p=&idiomas[it->first];
                    if (it2->second.a==aux.a[caminho]) continue;
                    if (p->d[0]==-1){
                        p->d[0]=aux.d[caminho] + it2->second.dist;
                        p->a[0]=it2->second.a;
                    //    cout << "    posicao 0 do no " << it->first << " alterada para a=" << it2->second.a << " e d=" << p->d[0] << endl;
                    }
                    else if (p->d[1]==-1 && p->a[0]!=it2->second.a){
                        p->d[1]=aux.d[caminho] + it2->second.dist;
                        p->a[1]=it2->second.a;
                     //   cout << "    posicao 1 do no " << it->first << " alterada para a=" << it2->second.a << " e d=" << p->d[1] << endl;
                    }
                    else if (p->d[1]==-1){
                        if (p->d[0] > aux.d[caminho] + it2->second.dist){
                            p->d[0] = aux.d[caminho] + it2->second.dist;
                            p->a[0] = it2->second.a;
                        }
                    }
                    else if (p->d[0]>p->d[1]){
                        if (p->a[1]==it2->second.a){
                            if (p->d[1] > aux.d[caminho] + it2->second.dist){
                                p->d[1] = aux.d[caminho] + it2->second.dist;
                        //        cout << "    posicao 1 do no " << it->first << " alterada para a=" << it2->second.a << " e d=" << p->d[1] << endl;
                            }
                        }
                        else if (p->d[0] > aux.d[caminho] + it2->second.dist){
                            p->d[0] = aux.d[caminho] + it2->second.dist;
                            p->a[0] = it2->second.a;
                         //   cout << "    posicao 0 do no " << it->first << " alterada para a=" << it2->second.a << " e d=" << p->d[0] << endl;
                        }
                    }
                    else{
                        if (p->a[0]==it2->second.a){
                            if (p->d[0] > aux.d[caminho] + it2->second.dist){
                                p->d[0] = aux.d[caminho] + it2->second.dist;
                        //        cout << "    posicao 0 do no " << it->first << " alterada para a=" << it2->second.a << " e d=" << p->d[0] << endl;
                            }
                        }
                        else if (p->d[1] > aux.d[caminho] + it2->second.dist){
                            p->d[1] = aux.d[caminho] + it2->second.dist;
                            p->a[1] = it2->second.a;
                         //   cout << "    posicao 1 do no " << it->first << " alterada para a=" << it2->second.a << " e d=" << p->d[1] << endl;
                        }
                    }
                }
            }
            caminho=2;
            map<string, node>::iterator itl;
            for (itl=idiomas.begin(); itl!=idiomas.end(); itl++){
                for (int i=0; i<2; i++){
                    if (itl->second.d[i]!=-1 && !itl->second.vis[i] && (caminho==2 || minD>itl->second.d[i])){
                        minD = itl->second.d[i];
                        caminho=i;
                        pivot = itl->first;
                    }
                }
            }
        }while (caminho!=2);
        aux=idiomas[D];
        if (aux.d[0]==-1 && aux.d[1]==-1) cout <<"impossivel" << endl;
        else if (aux.d[0]==-1) cout << aux.d[1] << endl;
        else if (aux.d[1]==-1) cout << aux.d[0] << endl;
        else cout << (aux.d[0]>aux.d[1] ? aux.d[1]:aux.d[0]) << endl;
    }
    return 0;
}
