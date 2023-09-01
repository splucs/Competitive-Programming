class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n+1, 0);
        for (int j = 1, zeroesRight = 0; j <= n; j <<= 1, zeroesRight++) {
            for (int i = j, di = j<<1; i <= n; i += di) {
                ans[i] -= zeroesRight;
            }
        }
        for (int i = 1; i <= n; i++) {
            ans[i] += ans[i-1]+1;
        }
        return ans;
    }
};
