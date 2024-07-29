#define INF 0x3f3f3f3f
class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        int dist[26][26];
        memset(&dist, INF, sizeof dist);

        for (int t = 0; t < (int)cost.size(); t++) {
            int i = original[t]-'a', j = changed[t]-'a', w = cost[t];
            dist[i][j] = min(dist[i][j], w);
        }

        //Floyd-warshall
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        
        long long ans = 0;
        for (int t = 0; t < (int)target.size(); t++) {
            int i = source[t]-'a', j = target[t]-'a';
            if (i == j) {
                continue;
            }
            if (dist[i][j] == INF) {
                return -1;
            }
            ans += dist[i][j];
        }
        return ans;
    }
};
