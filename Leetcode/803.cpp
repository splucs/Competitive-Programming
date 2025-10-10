class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
    int n, m, nm;
    vector<int> getNeighbors(int u) {
        int i = u/m, j = u%m;
        vector<int> ans;
        for (int dir = 0; dir < 4; dir++) {
            int ni = i + di[dir];
            int nj = j + dj[dir];
            if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                continue;
            }
            int v = ni*m + nj;
            ans.push_back(v);
        }
        return ans;
    }
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        n = grid.size();
        m = grid[0].size();
        nm = n*m;
        int nHits = hits.size();
        vector<int> hitTime(nm, -1);
        for (int u = 0; u < m; u++) {
            if (grid[0][u] == 0) {
                continue;
            }
            hitTime[u] = nHits;
        }
        for (int t = 0; t < nHits; t++) {
            int i = hits[t][0], j = hits[t][1];
            if (grid[i][j] == 0) {
                continue;
            }
            int u = i*m + j;
            hitTime[u] = t;
        }

        vector<vector<int>> toVisit(nHits+1), candidates(nHits+1);
        for (int u = 0; u < nm; u++) {
            if (hitTime[u] != -1) {
                candidates[hitTime[u]].push_back(u);
            }
        }

        for (int t = nHits; t >= 0; t--) {
            for (int ut = 0; ut < (int)candidates[t].size(); ut++) {
                int u = candidates[t][ut];
                int i = u/m, j = u%m;

                bool hasStableNeighbor = false;
                if (i == 0) {
                    hasStableNeighbor = true;
                }
                vector<int> neighbors = getNeighbors(u);
                for (int v : neighbors) {
                    int ni = v/m, nj = v%m;
                    if (hitTime[v] < t) {
                        continue;
                    }
                    hasStableNeighbor = true;
                }
                // No stable neighbor at time t, this block falls before t.
                if (!hasStableNeighbor) {
                    hitTime[u] = -1;
                    continue;
                }
                toVisit[t].push_back(u);
            }

            for (int ut = 0; ut < (int)toVisit[t].size(); ut++) {
                int u = toVisit[t][ut];
                int i = u/m, j = u%m;

                vector<int> neighbors = getNeighbors(u);
                for (int v : neighbors) {
                    int ni = v/m, nj = v%m;
                    if (hitTime[v] != -1 || grid[ni][nj] == 0) {
                        continue;
                    }
                    hitTime[v] = t;
                    toVisit[t].push_back(v);
                }
            }
        }

        vector<int> ans(nHits);
        for (int t = 0; t < nHits; t++) {
            ans[t] = max(0, ((int)toVisit[t].size())-1);
        }
        return ans;
    }
};
