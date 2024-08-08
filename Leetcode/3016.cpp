#define NUMKEYS 8

class Solution {
public:
    int minimumPushes(string word) {
        int freq[26];
        memset(&freq, 0, sizeof freq);
        for (char c : word) {
            freq[c-'a']++;
        }
        sort(freq, freq+26);
        int keys = NUMKEYS, pushes = 1;
        int ans = 0;
        for (int i = 25; i >= 0 && freq[i] > 0; i--) {
            if (keys == 0) {
                pushes++;
                keys = NUMKEYS;
            }
            ans += freq[i]*pushes;
            keys--;
        }
        return ans;
    }
};
