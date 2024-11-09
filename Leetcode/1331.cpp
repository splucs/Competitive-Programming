class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        map<int, int> rank;
        for (int x : arr) {
            rank[x] = 0;
        }
        int r = 1;
        for (auto& p : rank) {
            p.second = r++;
        }
        for (int& x : arr) {
            x = rank[x];
        }
        return arr;
    }
};
