#include <bits/stdc++.h>
using namespace std;
#define MAXN 64
#define max(x, y) ((x) < (y) ? (y) : (x))

int pressure[MAXN];
vector<int> g[MAXN];
int n = 0;

map<string, int> nodes;
int getNode(string s) {
    if (!nodes.count(s)) {
        nodes[s] = n++;
    }
    return nodes[s];
}

int reduced[MAXN];
int reducedCnt = 0;
int reduce(int u) {
    reduced[u] = reducedCnt;
    reducedCnt++;
}

void readInput() {
    int p;
    char valve[4], valves[109], trash[109];
    while(scanf("Valve %s has flow rate=%d; %s %s to %s ", valve, &p, trash, trash+10, trash+20) != EOF) {
        int u = getNode(string(valve));
        pressure[u] = p;
        if (p > 0) {
            reduce(u);
        }

        gets(valves);
        int m = strlen(valves);
        for (int i = 0; i < m; i+=4) {
            string s;
            s.push_back(valves[i]);
            s.push_back(valves[i+1]);
            int v = getNode(s);
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
}

int dp[2][33009][MAXN][MAXN];

int main() {
    readInput();
    memset(dp, 0, sizeof dp);

    for (int d = 0; d <= 26; d++) {
        for(int u = 0; u < n; u++) for(int w = 0; w < n; w++) {
            for(int mask = 0; mask < (1<<reducedCnt); mask++) {
                int &res = dp[d&1][mask][u][w];
                res = 0;
                // base case
                if (d == 0) {
                    continue;
                }
                // optimization with symmetry
                if (w < u) {
                    res = dp[d&1][mask][w][u];
                    continue;
                }

                // case 1, u opens valve, w expands
                if (pressure[u] > 0) {
                    int ru = reduced[u];
                    if (!(mask & (1<<ru))) {
                        int newRes;
                        for (int gw : g[w]) {
                            newRes = dp[(d+1)&1][mask|(1<<ru)][u][gw] + (d-1)*pressure[u];
                            res = max(res, newRes);
                        }
                    }
                }

                // case 2, w opens valve, u expands
                if (pressure[w] > 0) {
                    int rw = reduced[w];
                    if (!(mask & (1<<rw))) {
                        int newRes;
                        for (int gu : g[u]) {
                            newRes = dp[(d+1)&1][mask|(1<<rw)][gu][w] + (d-1)*pressure[w];
                            res = max(res, newRes);
                        }
                    }
                }

                // case 3, both open valve
                if (pressure[u] > 0 && pressure[w] > 0 && u != w) {
                    int ru = reduced[u];
                    int rw = reduced[w];
                    if (!(mask & (1<<ru)) && !(mask & (1<<rw))) {
                        int newRes = dp[(d+1)&1][mask|(1<<ru)|(1<<rw)][u][w] + (d-1)*(pressure[u]+pressure[w]);
                        res = max(res, newRes);
                    }
                }

                //case 4, both expand
                int newRes;
                for (int gu : g[u]) for (int gw : g[w]) {
                    newRes = dp[(d+1)&1][mask][gu][gw];
                    res = max(res, newRes);
                }
            }
        }
    }
    printf("%d\n", dp[26&1][0][getNode("AA")][getNode("AA")]);
    return 0;
}