class Solution {
private:
     bool checkValidCuts1D(vector<pair<int, int>>& ranges) {
        int last = 0;
        sort(ranges.begin(), ranges.end());
        int cuts = 0;
        for (const pair<int, int> range : ranges) {
            if (range.first >= last) {
                cuts++;
            }
            last = max(last, range.second);
        }
        return cuts >= 3;
    }
public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        vector<pair<int, int>> horizontal, vertical;
        for (const vector<int>& rectangle : rectangles) {
            horizontal.push_back(make_pair(rectangle[0], rectangle[2]));
            vertical.push_back(make_pair(rectangle[1], rectangle[3]));
        }
        return checkValidCuts1D(horizontal) || checkValidCuts1D(vertical);
    }
};
