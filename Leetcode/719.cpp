class Solution {
private:
    vector<int> nums;
    int numberOfPairsBelow(int d) {
        int ans = 0;
        for(int i = 0, j = 0; j < (int)nums.size(); j++) {
            while(nums[j] - nums[i] > d) {
                i++;
            }
            ans += j-i;
        }
        return ans;
    }
public:
    int smallestDistancePair(vector<int>& _nums, int k) {
        nums.swap(_nums);
        sort(nums.begin(), nums.end());
        int lo = -1;
        int hi = *nums.rbegin() - *nums.begin() + 1;
        while (hi > lo + 1) {
            int mid = (hi + lo) >> 1;
            if (numberOfPairsBelow(mid) >= k) hi = mid;
            else lo = mid;
        }
        return hi;
    }
};
