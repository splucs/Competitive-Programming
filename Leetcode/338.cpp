class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n+1);
        ans[0] = 0;
        for (int i = 1; i <= n; i++) {
            int zeroesRight = 0, cur = i;
            while((cur&1) == 0) {
                cur >>= 1;
                zeroesRight++;
            }
            ans[i] = ans[i-1]+1-zeroesRight;
        }
        return ans;
    }
};
