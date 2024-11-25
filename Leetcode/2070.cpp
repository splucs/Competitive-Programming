class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        sort(items.begin(), items.end());
        int prevBeauty = 0;
        for (vector<int> &item : items) {
            prevBeauty = item[1] = max(item[1], prevBeauty);
        }
        for (int &q : queries) {
            int lo = -1, hi = items.size();
            while(hi > lo + 1) {
                int mid = (hi+lo)>>1;
                if (items[mid][0] <= q) lo = mid;
                else hi = mid;
            }
            q = lo == -1 ? 0 : items[lo][1];
        }
        return queries;
    }
};
