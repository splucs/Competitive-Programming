class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
    vector<vector<int>> island, grid;
    vector<int> islandSize;
    int n, m;

    void explore(int i, int j) {
        islandSize[island[i][j]]++;
        for (int dir = 0; dir < 4; dir++) {
            int ni = i + di[dir];
            int nj = j + dj[dir];
            if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                continue;
            }
            if (grid[ni][nj] == 0 || island[ni][nj] != 0) {
                continue;
            }
            island[ni][nj] = island[i][j];
            explore(ni, nj);
        }
    }
public:
    int largestIsland(vector<vector<int>>& _grid) {
        grid.swap(_grid);
        n = grid.size(), m = grid[0].size();
        island.assign(n, vector<int>(m, 0));
        islandSize.assign(1, 0);

        int nIslands = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && island[i][j] == 0) {
                    island[i][j] = ++nIslands;
                    islandSize.push_back(0);
                    explore(i, j);
                    ans = max(ans, islandSize[nIslands]);
                }
            }
        }

        vector<bool> alreadySeenNeighbor(nIslands+1, false);
        vector<int> neighbors;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 0) {
                    continue;
                }
                for (int dir = 0; dir < 4; dir++) {
                    int ni = i + di[dir];
                    int nj = j + dj[dir];
                    if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                        continue;
                    }
                    if (grid[ni][nj] == 0) {
                        continue;
                    }
                    neighbors.push_back(island[ni][nj]);
                }
                int curAns = 1;
                for (int neighbor : neighbors) {
                    if (alreadySeenNeighbor[neighbor]) {
                        continue;
                    }
                    alreadySeenNeighbor[neighbor] = true;
                    curAns += islandSize[neighbor];
                }
                ans = max(ans, curAns);
                for (int neighbor : neighbors) {
                    alreadySeenNeighbor[neighbor] = false;
                }
                neighbors.clear();
            }
        }
        return ans;
    }
};
