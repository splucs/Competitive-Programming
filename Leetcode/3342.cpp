#define INF 0x3f3f3f3f

class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size(), m = moveTime[0].size();
        set<pair<int, int>> pq;
        vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(2, INF)));
        dist[0][0][0] = 0;
        pq.insert(make_pair(dist[0][0][0], 0));
        while(!pq.empty()) {
            auto it = pq.begin();
            int w = it->first, c = it->second;
            int b = c%2, i = (c/2)%n, j = c/(2*n);
            pq.erase(it);
            for (int dir = 0; dir < 4; dir++) {
                int ni = i + di[dir];
                int nj = j + dj[dir];
                if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                    continue;
                }
                int nb = 1 - b;
                int nc = nj*n*2 + ni*2 + nb;
                int nw = max(dist[i][j][b], moveTime[ni][nj]) + (b == 0 ? 1 : 2);
                if (nw < dist[ni][nj][nb]) {
                    pq.erase(make_pair(dist[ni][nj][nb], nc));
                    dist[ni][nj][nb] = nw;
                    pq.insert(make_pair(dist[ni][nj][nb], nc));
                }
            }
        }
        return min(dist[n-1][m-1][0], dist[n-1][m-1][1]);
    }
};
