class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        string t(2*n+1, '|');
        for (int i = 0; i < n; i++) {
            t[(i<<1)+1] = s[i];
        }

        n = (n<<1)+1;
        t.resize(n);
        vector<int> len(n, 1);

        int ansIdx = 0, ansLen = 0;
        int c = 0;

        for (int i = 0; i < n; i++) {
            int &l = len[i]; 

            int j = (c<<1) - i;
            if (j >= 0) {
                l = min(len[j], j-c+len[c]);
            } 

            while (i-l >= 0 && i+l < n && t[i-l] == t[i+l]) l++;

            if (c+len[c] < i+l) {
                c = i;
            }
            if (ansLen < l) {
                ansLen = l;
                ansIdx = i;
            }
        }

        string ans(ansLen-1, 'a');
        for (int i = ansIdx-ansLen+2, j = 0; i < ansIdx+ansLen; i+=2) {
            ans[j++] = t[i];
        }
        return ans;
    }
};
