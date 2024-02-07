#define MAX_CHAR 62
class Solution {
private:
    int toId(char c) {
        if ('a' <= c && c <= 'z') {
            return c-'a';
        }
        if ('A' <= c && c <= 'Z') {
            return c-'A'+26;
        }
        if ('0' <= c && c <= '9') {
            return c-'0'+52;
        }
        return -1;
    }
public:
    string frequencySort(string s) {
        vector<pair<int, char>> freq(MAX_CHAR);
        for (char c = 'a'; c <= 'z'; c++) {
            freq[toId(c)].second = c;
        }
        for (char c = 'A'; c <= 'Z'; c++) {
            freq[toId(c)].second = c;
        }
        for (char c = '0'; c <= '9'; c++) {
            freq[toId(c)].second = c;
        }
        for (char c : s) {
            freq[toId(c)].first++;
        }
        sort(freq.begin(), freq.end());
        vector<char> ans(s.size());
        for (int c = MAX_CHAR-1, i = 0; c >= 0; c--) {
            while(freq[c].first --> 0) {
                ans[i++] = freq[c].second;
            }
        }
        return string(ans.begin(), ans.end());
    }
};
