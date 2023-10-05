class Solution {
private:
    void quicksort(vector<int>& nums, int lo, int hi, int threshold, vector<int>& ans) {
        if (hi-lo <= threshold) {
            return;
        }
        int pivot = nums[lo + rand()%(hi-lo)];
        int leq = lo, ge = lo;
        for (int i = lo; i < hi; i++) {
            if (nums[i] == pivot) {
                swap(nums[i], nums[ge++]);
            } else if (nums[i] < pivot) {
                swap(nums[i], nums[ge]);
                swap(nums[ge++], nums[leq++]);
            }
        }
        if (ge - leq > threshold) {
            ans.push_back(pivot);
        }
        quicksort(nums, lo, leq, threshold, ans);
        quicksort(nums, ge, hi, threshold, ans);
    }
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
        quicksort(nums, 0, n, n/3, ans);
        return ans;
    }
};
