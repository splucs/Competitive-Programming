class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) {
        ft.assign(n + 1, 0);
    }
    int rsq(int i) {
        int sum = 0;
        for(; i; i -= (i & -i)) {
            sum = sum + ft[i];
        }
        return sum;
    }
    void update(int i, int v) {
        for(; i > 0 && i < (int)ft.size(); i += (i & -i)) {
            ft[i] += v;
        }
    }
};

class Solution {
private:
    int calcMaxElem(vector<int> &rating) {
        int ans = 0;
        for (int i = 0; i < (int)rating.size(); i++) {
            ans = max(ans, rating[i]);
        }
        return ans;
    }
    int numTeamsOneWay(vector<int> &rating, int maxElem) {
        int n = rating.size();
        FenwickTree team1(maxElem), team2(maxElem);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            team1.update(rating[i], 1);
            team2.update(rating[i], team1.rsq(rating[i]-1));
            ans += team2.rsq(rating[i]-1);
        }
        return ans;
    }
public:
    int numTeams(vector<int>& rating) {
        int maxElem = calcMaxElem(rating);
        int ans = numTeamsOneWay(rating, maxElem);
        reverse(rating.begin(), rating.end());
        ans += numTeamsOneWay(rating, maxElem);
        return ans;
    }
};
