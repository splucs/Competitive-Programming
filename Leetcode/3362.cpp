class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<vector<int>> startToEnd(n);
        vector<int> endsAt(n, 0);
        for (const vector<int>& query : queries) {
            int i = query[0], j = query[1];
            startToEnd[i].push_back(j);
            endsAt[j]++;
        }
        multiset<int> endsAvailable;
        int cur = 0, ans = queries.size();
        for (int i = 0; i < n; i++) {
            for (int j : startToEnd[i]) {
                endsAvailable.insert(j);
            }
            while (cur < nums[i]) {
                if (endsAvailable.empty()) {
                    return -1;
                }
                int j = *endsAvailable.rbegin();
                auto it = endsAvailable.find(j);
                endsAvailable.erase(it);
                cur++;
                ans--;
            }
            while (endsAt[i] --> 0) {
                auto it = endsAvailable.find(i);
                if (it != endsAvailable.end()) {
                    endsAvailable.erase(it);
                } else {
                    cur--;
                }
            }
        }
        return ans;
    }
};
