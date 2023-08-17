struct cell {
    int i;
    int j;
    cell(int _i, int _j) : i(_i), j(_j) {}
};

class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        
        vector<cell> q;
        q.reserve(n*m);

        vector<vector<int>> dist(n, vector<int>(m, -1));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
                q.push_back(cell(i, j));
                dist[i][j] = 0;
            }
        }

        for (int ci = 0; ci < (int)q.size(); ci++) {
            cell c = q[ci];
            for (int d = 0; d < 4; d++) {
                int ni = c.i + di[d];
                int nj = c.j + dj[d];

                if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                if (dist[ni][nj] != -1) continue;

                dist[ni][nj] = 1 + dist[c.i][c.j];
                q.push_back(cell(ni, nj));
            }
        }

        return dist;
    }
};
