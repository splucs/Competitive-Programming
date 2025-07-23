class Solution {
private:
    vector<int> freq, used;
    int compute() {
        int ans = 1, num = 1;
        for (int i = 0; i < 26; i++) {
            for (int den = 1; den <= used[i]; den++) {
                ans *= num++;
                ans /= den;
            }
        }
        return ans;
    }
    int recurse(int i) {
        if (i == used.size()) {
            return compute();
        }

        int ans = 0;
        for(used[i] = 0; used[i] <= freq[i]; used[i]++) {
            ans += recurse(i+1);
        }
        return ans;
    }
public:
    int numTilePossibilities(string tiles) {
        freq.assign(26, 0);
        used.assign(26, 0);
        for (char c : tiles) {
            freq[c-'A']++;
        }
        return recurse(0)-1;
    }
};
