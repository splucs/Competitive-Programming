class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        vector<int> cnt(60, 0);
        int ans = 0, rem;
        for (int t : time) {
            rem = t%60;
            ans += cnt[(60 - rem) % 60];
            cnt[rem]++;
        }
        return ans;
    }
};
