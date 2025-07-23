#define INF 0x3f3f3f3f

class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size(), m = moveTime[0].size();
        set<pair<int, pair<int, int>>> pq;
        vector<vector<int>> dist(n, vector<int>(m, INF));
        dist[0][0] = 0;
        pq.insert(make_pair(dist[0][0], make_pair(0, 0)));
        while(!pq.empty()) {
            auto it = pq.begin();
            int w = it->first, i = it->second.first, j = it->second.second;
            pq.erase(it);
            for (int dir = 0; dir < 4; dir++) {
                int ni = i + di[dir];
                int nj = j + dj[dir];
                if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                    continue;
                }
                int nw = max(dist[i][j], moveTime[ni][nj]) + 1;
                if (nw < dist[ni][nj]) {
                    pq.erase(make_pair(dist[ni][nj], make_pair(ni, nj)));
                    dist[ni][nj] = nw;
                    pq.insert(make_pair(dist[ni][nj], make_pair(ni, nj)));
                }
            }
        }
        return dist[n-1][m-1];
    }
};
