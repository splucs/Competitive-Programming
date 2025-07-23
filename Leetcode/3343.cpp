#define MOD 1000000007
class Solution {
private:
    vector<vector<int>> pascal;
    void buildPascal(int n) {
        pascal.assign(n+1, vector<int>(n+1, 0));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    pascal[i][j] = 1;
                } else {
                    pascal[i][j] = (pascal[i-1][j] + pascal[i-1][j-1]) % MOD;
                }
            }
        }
    }
public:
    int countBalancedPermutations(string num) {
        // dp[d][sumLeft][picksLeft] = number of permutations where sum of even idx is at sumLeft and I still need to pick picksLeft for even idx
        vector<int> freq(10, 0), partialSum(11);

        int totSum = 0;
        for (char c : num) {
            freq[c-'0']++;
            totSum += c-'0';
        }
        if (totSum & 1) {
            return 0;
        }
        int sum = totSum/2;

        partialSum[10] = 0;
        for (int d = 9; d >= 0; d--) {
            partialSum[d] = freq[d] + partialSum[d+1];
        }

        int n = num.size();
        buildPascal(n);

        vector<vector<vector<int>>> dp(11, vector<vector<int>>(sum+1, vector<int>(n/2+1, 0)));
        dp[10][0][0] = 1;
        for (int d = 9; d >= 0; d--) {
            for (int sumLeft = 0; sumLeft <= sum; sumLeft++) {
                for (int picksLeft = min(n/2, partialSum[d]); picksLeft >= 0; picksLeft--) {
                    int &ans = dp[d][sumLeft][picksLeft];
                    for (int picks = max(0, picksLeft - partialSum[d+1]); picks <= freq[d] && picks <= picksLeft && d*picks <= sumLeft; picks++) {
                        int rec = dp[d+1][sumLeft-d*picks][picksLeft-picks];
                        int pickedRecSize = picksLeft - picks;
                        int unpickedRecSize = partialSum[d+1] - pickedRecSize;
                        rec = (pascal[pickedRecSize + picks][pickedRecSize] * (long long) rec) % MOD;
                        rec = (pascal[unpickedRecSize + freq[d] - picks][unpickedRecSize] * (long long) rec) % MOD;
                        ans = (ans + rec) % MOD;
                    }
                }
            }
        }
        return dp[0][sum][n/2];
    }
};
