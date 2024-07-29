#define INF 0x3f3f3f3f
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dist(n, vector<int>(n, INF));

        for (vector<int> &edge : edges) {
            int i = edge[0];
            int j = edge[1];
            int w = edge[2];
            dist[i][j] = dist[j][i] = w;
        }

        // Floyd-warshall
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        int minAns = n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int cur = 0;
            for (int j = 0; j < n; j++) {
                if (i != j && dist[i][j] <= distanceThreshold) {
                    cur++;
                }
            }
            if (cur <= minAns) {
                minAns = cur;
                ans = i;
            }
        }
        return ans;
    }
};
