class Solution {
private:
    inline int abs(int x) {
        return x < 0 ? -x : x;
    }
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> piles;
        int n = grid.size(), m = grid[0].size();
        int rem = grid[0][0]%x, tot = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j]%x != rem) {
                    return -1;
                }
                piles.push_back(grid[i][j]/x);
            }
        }

        sort(piles.begin(), piles.end());
        int target = piles[piles.size()/2];

        int ans = 0;
        for (int pile : piles) {
            ans += abs(pile - target);
        }
        return ans;
    }
};
