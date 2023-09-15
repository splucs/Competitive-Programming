struct UnionFind {
    vector<int> par;
    UnionFind(int n) {
        par.resize(n);
        for (int i = 0; i < n; i++) par[i] = i;
    }
    int find(int u) {
        if (par[u] == u) return u;
        return par[u] = find(par[u]);
    }
    void merge(int u, int v) {
        par[find(u)] = find(v);
    }
};

class Solution {
private:
    inline int abs(int x) {
        return x < 0 ? -x : x;
    }
    inline int manhattanDist(int x1, int y1, int x2, int y2) {
        return abs(x2-x1) + abs(y2-y1);
    }
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        vector<vector<pair<int, int>>> dists(1);
        int n = points.size();
        for (int i = 0; i < n; i++) {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = 0; j < i; j++) {
                int x2 = points[j][0], y2 = points[j][1];
                int d = manhattanDist(x1, y1, x2, y2);

                while (dists.size() <= d) {
                    dists.resize(2*dists.size());
                }
                dists[d].push_back(make_pair(i, j));
            }
        }
        UnionFind uf(n);
        int ans = 0;
        for (int d = 0; d < (int)dists.size(); d++) {
            for (pair<int, int> pp : dists[d]) {
                int i = pp.first;
                int j = pp.second;
                if (uf.find(i) == uf.find(j)) {
                    continue;
                }

                ans += d;
                uf.merge(i, j);
            }
        }
        return ans;
    }
};
