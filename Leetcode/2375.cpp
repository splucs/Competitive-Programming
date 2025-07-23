class Solution {
private:
    vector<bool> used;
    int n;
    string pattern;
    string ans;
    bool recurse(int i) {
        if (i == n+1) {
            return true;
        }

        char from = '1';
        if (i > 0 && pattern[i-1] == 'I') {
            from = ans[i-1]+1;
        }
        char to = '9';
        if (i > 0 && pattern[i-1] == 'D') {
            to = ans[i-1]-1;
        }
        
        for (char c = from; c <= to; c++) {
            if (used[c-'0']) {
                continue;
            }
            used[c-'0'] = true;
            ans[i] = c;
            if (recurse(i+1)) {
                return true;    
            }
            used[c-'0'] = false;
        }
        return false;
    }
public:
    string smallestNumber(string _pattern) {
        pattern.swap(_pattern);
        n = pattern.size();

        used.assign(10, false);
        ans.resize(n+1);

        recurse(0);
        return ans;
    }
};
