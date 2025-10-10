class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        // Let n be numExchange-1 (we get refunded one bottle after each exchange)
        // Let b be numBottles-1 (we need to have at least one bottle at the end)
        // Let x be the number of exchanges
        // Find maximum x such that
        // b >= n + n+1 + ... + n+x-1.
        // b >= (n + n+x-1)*x/2
        // b >= (2*n-1 + x)*x/2
        // 2*b >= (2*n-1 + x)*x
        // x^2 + (2*n-1)*x - 2*b <= 0
        // delta = (2*n-1)^2 + 8*b
        // x <= (-(2*n-1) + sqrt(delta))/2
        double n = numExchange-1;
        double b = numBottles-1;
        double delta = (2*n-1)*(2*n-1) + 8*b;
        int x = (-(2*n-1) + sqrt(delta))/2;
        if (x < 0) {
            x = 0;
        }
        return numBottles + x;
    }
};
