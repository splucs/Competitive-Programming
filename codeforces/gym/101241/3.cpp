#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=(a);i<(b);i++)
#define REP(i,a,b) for (int i=(a);i<=(b);i++)
#define PER(i,b,a) for (int i=(b);i>=(a);i--)

typedef pair<int, int> ii;
typedef long long ll;

struct node{
    vector<int> next;
    vector<int> pd;
    int depth;
    string nome;    
    int melhor;
    node(){
        next.clear();
        pd.clear();
        nome = "";
        depth = 0;
    }
    node(string n, int d){
        nome = n;
        next.clear();
        pd.clear();
        depth = d;
    }
};

vector<node> tree;

void read(){
    int d = 0;
    string s;
    while(cin>>s){
        if(s=="|") d++;
        else{
            tree.push_back(node(s, d));
            d = 0;
        }
    }
}

int p;
void build(int x){
    while(tree[x].depth<tree[p].depth){
        tree[x].next.push_back(p);
        p++;
        if(tree[p-1].nome[0]!='.')
            build(p-1);
    }
}

const int INF = 999999999;
vector<int> aux;
int w;
void DFS(int x){
    if(tree[x].next.size()==0){
        tree[x].pd.resize(w+2, 0);
        tree[x].pd[0] = INF;
        return;
    }
    for(vector<int>::iterator it = tree[x].next.begin(), fim = tree[x].next.end(); it!=fim; it++){
        DFS(*it);
    }
    tree[x].pd.resize(w+2, 0);
    tree[x].pd[0] = INF;
    for(vector<int>::iterator it = tree[x].next.begin(), fim = tree[x].next.end(); it!=fim; it++){
        for(int i = 1; i<=w; i++){
            int menor = INF;
            for(int j = 1; j<=i; j++){
                menor = min(menor, tree[x].pd[j] + tree[*it].pd[i-j]);
            }
            aux[i] = menor;
        }
        for(int i = 1; i<w; i++){
            tree[x].pd[i] = aux[i];
        }
    }
}

void print(int x){
    for(int i = 0; i<tree[x].depth; i++){
        printf("| ");
    }
    cout<<tree[x].nome<<endl;

}

void DFS2(int x, int l){
    if(l==1){
        if(tree[x].nome[0]!='.')
            tree[x].nome[0] = '+';
        print(x);
        return;
    }
    tree[x].nome[0] = '-';
    print(x);

    tree[x].pd.resize(w+2, 0);
    tree[x].pd[0] = INF;
    for(vector<int>::iterator it = tree[x].next.begin(), fim = tree[x].next.end(); it!=fim; it++){
        for(int i = 1; i<=w; i++){
            int menor = INF;
            int y;
            for(int j = 1; j<=i; j++){
                y = tree[x].pd[j] + tree[*it].pd[i-j];
                if(y<menor){
                    menor = y;
                }
            }
            aux[i] = menor;
        }
        for(int i = 1; i<w; i++){
            tree[x].pd[i] = aux[i];
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    cin>>w;
    read();
    p = 0;
    aux.resize(w);
    int tam = tree.size();
    while(p<=tam){
        p++;
        build(p-1);
    }

    // for(int i = 0; i<tree.size(); i++){
    //     cout<<i<<": "<<tree[i].nome<<" "<<tree[i].depth<<" (";
    //     for(int j = 0; j<tree[i].next.size(); j++){
    //         cout<<tree[i].next[j]<<", ";
    //     }
    //     cout<<")\n";
    // }

    for(int i = 0; i<tam; i++){
        if(tree[i].depth==0) DFS(i);
    }
    for(int i = 0; i<tam; i++){
        if(tree[i].depth==0 || tree[i].nome[0]=='+') DFS2(i, w);
    }
}