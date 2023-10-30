class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        vector<vector<int>> buckets(15);
        for (int num : arr) {
            buckets[__builtin_popcount(num)].push_back(num);
        }
        vector<int> ans;
        for (vector<int> &bucket : buckets) {
            sort(bucket.begin(), bucket.end());
            for (int num : bucket) {
                ans.push_back(num);
            }
        }
        return ans;
    }
};
