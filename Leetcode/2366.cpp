class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        int n = nums.size();
        int last = 1e9;
        long long ans = 0;
        for (int i = n-1; i >= 0; i--) {
            int x = nums[i];
            if (x <= last) {
                last = x;
                continue;
            }

            int parts = (x+last-1)/last;
            ans += parts-1;
            last = x/parts;
        }
        return ans;
    }
};
