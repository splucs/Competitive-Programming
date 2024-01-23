class Solution {
public:
    int maxLength(vector<string>& arr) {
        int n = arr.size();
        vector<int> mask(n, 0);
        for (int i = 0; i < n; i++) {
            for (char c : arr[i]) {
                mask[i] |= (1 << (c-'a'));
            }
            if (arr[i].size() != __builtin_popcount(mask[i])) {
                mask[i] = 0;
            }
        }

        unordered_set<int> possible;
        possible.insert(0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            vector<int> toAdd;
            for (const auto& subM : possible) {
                if ((subM & mask[i]) != 0) {
                    continue;
                }
                int m = subM|mask[i];
                if (possible.count(m)) {
                    continue;
                }
                toAdd.push_back(m);
                ans = max(ans, __builtin_popcount(m));
            }
            for (int m : toAdd) {
                possible.insert(m);
            }
        }
        return ans;
    }
};
