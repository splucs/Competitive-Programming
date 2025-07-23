class Solution {
private:
    bool isPrefixAndSuffix(const string& str1, const string& str2) {
        int n = str1.size(), m = str2.size();
        if (n > m) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if (str1[i] != str2[i]) {
                return false;
            }
            if (str1[n-1-i] != str2[m-1-i]) {
                return false;
            }
        }
        return true;
    }
public:
    int countPrefixSuffixPairs(vector<string>& words) {
        int ans = 0;
        for (int j = 0; j < (int)words.size(); j++) {
            for (int i = 0; i < j; i++) {
                if (isPrefixAndSuffix(words[i], words[j])) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
