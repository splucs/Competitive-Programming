#define INF 0x3f3f3f3f
class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int maxNum = -INF;
        int minNum = INF;
        for (int num : nums) {
            maxNum = max(maxNum, num);
            minNum = min(minNum, num);
        }

        int m = l.size();
        vector<bool> ans(m, true);
        vector<bool> seen(maxNum-minNum+1, false);
        for(int i = 0; i < m; i++) {
            int maxRange = -INF;
            int minRange = INF;
            for (int j = l[i]; j <= r[i]; j++) {
                maxRange = max(maxRange, nums[j]);
                minRange = min(minRange, nums[j]);
                seen[nums[j]-minNum] = true;
            }

            int deltaNum = maxRange-minRange;
            int deltaIdx = r[i]-l[i];
            if (deltaNum%deltaIdx != 0) {
                ans[i] = false;
            } else if (deltaNum == 0) {
                ans[i] = true;
            } else {
                int ratio = deltaNum/deltaIdx;
                for (int num = minRange; num <= maxRange; num += ratio) {
                    if(!seen[num-minNum]) {
                        ans[i] = false;
                        break;
                    }
                }
            }

            for (int j = l[i]; j <= r[i]; j++) {
                seen[nums[j]-minNum] = false;
            }
        }
        
        return ans;
    }
};
