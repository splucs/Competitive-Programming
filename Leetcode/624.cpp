#define INF 0x3f3f3f3f
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        pair<int, int> maxq[2] = {{-INF, -1}, {-INF, -1}};
        pair<int, int> minq[2] = {{INF, -1}, {INF, -1}};
        for (int i = 0; i < (int)arrays.size(); i++) {
            pair<int, int> maxe(*arrays[i].rbegin(), i);
            pair<int, int> mine(*arrays[i].begin(), i);

            if (maxq[1] < maxe) {
                maxq[1] = maxe;
                if (maxq[0] < maxq[1]) {
                    swap(maxq[0], maxq[1]);
                }
            }
            if (minq[1] > mine) {
                minq[1] = mine;
                if (minq[0] > minq[1]) {
                    swap(minq[0], minq[1]);
                }
            }
        }
        if (maxq[0].second != minq[0].second) {
            return maxq[0].first - minq[0].first;
        }
        return max(maxq[1].first - minq[0].first, maxq[0].first - minq[1].first);
    }
};
