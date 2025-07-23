class Solution {
private:
    string RLE(string s) {
        int cnt = 0;
        char prev = s[0];
        string ans;
        for (char c : s) {
            if (c == prev) {
                cnt++;
                continue;
            }
            ans = ans + to_string(cnt) + prev;
            cnt = 1;
            prev = c;
        }
        ans = ans + to_string(cnt) + prev;
        return ans;
    }
public:
    string countAndSay(int n) {
        string s = "1";
        for (int i = 2; i <= n; i++) {
            s = RLE(s);
        }
        return s;
    }
};
