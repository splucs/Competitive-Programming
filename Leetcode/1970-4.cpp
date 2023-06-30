class Solution {
private:
    int di[4] = {-1, 0, 0, 1};
    int dj[4] = {0, -1, 1, 0};
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        vector<vector<bool>> viz(row, vector<bool>(col, false));
        vector<vector<int>> maxDay(row, vector<int>(col));
        vector<vector<int>> qi(row*col), qj(row*col);

        // maxDay[i][j] = maximum day where (i,j) can be reached.
        // Starts with the day before it floods.
        for (int d = 0; d < (int)cells.size(); d++) {
            int i = cells[d][0]-1;
            int j = cells[d][1]-1;
            maxDay[i][j] = d;
        }

        // Start processing back row.
        for (int j = 0; j < col; j++) {
            int d = maxDay[0][j];
            viz[0][j] = true;
            qi[d].push_back(0);
            qj[d].push_back(j);
        }

        // Modified dijkstra that uses bucket sort to process graph in linear time.
        for (int d = row*col-1; d >= 0; d--) {
            while(!qi[d].empty()) {
                int i = qi[d].back(); qi[d].pop_back();
                int j = qj[d].back(); qj[d].pop_back();
                int d = maxDay[i][j];
                if (i+1 == row) {
                    return d;
                }

                for (int dir = 0; dir < 4; dir++) {
                    int ni = i + di[dir];
                    int nj = j + dj[dir];
                    if (ni < 0 || ni >= row || nj < 0 || nj >= col) continue;

                    if (viz[ni][nj]) continue;

                    int &nd = maxDay[ni][nj];
                    if (nd > d) {
                        nd = d;
                    }
                    viz[ni][nj] = true;
                    qi[nd].push_back(ni);
                    qj[nd].push_back(nj);
                }
            }
        }
        return -1;
    }
};

