#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

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

int dp[2][33009][MAXN];

int main() {
    readInput();

    for (int d = 0; d <= 30; d++) {
        for(int u = 0; u < n; u++) {
            for(int mask = 0; mask < (1<<reducedCnt); mask++) {
                int &res = dp[d&1][mask][u];
                res = 0;
                // base case
                if (d == 0) {
                    continue;
                }

                // if current has pressure, try open;
                if (pressure[u] > 0) {
                    int ru = reduced[u];
                    if (!(mask & (1<<ru))) {
                        res = dp[(d+1)&1][mask|(1<<ru)][u] + (d-1)*pressure[u];
                    }
                }

                // expand
                for (int v : g[u]) {
                    res = max(res, dp[(d+1)&1][mask][v]);
                }
            }
        }
    }
    printf("%d\n", dp[30&1][0][getNode("AA")]);
    return 0;
}