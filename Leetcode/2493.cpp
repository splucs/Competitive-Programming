class Solution {
private:
    int n;
    vector<vector<int>> g;
    vector<int> color;
    void paint(int u) {
        for (int v : g[u]) {
            if (color[v] != 0) {
                continue;
            }
            color[v] = color[u];
            paint(v);
        }
    }
    
    int calculateMaxDist(int st) {
        vector<int> dist(n+1, 0);
        vector<int> q;
        int ans = 0;

        dist[st] = 1;
        q.push_back(st);
        for (int front = 0; front < (int)q.size(); front++) {
            int u = q[front];
            ans = max(ans, dist[u]);
            for (int v : g[u]) {
                if (dist[v] == dist[u]) {
                    return -1;
                }
                if (dist[v] == 0) {
                    dist[v] = dist[u] + 1;
                    q.push_back(v);
                }
            }
        }
        return ans;
    }
public:
    int magnificentSets(int _n, vector<vector<int>>& edges) {
        n = _n;
        g.resize(n+1);
        for (const vector<int>& edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        int nColors = 0;
        color.assign(n+1, 0);
        for (int u = 1; u <= n; u++) {
            if (color[u] == 0) {
                color[u] = ++nColors;
                paint(u);
            }
        }

        vector<int> ansByColor(nColors+1, 0);
        for (int u = 1; u <= n; u++) {
            int c = color[u];
            int maxDist = calculateMaxDist(u);
            if (maxDist == -1) {
                return -1;
            }
            ansByColor[c] = max(ansByColor[c], maxDist);
        }

        int ans = 0;
        for (int c = 1; c <= nColors; c++) {
            ans += ansByColor[c];
        }
        return ans;
    }
};
