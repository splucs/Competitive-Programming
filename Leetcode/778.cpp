class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {-1, 0, 1, 0};
    vector<int> par, sz;
    int find(int u) {
        if (par[u] == u) {
            return u;
        }
        return par[u] = find(par[u]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) {
            return;
        }
        if (sz[u] > sz[v]) {
            swap(u, v);
        }
        par[u] = v;
        sz[v] += sz[u];
    }
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = n*n;
        vector<vector<int>> g(m, vector<int>());
        par.resize(m);
        sz.resize(m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int u = grid[i][j];
                par[u] = u;
                sz[u] = 1;
                for (int dir = 0; dir < 4; dir++) {
                    int ni = i + di[dir];
                    int nj = j + dj[dir];
                    if (ni < 0 || nj < 0 || ni >= n || nj >= n) {
                        continue;
                    }
                    int v = grid[ni][nj];
                    if (u > v) {
                        g[u].push_back(v);
                    }
                }
            }
        }
        int st = grid[0][0], en = grid[n-1][n-1], u = -1;
        do {
            u++;
            for (int v : g[u]) {
                merge(u, v);
            }
        } while (find(st) != find(en));
        return u;
    }
};
