class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        vector<int> freq(n, 0);
        int numDiff = 0, ans = 0;
        for (int i = n-1, j = n-1; i >= 0; i--) {
            freq[fruits[i]]++;
            if (freq[fruits[i]] == 1) {
                numDiff++;
            }

            while (numDiff > 2) {
                if (freq[fruits[j]] == 1) {
                    numDiff--;
                }
                freq[fruits[j--]]--;
            }

            ans = max(ans, j-i+1);
        }
        return ans;
    }
};
