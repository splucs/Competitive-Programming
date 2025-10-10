class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n, -1);
        unordered_map<int, queue<int>> freq;
        set<int> avail;
        for (int i = 0; i < n; i++) {
            int r = rains[i];
            if (r == 0) {
                avail.insert(i);
                continue;
            }
            freq[r].push(i);
            if (freq[r].size() == 1) {
                continue;
            }

            auto it = avail.upper_bound(freq[r].front());
            if (it == avail.end()) {
                return {};
            }
            ans[*it] = r;
            avail.erase(it);
            freq[r].pop();
        }

        for (int i : avail) {
            ans[i] = 1;
        }
        return ans;
    }
};
