class Solution {
    vector<vector<int>> nxt, cnt;
    int n, k, maxSub;
    vector<int> freq;
    string sub;
    bool isValid() {
        int i = 0;
        freq.assign(26, 0);
        for (int j = 0; j < (int)sub.size(); j++) {
            int c = sub[j]-'a';
            freq[c] += k;
        }
        for (int kt = 0; kt < k; kt++) {
            for (int j = 0; j < (int)sub.size(); j++) {
                int c = sub[j]-'a';
                if (cnt[i][c] < freq[c]) {
                    return false;
                }
                freq[c]--;
                i = nxt[i][c]+1;
            }
        }
        return true;
    }

    string ans;
    void iterateSub(string& s, int i) {
        if (sub.size() == maxSub) {
            return;
        }
        for (char ct = 'z'; ct >= 'a'; ct--) {  
            char c = ct-'a';
            if (nxt[i][c] == -1) {
                continue;
            }
            sub.push_back(ct);
            if (isValid()) {
                iterateSub(s, nxt[i][c]+1);
                if (ans.size() < sub.size()) {
                    ans = sub;
                }
            }
            sub.pop_back();
        }
    }
public:
    string longestSubsequenceRepeatedK(string s, int _k) {
        n = s.size();
        k = _k;
        maxSub = n/k;
        ans = "";
        nxt.assign(n+1, vector<int>(26, -1));
        cnt.assign(n+1, vector<int>(26, 0));
        for (int i = n-1; i >= 0; i--) {
            int c = s[i]-'a';
            nxt[i] = nxt[i+1];
            nxt[i][c] = i;
            cnt[i] = cnt[i+1];
            cnt[i][c]++;
        }
        iterateSub(s, 0);
        return ans;
    }
};
