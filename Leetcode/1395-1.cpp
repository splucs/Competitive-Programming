class Solution {
private:
    int numTeamsOneWay(vector<int> &rating) {
        int n = rating.size();
        vector<int> team2(n, 0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (rating[j] < rating[i]) {
                    team2[i]++;
                    ans += team2[j];
                }
            }
        }
        return ans;
    }
public:
    int numTeams(vector<int>& rating) {
        int ans = numTeamsOneWay(rating);
        reverse(rating.begin(), rating.end());
        ans += numTeamsOneWay(rating);
        return ans;
    }
};
