#define MOD 1000000007
#define MAXP 20
class Solution {
private:
    vector<vector<int>> multiples;
    void computeMultiples(int maxValue) {
        multiples.resize(maxValue+1);
        for (int i = 1; i <= maxValue; i++) {
            for (int j = i+i; j <= maxValue; j += i) {
                multiples[i].push_back(j);
            }
        }
    }

    vector<int> ansByPathLen;
    void computeAnsByPathSize(int n) {
        // ansByPathLen[len] == pascal(n-1, len-1);
        vector<vector<int>> pascal(2, vector<int>(MAXP, 0));
        for (int i = 0; i <= n; i++) {
            int ri = i&1;
            for (int j = 0; j <= i && j < MAXP; j++) {
                if (j == 0 || j == i) {
                    pascal[ri][j] = 1;
                } else {
                    pascal[ri][j] = (pascal[ri^1][j] + pascal[ri^1][j-1]) % MOD;
                }
            }
        }
        ansByPathLen.assign(MAXP, 0);
        for (int len = 1; len < MAXP; len++) {
            ansByPathLen[len] = pascal[(n-1)&1][len-1];
        }
    }

    int computePaths(int maxValue) {
        vector<vector<int>> dp(maxValue+1, vector<int>(MAXP, 0));
        int ans = 0;
        for (int i = maxValue; i > 0; i--) {
            for (int len = 1; len+1 < MAXP; len++) {
                dp[i][len] = ansByPathLen[len];
                for (int j : multiples[i]) {
                    dp[i][len] = (dp[i][len] + dp[j][len+1]) % MOD;
                }
            }
            ans = (ans + dp[i][1]) % MOD;
        }
        return ans;
    }
public:
    int idealArrays(int n, int maxValue) {
        computeMultiples(maxValue);
        computeAnsByPathSize(n);
        return computePaths(maxValue);
    }
};
