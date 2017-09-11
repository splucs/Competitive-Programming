#include <bits/stdc++.h>

using namespace std;

int valor[100100] = {0};
vector<int> grafo[100100];

int DFS(int x){
    for(vector<int>::iterator it = grafo[x].begin(); it!=grafo[x].end(); it++){
        if(valor[*it]==0){
            valor[*it] = -valor[x];
            DFS(*it);
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, g;
    scanf("%d %d", &n, &g);
    int m, x;
    for(int i = 1; i<=n; i++){
        cin>>m;
        for(int j = 0; j<m; j++){
            scanf("%d", &x);
            grafo[i].push_back(x);
        }
    }

    valor[g] = 1;
    DFS(g);
    for(int i = 1; i<=n; i++){
        if(grafo[i].size()<=1){
            if(valor[i]==1)printf("CW\n");
            else if(valor[i]==-1) printf("CCW\n");
            else printf("%c\n", 45);
        }
    }

}