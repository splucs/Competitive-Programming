class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();
        vector<int> costAfter(n+1, 0);
        for (int i = n-1; i >= 0; i--) {
            costAfter[i] = costAfter[i+1];
            if (customers[i] == 'Y') costAfter[i]++;
        }

        int costBefore = 0;
        int minCost = n;
        int minHour = -1;
        for (int i = 0; i <= n; i++) {
            int cost = costBefore + costAfter[i];
            if (cost < minCost) {
                minCost = cost;
                minHour = i;
            }

            if (i < n && customers[i] == 'N') {
                costBefore++;
            }
        }
        return minHour;
    }
};

