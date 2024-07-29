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
    void reduce(vector<int> &rating) {
        map<int, int> reduced;
        for (int x : rating) {
            reduced[x] = 0;
        }
        int cnt = 0;
        for (auto &it : reduced) {
            it.second = ++cnt;
        }
        for (int i = 0; i < (int)rating.size(); i++) {
            rating[i] = reduced[rating[i]];
        }
    }
    int numTeamsOneWay(vector<int> &rating) {
        int n = rating.size();
        FenwickTree team1(n), team2(n);
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
        reduce(rating);
        int ans = numTeamsOneWay(rating);
        reverse(rating.begin(), rating.end());
        ans += numTeamsOneWay(rating);
        return ans;
    }
};
