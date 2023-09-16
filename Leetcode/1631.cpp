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
    int di[2] = {1, 0};
    int dj[2] = {0, 1};
    inline int abs(int x) {
        return x < 0 ? -x : x;
    }
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        vector<pair<int, pair<int, int>>> dists;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int u = i*m + j;
                for (int dir = 0; dir < 2; dir++) {
                    int ni = i + di[dir];
                    int nj = j + dj[dir];
                    if (ni >= n || nj >= m) continue;
                    int v = ni*m + nj;

                    int d = abs(heights[i][j]-heights[ni][nj]);
                    dists.push_back(make_pair(d, make_pair(u, v)));
                }
            }
        }
        sort(dists.begin(), dists.end());
        UnionFind uf(n*m);
        int ans = 0;
        for (auto ppp : dists) {
            int d = ppp.first;
            int u = ppp.second.first;
            int v = ppp.second.second;
            if (uf.find(u) == uf.find(v)) {
                continue;
            }
            ans = max(ans, d);
            uf.merge(u, v);
            if (uf.find(0) == uf.find(n*m-1)) {
                break;
            }
        }
        return ans;
    }
};
