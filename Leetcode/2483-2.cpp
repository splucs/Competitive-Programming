class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();
        int numClients = 0;
        for (char c : customers) {
            if (c == 'Y') numClients++;
        }

        int clientsBefore = 0;
        int minCost = n;
        int minHour = -1;
        for (int i = 0; i <= n; i++) {
            int costBefore = i-clientsBefore;
            int costAfter = numClients-clientsBefore;
            int cost = costBefore + costAfter;
            if (cost < minCost) {
                minCost = cost;
                minHour = i;
            }

            if (i < n && customers[i] == 'Y') {
                clientsBefore++;
            }
        }
        return minHour;
    }
};

