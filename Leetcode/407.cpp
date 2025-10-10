class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int n = heightMap.size(), m = heightMap[0].size();
        vector<vector<int>> q;
        vector<bool> inq(n*m, false);
        for (int i = 0; i < n; i++) {
            int dj = (i == 0 || i == n-1 || m == 1) ? 1 : m-1;
            for (int j = 0; j < m; j+=dj) {
                int u = i*m + j;
                int h = heightMap[i][j];
                if (q.size() <= h) {
                    q.resize(2*h);
                }
                q[h].push_back(u);
                inq[u] = true;
            }
        }

        int ans = 0;
        int di[4] = {0, -1, 0, 1};
        int dj[4] = {-1, 0, 1, 0};
        for (int h = 0; h < (int)q.size(); h++) {
            for (int ut = 0; ut < (int)q[h].size(); ut++) {
                int u = q[h][ut];
                int i = u/m, j = u%m;
                ans += h - heightMap[i][j];
                for (int dir = 0; dir < 4; dir++) {
                    int ni = i + di[dir];
                    int nj = j + dj[dir];
                    if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                        continue;
                    }
                    int nu = ni*m + nj;
                    if (inq[nu]) continue;
                    int nh = max(h, heightMap[ni][nj]);
                    if (q.size() <= nh) {
                        q.resize(2*nh);
                    }
                    q[nh].push_back(nu);
                    inq[nu] = true;
                }
            }
        }
        return ans;
    }
};
