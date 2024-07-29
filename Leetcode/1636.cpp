class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        int n = nums.size();
        vector<int> idx(n);
        vector<int> freq(201, 0);;
        for (int i = 0; i < n; i++) {
            idx[i] = i;
            freq[nums[i]+100]++;
        }

        sort(idx.begin(), idx.end(), [=](int i, int j) {
            int fi = freq[nums[i]+100];
            int fj = freq[nums[j]+100];
            if (fi != fj) {
                return fi < fj;
            }
            return nums[i] > nums[j];
        });

        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = nums[idx[i]];
        }
        return ans;
    }
};
