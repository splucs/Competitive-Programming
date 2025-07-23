class Solution {
public:
    int differenceOfSums(int n, int m) {
        int div = n/m;
        int sumDiv = div*(div+1)*m/2;
        int sum = n*(n+1)/2;
        return sum - 2*sumDiv;
    }
};
