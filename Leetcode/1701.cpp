class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        int curFinishTime = 0;
        long long totalWait = 0;
        int n = customers.size();
        for (int i = 0; i < n; i++) {
            int start = customers[i][0];
            int duration = customers[i][1];
            if (curFinishTime < start) {
                curFinishTime = start;
            }
            curFinishTime += duration;
            totalWait += curFinishTime - start;
        }
        return totalWait / (double)customers.size();
    }
};
