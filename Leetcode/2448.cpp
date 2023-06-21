class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& cost) {
        int n = nums.size();

        // Calculate the slope of the cost graph "f(x) = cost to make everything equal to x" at minus infinity
        long long slope = 0;
        for (int i = 0; i < n; i++) {
            slope -= cost[i];
        }

        // Calculate an array of indexes sorted by nums
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return nums[i] < nums[j];
        });
        
        // Iterate over all points in increasing order of nums
        // Find the point where the slope changes direction
        int target = 0;
        for (int it = 0; it < n; it++) {
            int i = idx[it];
            long long newSlope = slope + 2*cost[i];
            if (slope < 0 && newSlope >= 0) {
                target = nums[i];
                break;
            }
            slope = newSlope;
        }

        // Calculate answer by making all points equal to target
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long d = nums[i] - target;
            if (d < 0) d = -d;
            ans += cost[i]*d;
        }
        return ans;
    }
};
