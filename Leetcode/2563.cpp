class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        multiset<int> s;
        long long ans = 0;
        for (int num : nums) {
            ans += distance(s.lower_bound(lower-num), s.upper_bound(upper-num));
            s.insert(num);
        }
        return ans;
    }
};
