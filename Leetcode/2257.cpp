class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<vector<bool>>> guarded(4, vector<vector<bool>>(m, vector<bool>(n, false)));
        for (vector<int>& guard : guards) {
            int j = guard[0], i = guard[1];
            for (int dir = 0; dir < 4; dir++) {
                guarded[dir][j][i] = true;
            }
        }

        vector<vector<bool>> walled(m, vector<bool>(n, false));
        for (vector<int>& wall : walls) {
            int j = wall[0], i = wall[1];
            walled[j][i] = true;
        }

        for (int dir = 0; dir < 4; dir++) {
            for (vector<int>& guard : guards) {
                int j = guard[0]+dj[dir], i = guard[1]+di[dir];
                for (; i >= 0 && j >= 0 && i < n && j < m && !guarded[dir][j][i] && !walled[j][i]; i += di[dir], j += dj[dir]) {
                    guarded[dir][j][i] = true;
                }
            }
        }

        int ans = 0;
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                if (walled[j][i]) {
                    continue;
                }
                bool guardedSomeDir = false;
                for (int dir = 0; dir < 4; dir++) {
                    if (guarded[dir][j][i]) {
                        guardedSomeDir = true;
                        break;
                    }
                }
                if (!guardedSomeDir) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
