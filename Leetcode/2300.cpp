class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size(), m = potions.size();
        sort(potions.begin(), potions.end());
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            long long minPotion = (success+spells[i]-1)/spells[i];
            int lo = -1, hi = m;
            while (hi > lo + 1) {
                int mid = (lo + hi) >> 1;
                if (potions[mid] < minPotion) lo = mid;
                else hi = mid;
            }
            ans[i] = m - hi;
        }
        return ans;
    }
};
