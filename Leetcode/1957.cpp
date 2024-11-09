class Solution {
public:
    string makeFancyString(string s) {
        int cnt = 0;
        char last = '$';
        vector<char> ans;
        for (char c : s) {
            if (c != last) {
                last = c;
                cnt = 0;
            }
            cnt++;
            if (cnt <= 2) {
                ans.push_back(c);
            }
        }
        return string(ans.begin(), ans.end());
    }
};
