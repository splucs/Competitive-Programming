class Solution {
public:
    string clearDigits(string s) {
        vector<char> ans;
        for (char c : s) {
            if ('0' <= c && c <= '9') {
                if (!ans.empty()) {
                    ans.pop_back();
                }
            } else {
                ans.push_back(c);
            }
        }
        return string(ans.begin(), ans.end());
    }
};
