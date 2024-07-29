class Solution {
private:
    vector<int> mapping;
    int doMapping(int x) {
        if (x == 0) {
            return mapping[0];
        }
        int y = 0;
        for (int p = 1; x; x /= 10, p *= 10) {
            y += mapping[x%10] * p;
        }
        return y;
    }
public:
    vector<int> sortJumbled(vector<int>& _mapping, vector<int>& nums) {
        mapping.swap(_mapping);
        sort(nums.begin(), nums.end(), [=](int i, int j) {
            return doMapping(i) < doMapping(j);
        });
        return nums;
    }
};
