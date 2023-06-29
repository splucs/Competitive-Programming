class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        const int INF = 1e7;
        int di[4] = {0, 1, 0, -1};
        int dj[4] = {1, 0, -1, 0};

        int n = grid.size();
        int m = grid[0].size();
        int numKeys = countKeys(grid);

        // Set up dist table
        vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(1<<numKeys, INF)));

        // Set up bfs
        queue<int> qi, qj, qmask;
        pair<int, int> start = findStart(grid);
        qi.push(start.first);
        qj.push(start.second);
        qmask.push(0);
        dist[start.first][start.second][0] = 0;

        // Run bfs
        while(!qmask.empty()) {
            int i = qi.front(); qi.pop();
            int j = qj.front(); qj.pop();
            int mask = qmask.front(); qmask.pop();
            char c = grid[i][j];

            // Adjust mask
            int nmask = mask;
            if (c >= 'a' && c <= 'z') {
                nmask |= 1<<(c-'a');
                dist[i][j][nmask] = dist[i][j][mask];
            }

            // Check if we have all keys
            if (nmask+1 == (1<<numKeys)) {
                return dist[i][j][nmask];
            }
    
            for (int dir = 0; dir < 4; dir++) {
                int ni = i + di[dir];
                int nj = j + dj[dir];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                c = grid[ni][nj];

                // If new char is a lock, skip
                if (c == '#') continue;

                // If new char is a lock, check if we can't open it
                if (c >= 'A' && c <= 'Z') {
                    int keyMask = nmask&(1<<(c-'A'));
                    if (!keyMask) continue;
                }

                if (dist[ni][nj][nmask] > dist[i][j][mask]+1) {
                    dist[ni][nj][nmask] = dist[i][j][mask]+1;
                    qi.push(ni);
                    qj.push(nj);
                    qmask.push(nmask);
                }
            }
        }
        return -1;
    }
    int countKeys(vector<string>& grid) {
        int ans = 0;
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char c = grid[i][j];
                if (c >= 'a' && c <= 'z') ans++;
            }
        }
        return ans;
    }
    pair<int, int> findStart(vector<string>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char c = grid[i][j];
                if (c == '@') return make_pair(i, j);
            }
        }
        return make_pair(-1, -1);
    }
};
