class Solution {
private:
    int di[4] = {1, 0, 0, -1};
    int dj[4] = {0, 1, -1, 0};
    vector<vector<int>> viz;
    int n, m;
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        n = row;
        m = col;
        int lo = 0;
        int hi = row*col;
        while(hi > lo+1) {
            int mid = (hi+lo)/2;
            if (canCrossAtDay(mid, cells)) lo = mid;
            else hi = mid;
        }
        return lo;
    }
    bool canCrossAtDay(int day, vector<vector<int>>& cells) {
        viz = vector<vector<int>>(n, vector<int>(m, 0));
        for (int d = 0; d < day; d++) {
            int i = cells[d][0]-1;
            int j = cells[d][1]-1;
            viz[i][j] = -1;
        }
        
        stack<int> qi, qj;
        for (int j = 0; j < m; j++) {
            if (viz[0][j] == 0 && dfs(0, j)) {
                return true;
            }
        }

        return false;
    }
    bool dfs(int i, int j) {
        viz[i][j] = 1;
        if (i+1 == n) {
            return true;
        }
        for (int dir = 0; dir < 4; dir++) {
            int ni = i + di[dir];
            int nj = j + dj[dir];
            if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;

            if (viz[ni][nj] != 0) {
                continue;
            }
            if (dfs(ni, nj)) {
                return true;
            }
        }
        return false;
    }
};

