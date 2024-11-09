class Solution {
private:
    int di[4] = {1, 0, -1, 0};
    int dj[4] = {0, 1, 0, -1};
    vector<vector<int>> discoverIslands(vector<vector<int>>& grid, int& nIslands) {
        int n = grid.size(), m = grid[0].size();

        vector<int> qi(n*m), qj(n*m);
        int sti = 0, eni = 0, stj = 0, enj = 0;

        vector<vector<int>> island(n, vector<int>(m, 0));
        nIslands = 0;
        
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0 || island[i][j] > 0) {
                continue;
            }
            island[i][j] = ++nIslands;

            qi[eni++] = i;
            qj[enj++] = j;
            while (sti < eni && stj < enj) {
                int i = qi[sti++];
                int j = qj[stj++];
                for (int k = 0; k < 4; k++) {
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                        continue;
                    }
                    if (grid[ni][nj] != 0 && island[ni][nj] == 0) {
                        island[ni][nj] = island[i][j];
                        qi[eni++] = ni;
                        qj[enj++] = nj;
                    }
                }
            }
        }
        return island;
    }
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int nIslands1, nIslands2;
        vector<vector<int>> island1 = discoverIslands(grid1, nIslands1);
        vector<vector<int>> island2 = discoverIslands(grid2, nIslands2);

        int n = grid1.size(), m = grid1[0].size();
        vector<int> mapping(nIslands2+1, 0);
        vector<bool> isSubIsland(nIslands2+1, true);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
            int u = island1[i][j];
            int v = island2[i][j];
            if (v == 0) {
                continue;
            }
            if (u == 0) {
                isSubIsland[v] = false;
            } else if (mapping[v] == 0) {
                mapping[v] = u;
            } else if (mapping[v] != u) {
                isSubIsland[v] = false;
            }
        }

        int ans = 0;
        for (int v = 1; v <= nIslands2; v++) {
            if (isSubIsland[v]) {
                ans++;
            }
        }
        return ans;
    }
};
