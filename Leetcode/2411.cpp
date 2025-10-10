#define MAX_BITS 32
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        vector<int> bit(MAX_BITS, 0);
        for (int i = n-1, j = n-1; i >= 0; i--) {
            for (int num = nums[i], t = 0; num > 0; num >>= 1, t++) {
                if ((num & 1) == 0) {
                    continue;
                }
                bit[t]++;
            }
            for (; i < j; j--) {
                bool canRemove = true;
                for (int num = nums[j], t = 0; num > 0; num >>= 1, t++) {
                    if ((num & 1) == 0) {
                        continue;
                    }
                    if (bit[t] == 1) {
                        canRemove = false;
                        break;
                    }
                }
                if (!canRemove) {
                    break;
                }
                for (int num = nums[j], t = 0; num > 0; num >>= 1, t++) {
                    if ((num & 1) == 0) {
                        continue;
                    }
                    bit[t]--;
                }
            }
            ans[i] = j-i+1;
        }
        return ans;
    }
};
