#define INF 0x3f3f3f3f3f3f3f3fLL
class Solution {
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        int n = nums1.size(), m = nums2.size();
        vector<long long> pos1, pos2, neg1, neg2;
        long long zero1 = 0, zero2 = 0;
        for (int num : nums1) {
            if (num < 0) neg1.push_back(-num);
            else if (num > 0) pos1.push_back(num);
            else zero1++;
        }
        reverse(neg1.begin(), neg1.end());
        for (int num : nums2) {
            if (num < 0) neg2.push_back(-num);
            else if (num > 0) pos2.push_back(num);
            else zero2++;
        }
        reverse(neg2.begin(), neg2.end());

        long long lo = -INF, hi = INF;
        while (hi > lo + 1) {
            long long x = (hi + lo) / 2;
            
            long long numLessEq = 0;
            if (x < 0) {
                for (int i = pos1.size()-1, j = 0; i >= 0; i--) {
                    while(j < (int)neg2.size() && pos1[i]*neg2[j] < -x) {
                        j++;
                    }
                    numLessEq += neg2.size() - j;
                }
                for (int i = neg1.size()-1, j = 0; i >= 0; i--) {
                    while(j < (int)pos2.size() && neg1[i]*pos2[j] < -x) {
                        j++;
                    }
                    numLessEq += pos2.size() - j;
                }
            } else if (x > 0) {
                numLessEq += zero1*m + zero2*n - zero1*zero2;
                numLessEq += neg1.size()*(long long)pos2.size() + neg2.size()*(long long)pos1.size();
                for (int i = 0, j = pos2.size()-1; i < (int)pos1.size(); i++) {
                    while(j >= 0 && pos1[i]*pos2[j] > x) {
                        j--;
                    }
                    numLessEq += j+1;
                }
                for (int i = 0, j = neg2.size()-1; i < (int)neg1.size(); i++) {
                    while(j >= 0 && neg1[i]*neg2[j] > x) {
                        j--;
                    }
                    numLessEq += j+1;
                }
            } else {
                numLessEq += zero1*m + zero2*n - zero1*zero2;
                numLessEq += neg1.size()*(long long)pos2.size() + neg2.size()*(long long)pos1.size();
            }
            
            if (numLessEq >= k) hi = x;
            else lo = x;
        }
        return hi;
    }
};
