class Solution {
public:
    long long flowerGame(int n, int m) {
        return (n/2)*((m+1LL)/2) + (m/2)*((n+1LL)/2);
    }
};
