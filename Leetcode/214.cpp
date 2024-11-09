class Solution {
private:
    string interpolate(string s) {
        int n = s.size();
        string ans(2*n, '|');
        for (int i = 0; i < n; i++) {
            ans[i<<1] = s[i];
        }
        ans.pop_back();
        return ans;
    }
    vector<int> manacher(string s) {
        int n = s.size();
        vector<int> maxPalindrome(n, 0);

        int c = 0, r = 0;
        for (int i = 0; i < n; i++) {
            int &p = maxPalindrome[i];
            if (i <= r) {
                p = min(r-i, maxPalindrome[(c<<1)-i]);
            }
            while (i+p+1 < n && i-p-1 >= 0 && s[i+p+1] == s[i-p-1]) {
                p++;
            }

            if (i+p > r) {
                c = i;
                r = i+p;
            }
        }
        return maxPalindrome;
    }
public:
    string shortestPalindrome(string original) {
        if (original == "") {
            return "";
        }

        string s = interpolate(original);
        vector<int> maxPalindrome = manacher(s);
        int n = s.size();
        int mid;
        for (int i = 0; i <= (n>>1); i++) {
            if (maxPalindrome[i] == i) {
                mid = i;
            }
        }
        string prefix = original.substr(maxPalindrome[mid]+1);
        reverse(prefix.begin(), prefix.end());
        return prefix + original;
    }
};
