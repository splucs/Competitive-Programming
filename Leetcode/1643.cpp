class Solution {
public:
    string kthSmallestPath(vector<int>& destination, int k) {
        int x = destination[1], y = destination[0];
        int n = x+y;

        vector<vector<long long>> pascal(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) pascal[i][j] = 1;
                else pascal[i][j] = pascal[i-1][j] + pascal[i-1][j-1];
            }
        }

        vector<char> ans(n);
        for (int i = 0; i < n; i++) {
            if (k <= pascal[x-1+y][y]) {
                x--;
                ans[i] = 'H';
            } else {
                k -= pascal[x-1+y][y];
                y--;
                ans[i] = 'V';
            }
        }

        return string(ans.begin(), ans.end());
    }
};
