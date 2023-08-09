typedef pair<int, int> ii;
typedef pair<int, ii> iii;

class Solution {
private:
    vector<int> diff;
public:
    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        diff.resize(n-1);
        for (int i = 0; i < n-1; i++) {
            diff[i] = nums[i+1]-nums[i];
        }
        int lo = -1, hi = nums[n-1]-nums[0];
        while (hi > lo+1) {
            int mid = (hi+lo)>>1;
            if (maxPairsUpTo(mid) >= p) hi = mid;
            else lo = mid;
        }
        return hi;
    }
    int maxPairsUpTo(int k) {
        int n = diff.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (diff[i] <= k) {
                ans++;
                i++;
            }
        }
        return ans;
    }
};
