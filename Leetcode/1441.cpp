class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        int j = 0;
        int t = target.size();
        vector<string> ans;
        ans.reserve(target.back()+target.back()-t);
        for (int i = 1; i <= n && j < t; i++) {
            if (i == target[j]) {
                ans.push_back("Push");
                j++;
            } else {
                ans.push_back("Push");
                ans.push_back("Pop");
            }
        }
        return ans;
    }
};
