#include <bits/stdc++.h>

using namespace std;

#define INF (1<<30)
const int neutral = 0; //comp(x, neutral) = x
long long comp(long long a, long long b) {
    return a + b;
}

class SegmentTree {
private:
    vector<long long> st, lazy;
    int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
    void build(int p, int l, int r, long long* A) {
        if (l == r) {
            st[p] = A[l];
        }
        else {
            build(left(p), l, (l + r) / 2, A);
            build(right(p), (l + r) / 2 + 1, r, A);
            st[p] = comp(st[left(p)], st[right(p)]);
        }
    }
    void push(int p, int l, int r) {
        st[p] += (r - l + 1)*lazy[p];   //Caso RSQ
        //st[p] += lazy[p];             //Caso RMQ
        if (l != r) {
            lazy[right(p)] += lazy[p];
            lazy[left(p)] += lazy[p];
        }
        lazy[p] = 0;
    }
    void update(int p, int l, int r, int a, int b, long long k) {
        push(p, l, r);
        if (a > r || b < l) return;
        else if (l >= a && r <= b) {
            lazy[p] = k; push(p, l, r);
        }
        else {
            update(left(p), l, (l + r) / 2, a, b, k);
            update(right(p), (l + r) / 2 + 1, r, a, b, k);
            st[p] = comp(st[left(p)], st[right(p)]);
        }
    }
    long long query(int p, int l, int r, int a, int b) {
        push(p, l, r);
        if (a > r || b < l) return neutral;
        if (l >= a && r <= b) return st[p];
        long long p1 = query(left(p), l, (l + r) / 2, a, b);
        long long p2 = query(right(p), (l + r) / 2 + 1, r, a, b);
        return comp(p1, p2);
    }
public:
    SegmentTree(long long* begin, long long* end) {
        size = (int)(end - begin);
        st.assign(4 * size, neutral);
        lazy.assign(4 * size, 0);
        build(1, 0, size - 1, begin);
    }
    long long query(int a, int b) { return query(1, 0, size - 1, a, b); }
    void update(int a, int b, long long k) { update(1, 0, size - 1, a, b, k); }
};
typedef pair<int, int> ii;
typedef pair<ii, int> piii;
vector<int> grafo[100100];
long long info[100100];
priority_queue<piii, vector<piii>, greater<piii> > pq;
long long lca[200500] = {0};
ii pos[100100];
int tech[100100];
int tam;

void DFS(int x, int d){
    pos[x].first = tam++;
    pq.push(piii(ii(tech[x], d), x));
    for(vector<int>::iterator it = grafo[x].begin(); it!=grafo[x].end(); it++){
        DFS(*it, d+1);
    }
    pos[x].second = tam++;
}

int main(){
    int n;
    int x, y, z;
    vector<int> raiz;
    scanf("%d", &n);
    for(int i = 1; i<=n; i++){
        scanf("%d %d %d", &x, &y, &z);
        info[i] = (long long) z;
        // pq.push(ii(ii(y, ), i));
        tech[i] = y;
        if(x!=-1){
            grafo[x].push_back(i);
        }else{
            raiz.push_back(i);
        }
    }
    tam = 0;
    for(vector<int>::iterator it = raiz.begin(); it!=raiz.end(); it++){
        DFS(*it, 0);
    }
    long long aux;
    SegmentTree st(lca, lca+tam);
    while(!pq.empty()){
        x = pq.top().second;
        pq.pop();
        aux = info[x];
        info[x] = st.query(pos[x].first, pos[x].second);
        st.update(pos[x].first, pos[x].first, aux);
    }
    for(int i = 1; i<=n; i++){
        cout<<info[i]<<endl;
    }

}