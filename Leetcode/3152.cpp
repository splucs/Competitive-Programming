class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> adj(n-1);
        for (int i = 0; i < n-1; i++) {
            adj[i] = (nums[i]&1) == (nums[i+1]&1) ? 1 : 0;
        }
        for (int i = 1; i < n-1; i++) {
            adj[i] += adj[i-1];
        }
        vector<bool> ans;
        for (const vector<int>& q : queries) {
            int i = q[0], j = q[1]-1;
            if (j >= i) {
                int sum = adj[j];
                if (i > 0) sum -= adj[i-1];
                ans.push_back(sum == 0);
            } else {
                ans.push_back(true);
            }
        }
        return ans;
    }
};
