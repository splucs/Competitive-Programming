class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        int n = groupSizes.size();
        vector<vector<int>> usersBySize(n+1);
        vector<vector<int>> ans;
        for (int i = 0; i < n; i++) {
            int s = groupSizes[i];
            vector<int> &cur = usersBySize[s];
            cur.push_back(i);
            if (cur.size() == s) {
                ans.push_back(cur);
                cur.clear();
            }
        }
        return ans;
    }
};
