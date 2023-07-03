class Solution {
public:
    bool buddyStrings(string s, string goal) {
        if (s.size() != goal.size()) {
            return false;
        }

        int n = s.size();
        if (n < 2) {
            return false;
        }

        vector<int> letterCount('z'-'a'+1);
        vector<int> toSwap;
        for (int i = 0; i < n; i++) {
            if (s[i] != goal[i]) {
                toSwap.push_back(i);
            }
            if (toSwap.size() > 2) {
                return false;
            }
            letterCount[s[i]-'a']++;
        }
        
        if (toSwap.size() == 1) {
            return false;
        }

        if (toSwap.size() == 0) {
            for (int cnt : letterCount) {
                if (cnt >= 2) {
                    return true;
                }
            }
            return false;
        }
        
        return s[toSwap[0]] == goal[toSwap[1]] && s[toSwap[1]] == goal[toSwap[0]];
    }
};
