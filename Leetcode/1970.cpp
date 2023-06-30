class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int lo = 0;
        int hi = row*col;
        while(hi > lo+1) {
            int mid = (hi+lo)/2;
            if (canCrossAtDay(mid, row, col, cells)) lo = mid;
            else hi = mid;
        }
        return lo;
    }
    bool canCrossAtDay(int day, int row, int col, vector<vector<int>>& cells) {
        vector<vector<int>> viz(row, vector<int>(col, 0));
        for (int d = 0; d < day; d++) {
            int i = cells[d][0]-1;
            int j = cells[d][1]-1;
            viz[i][j] = -1;
        }
        
        // Init dfs
        int di[4] = {-1, 0, 0, 1};
        int dj[4] = {0, -1, 1, 0};
        stack<int> qi, qj;
        for (int j = 0; j < col; j++) {
            if (viz[0][j] == 0) {
                qi.push(0);
                qj.push(j);
                viz[0][j] = 1;
            }
        }

        // Run dfs
        while (!qi.empty()) {
            int i = qi.top(); qi.pop();
            int j = qj.top(); qj.pop();
            if (i+1 == row) {
                return true;
            }
            for (int dir = 0; dir < 4; dir++) {
                int ni = i + di[dir];
                int nj = j + dj[dir];
                if (ni < 0 || ni >= row || nj < 0 || nj >= col) continue;

                if (viz[ni][nj] != 0) {
                    continue;
                }
                viz[ni][nj] = 1;
                qi.push(ni);
                qj.push(nj);
            }
        }

        return false;
    }
};

