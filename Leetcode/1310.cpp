class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            arr[i] ^= arr[i-1];
        }
        int q = queries.size();
        vector<int> ans(q);
        for (int i = 0; i < q; i++) {
            int l = queries[i][0], r = queries[i][1];
            ans[i] = arr[r]^(l > 0 ? arr[l-1] : 0);
        }
        return ans;
    }
};
