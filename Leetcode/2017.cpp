#define INF 0x3f3f3f3f3f3f3f
class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        int n = grid[0].size();
        long long top = 0, bot = 0;
        for (int i = 0; i < n; i++) {
            top += grid[0][i];
        }
        long long ans = INF;
        for (int i = 0; i < n; i++) {
            top -= grid[0][i];
            ans = min(ans, max(top, bot));
            bot += grid[1][i];
        }
        return ans;
    }
};
