#define INF 0x3f3f3f3f3f3f3f3fLL
class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int m = nums.size();
        int n = m/3;
        vector<long long> sumFirst(m-n, INF);

        multiset<int> choices;
        long long curSum = 0, ans = INF;
        for (int i = 0; i < m-n; i++) {
            curSum += nums[i];
            choices.insert(nums[i]);
            if (choices.size() > n) {
                int val = *choices.rbegin();
                curSum -= val;
                choices.erase(choices.find(val));
            }
            if (choices.size() == n) {
                sumFirst[i] = curSum;
            }
        }

        choices.clear();
        curSum = 0;
        for (int i = m-1; i >= n; i--) {
            curSum += nums[i];
            choices.insert(nums[i]);
            if (choices.size() > n) {
                int val = *choices.begin();
                curSum -= val;
                choices.erase(choices.find(val));
            }
            if (choices.size() == n) {
                ans = min(ans, sumFirst[i-1]-curSum);
            }
        }
        return ans;
    }
};
