class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        int total = mean*(n+m);
        for (int roll : rolls) {
            total -= roll;
        }

        int quo = total/n, rem = total%n;
        if (total < n || quo > 6 || (quo == 6 && rem > 0)) {
            return vector<int>();
        }
        
        vector<int> ans(n, quo);
        for (int i = 0; i < rem; i++) {
            ans[i]++;
        }
        return ans;
    }
};
