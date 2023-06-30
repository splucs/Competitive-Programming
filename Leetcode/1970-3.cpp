typedef pair<int, int> pii;
typedef pair<int, pii> piii;

class Solution {
private:
    int di[4] = {1, 0, 0, -1};
    int dj[4] = {0, 1, -1, 0};
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        // maxDay[i][j] = maximum day where cell (i,j) is reachable
        vector<vector<int>> maxDay(row, vector<int>(col));
        for (int d = 0; d < (int)cells.size(); d++) {
            int i = cells[d][0]-1;
            int j = cells[d][1]-1;
            maxDay[i][j] = d;
        }

        vector<vector<bool>> viz(row, vector<bool>(col));
        set<piii> s;
        for (int j = 0; j < col; j++) {
            s.insert(piii(maxDay[0][j], pii(0, j)));
        }

        while(!s.empty()) {
            piii cur = *s.rbegin(); s.erase(cur);
            int d = cur.first;
            int i = cur.second.first;
            int j = cur.second.second;
            viz[i][j] = true;
            if (i+1 == row) {
                return d;
            }

            for (int dir = 0; dir < 4; dir++) {
                int ni = i + di[dir];
                int nj = j + dj[dir];
                if (ni < 0 || ni >= row || nj < 0 || nj >= col) continue;

                if (viz[ni][nj]) continue;

                piii nxt(maxDay[ni][nj], pii(ni, nj));
                if (maxDay[ni][nj] > d) {
                    if (s.count(nxt)) s.erase(nxt);
                    nxt.first = maxDay[ni][nj] = d;
                }
                s.insert(nxt);
            }
        }
        return -1;
    }
};


