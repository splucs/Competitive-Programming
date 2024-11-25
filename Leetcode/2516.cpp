class Solution {
public:
    int takeCharacters(string s, int k) {
        int i = -1, j = s.size(), n = s.size();;
        int freq[3] = {0, 0, 0};

        while (freq[0] < k || freq[1] < k || freq[2] < k) {
            j--;
            if (j < 0) {
                return -1;
            }
            freq[s[j]-'a']++;
        }

        int ans = n-j;
        for (int i = 0; i < n; i++) {
            freq[s[i]-'a']++;
            while (j < n && freq[s[j]-'a'] > k) {
                freq[s[j]-'a']--;
                j++;
            }
            ans = min(ans, i+1+n-j);
        }

        return ans;
    }
};
