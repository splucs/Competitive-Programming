#define MOD 1000000007
class Solution {
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<long long> powers;
        for(int p = 1; n > 0; n >>= 1, p <<= 1) {
            if (n & 1) {
                powers.push_back(p);
            }
        }
        vector<int> ans(queries.size());
        for (int q = 0; q < (int)queries.size(); q++) {
            int l = queries[q][0];
            int r = queries[q][1];
            ans[q] = 1;
            for (int i = l; i <= r; i++) {
                ans[q] = (ans[q] * powers[i]) % MOD;
            }
        }
        return ans;
    }
};
