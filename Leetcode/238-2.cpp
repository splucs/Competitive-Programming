class Solution {
private:
    vector<int> nums;
    void dc(int l, int r, int prod) {
        if (l == r) {
            nums[l] = prod;
            return;
        }
        int mid = (l+r)>>1;
        int prodLeft = prod;
        for (int i = l; i <= mid; i++) {
            prodLeft *= nums[i];
        }
        int prodRight = prod;
        for (int i = mid+1; i <= r; i++) {
            prodRight *= nums[i];
        }
        dc(l, mid, prodRight);
        dc(mid+1, r, prodLeft);
    }
public:
    vector<int> productExceptSelf(vector<int>& _nums) {
        nums.swap(_nums);
        dc(0, nums.size()-1, 1);
        return nums;
    }
};
