class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        k--;
        int shift = 0;
        for(int i = 0; k > 0; k >>= 1, i++) {
            if ((k & 1) == 1 && operations[i] == 1) {
                shift++;
            }
        }
        return 'a' + shift % 26;
    }
};
