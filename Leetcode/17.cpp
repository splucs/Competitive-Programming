class Solution {
private:
    vector<string> buttons = {
        "",
        "",
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz",
    };
    vector<string> ans;
    string cur;
public:
    vector<string> letterCombinations(string digits) {
        ans.clear();
        if (digits.empty()) return ans;
        cur.resize(digits.size());
        recurse(digits, 0);
        return ans;
    }
    void recurse(string &digits, int i) {
        if (i == (int)digits.size()) {
            ans.push_back(cur);
            return;
        }
        for (char c : buttons[digits[i]-'0']) {
            cur[i] = c;
            recurse(digits, i+1);
        }
    }
};
