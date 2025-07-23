class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        int n = nums.size();
        int maxElem = *max_element(nums.begin(), nums.end());
        vector<int> totalFreq(maxElem+1, 0);
        int totalUnique = 0;
        for (int num : nums) {
            if (totalFreq[num] == 0) {
                totalUnique++;
            }
            totalFreq[num]++;
        }

        vector<int> windowFreq(maxElem+1, 0);
        int windowUnique = 0;
        int ans = 0;
        bool started = false;
        for (int i = 0, j = 0; j < n; j++) {
            if (windowFreq[nums[j]] == 0) {
                windowUnique++;
            }
            windowFreq[nums[j]]++;

            for (; windowUnique == totalUnique; i++) {
                started = true;
                if (windowFreq[nums[i]] == 1) {
                    windowUnique--;
                }
                windowFreq[nums[i]]--;
            }

            if (started) {
                ans += i;
            }
        }
        return ans;
    }
};
