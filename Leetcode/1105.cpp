#define INF 0x3f3f3f3f
class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<int> dp(n);
        for (int i = 0; i < n; i++) {
            dp[i] = INF;

            int curHeight = 0, curWidth = 0;
            for (int j = i; j >= 0; j--) {
                curHeight = max(curHeight, books[j][1]);
                curWidth += books[j][0];
                if (curWidth > shelfWidth) {
                    break;
                }
                dp[i] = min(dp[i], curHeight + (j > 0 ? dp[j-1] : 0));
            }
        }
        return dp[n-1];
    }
};
