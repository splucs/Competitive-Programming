class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        int n2 = n*n;
        int u = 0;
        vector<int> snake(n2 + 1);
        for (int i = n-1; i >= 0; i--) {
            for (int jt = 0; jt < n; jt++) {
                int j = ((n-i-1) & 1) == 0 ? jt : n-1-jt;
                u++;
                snake[u] = board[i][j] == -1 ? u : board[i][j];
            }
        }
        vector<int> q, dist(n2 + 1, -1);;
        q.reserve(n2 + 1);
        q.push_back(1);
        dist[1] = 0;
        for (int t = 0; t < (int)q.size(); t++) {
            int u = q[t];
            for (int vt = u+1; vt <= u+6 && vt <= n2; vt++) {
                int v = snake[vt];
                if (dist[v] == -1) {
                    dist[v] = 1 + dist[u];
                    q.push_back(v);
                }
            }
        }
        return dist[n2];
    }
};
