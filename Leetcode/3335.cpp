#define MOD 1000000007
class Solution {
public:
    int lengthAfterTransformations(string s, int t) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c-'a']++;
        }
        while (t --> 0) {
            int numZ = freq.back();
            for (int i = 25; i > 0; i--) {
                freq[i] = freq[i-1];
            }
            freq[0] = numZ;
            freq[1] = (freq[1] + numZ) % MOD;
        }
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            ans = (ans + freq[i]) % MOD;
        }
        return ans;
    }
};
