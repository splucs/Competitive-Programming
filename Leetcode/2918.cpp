class Solution {
private:
    long long minimumSum(vector<int>& nums) {
        long long sum = 0; 
        for (int num : nums) {
            if (num == 0) {
                sum++;
            } else {
                sum += num;
            }
        }
        return sum;
    }
    bool hasZero(vector<int>& nums) {
        for (int num : nums) {
            if (num == 0) {
                return true;
            }
        }
        return false;
    }
public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        long long sum1 = minimumSum(nums1), sum2 = minimumSum(nums2);
        bool hasZero1 = hasZero(nums1), hasZero2 = hasZero(nums2);
        if (sum1 < sum2 && !hasZero1) {
            return -1;
        }
        if (sum2 < sum1 && !hasZero2) {
            return -1;
        }
        return max(sum1, sum2);
    }
};
