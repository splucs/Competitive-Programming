class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> lis;
        for (int num : nums) {
            int lo = -1;            // lis[lo] < num
            int hi = lis.size();    // lis[hi] >= num
            while(hi > lo + 1) {
                int mid = (hi+lo)>>1;
                if (lis[mid] < num) lo = mid;
                else hi = mid;
            }
            if (hi == lis.size()) lis.push_back(num);
            else lis[hi] = num;
        }
        return lis.size();
    }
};
