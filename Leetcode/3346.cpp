class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        map<int, pair<int, int>> partialSum; // (frequency, number of operations required)
        for (int num : nums) {
            partialSum[num-k].first++;
            partialSum[num-k].second++;
            partialSum[num].second--;
            partialSum[num+1].second++;
            partialSum[num+k+1].first--;
            partialSum[num+k+1].second--;
        }
        int ans = 0, sum = 0, numOperationsRequired = 0;
        for (const pair<int, pair<int, int>>& entry : partialSum) {
            sum += entry.second.first;
            numOperationsRequired += entry.second.second;
            int possibleSum = sum;
            if (numOperationsRequired > numOperations) {
                possibleSum -= numOperationsRequired - numOperations;
            }
            ans = max(ans, possibleSum);
        }
        return ans;
    }
};

