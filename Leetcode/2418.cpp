class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        int n = names.size();
        vector<int> idx(n);
        for (int i = 0; i < n; i++) {
            idx[i] = i;
        }

        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return heights[i] > heights[j];
        });
        vector<string> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i].swap(names[idx[i]]);
        }
        return ans;
    }
};
