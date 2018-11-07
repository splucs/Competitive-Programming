#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define MAXN 509
#define INF 0x3f3f3f3f

int n, adjMatrix[MAXN][MAXN];
vector<int> bestCut;

// Modifica o grafo!!!! Se precisar do grafo depois faça uma cópia
int mincut() {
    int bestCost = INF;
    vector<int> v[MAXN];
    for (int i=0; i<n; ++i)
        v[i].assign (1, i);
    int w[MAXN], sel;
    bool exist[MAXN], added[MAXN];
    memset (exist, true, sizeof exist);
    for (int phase=0; phase<n-1; ++phase) {
        memset (added, false, sizeof added);
        memset (w, 0, sizeof w);
        for (int j=0, prev; j<n-phase; ++j) {
            sel = -1;
            for (int i=0; i<n; ++i) {
                if (exist[i] && !added[i] && (sel == -1 || w[i] > w[sel]))
                    sel = i;
            }
            if (j == n-phase-1) {
                if (w[sel] < bestCost) {
                    bestCost = w[sel];
                    bestCut = v[sel];
                }
                v[prev].insert (v[prev].end(), v[sel].begin(), v[sel].end());
                for (int i=0; i<n; ++i) adjMatrix[prev][i] = adjMatrix[i][prev] += adjMatrix[sel][i];
                exist[sel] = false;
            }
            else {
                added[sel] = true;
                for (int i=0; i<n; ++i)  w[i] += adjMatrix[sel][i];
                prev = sel;
            }
        }
    }
    return bestCost;
}

int main() {
    return 0;
}