#define INF 0x3f3f3f3f

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == i) {
                    triangle[i][j] += triangle[i-1][j-1];
                } else if (j == 0) {
                    triangle[i][j] += triangle[i-1][j];
                } else {
                    triangle[i][j] += min(triangle[i-1][j-1], triangle[i-1][j]);
                }
            }
        }
        int ans = INF;
        for (int j = 0; j < n; j++) {
            ans = min(ans, triangle[n-1][j]);
        }
        return ans;
    }
};
