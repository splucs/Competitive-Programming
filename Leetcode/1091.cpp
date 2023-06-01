class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if (grid[0][0] == 1) {
            return -1;
        }

        int n = grid.size();
        int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
        int dy[8] = {1, 1, 1, 0, -1, -1, -1, 0};

        // Init bfs
        queue<int> qx, qy;
        vector<vector<int> > dist(n, vector<int>(n, -1));
        qx.push(0);
        qy.push(0);
        dist[0][0] = 1;

        // Run bfs
        while(!qx.empty()) {
            int x = qx.front(); qx.pop();
            int y = qy.front(); qy.pop();
            for (int k = 0; k < 8; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx < 0 || ny < 0 || nx >= n || ny >= n) {
                    continue;
                }
                if (dist[nx][ny] != -1 || grid[nx][ny] == 1) {
                    continue;
                }

                dist[nx][ny] = dist[x][y] + 1;
                qx.push(nx);
                qy.push(ny);
            }
        }
        return dist[n-1][n-1];
    }
};
