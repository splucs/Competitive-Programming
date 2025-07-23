#define INF 0x3f3f3f3f

class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int n = isWater.size(), m = isWater[0].size();
        vector<vector<int>> height(n, vector<int>(m, INF));
        vector<int> qi, qj;
        qi.reserve(n*m), qj.reserve(n*m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (isWater[i][j]) {
                    height[i][j] = 0;
                    qi.push_back(i);
                    qj.push_back(j);
                }
            }
        }

        for (int t = 0; t < (int)qi.size(); t++) {
            int i = qi[t], j = qj[t];
            for (int dir = 0; dir < 4; dir++) {
                int ni = i + di[dir], nj = j + dj[dir];
                if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                    continue;
                }
                if (height[ni][nj] < INF) {
                    continue;
                }
                height[ni][nj] = 1 + height[i][j];
                qi.push_back(ni);
                qj.push_back(nj);
            }
        }
        return height;
    }
};
