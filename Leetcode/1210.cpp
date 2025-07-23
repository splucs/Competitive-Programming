#define validate(i, j, di, dj) 

class Solution {
private:
    vector<vector<int>> grid;
    vector<vector<vector<int>>> dist;
    vector<int> qi, qj, qdi;
    void process(int i, int j, int di, int ndist) {
        int dj = 1 - di;
        int n = grid.size();
        if (i < 0 || i >= n || j < 0 || j >= n) {
            return;
        }
        if (i + di < 0 || i + di >= n || j + dj < 0 || j + dj >= n) {
            return;
        }
        if (grid[i][j] == 1 || grid[i+di][j+dj] == 1) {
            return;
        }
        if (dist[i][j][di] != -1) {
            return;
        }
        dist[i][j][di] = ndist;
        qi.push_back(i);
        qj.push_back(j);
        qdi.push_back(di);
    }
public:
    int minimumMoves(vector<vector<int>>& _grid) {
        grid.swap(_grid);
        int n = grid.size();
        dist.assign(n, vector<vector<int>>(n, vector<int>(2, -1)));
        process(0, 0, 0, 0);
        for (int t = 0; t < (int)qi.size(); t++) {
            int i = qi[t], j = qj[t];
            int di = qdi[t];
            int ndist = 1 + dist[i][j][di];
            
            process(i, j+1, di, ndist); // move right
            process(i+1, j, di, ndist); // move down 
            if (i+1 < n && j+1 < n && grid[i+1][j+1] == 0) {
                process(i, j, 1-di, ndist); // rotate
            }
        }
        return dist[n-1][n-2][0];
    }
};
