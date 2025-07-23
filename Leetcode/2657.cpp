class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> freqA(n, 0), freqB(n, 0), C(n, 0);
        for (int i = 0; i < n; i++) {
            A[i]--, B[i]--;
            freqA[A[i]]++;
            freqB[B[i]]++;
            if (i > 0) {
                C[i] = C[i-1];
            }
            if (freqA[A[i]] == freqB[A[i]]) {
                C[i]++;
            }
            if (A[i] != B[i] && freqA[B[i]] == freqB[B[i]]) {
                C[i]++;
            }
        }
        return C;
    }
};
