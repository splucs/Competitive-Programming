class Solution {
public:
    string decodeAtIndex(string s, int k) {
        int n = s.size();
        unsigned long long size = 0;
        for (int i = 0; i < n; i++) {
            char c = s[i];
            if (c >= '0' && c <= '9') {
                size *= c-'0';
            } else {
                size++;
            }
        }

        k--; // make 0-indexed
        string ans;
        for (int i = n-1; i >= 0; i--) {
            char c = s[i];
            if (c >= '0' && c <= '9') {
                size /= c-'0';
                k %= size;
            } else {
                size--;
                if (size == k) {
                    ans += c;
                    break;
                }
            }
        }
        return ans;
    }
};
