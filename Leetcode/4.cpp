class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int median = (m+n)>>1;

        // i points to the first index of nums1 that belongs to the second half. 0 <= i <= m.
        // j points to the first index of nums2 that belongs to the second half. 0 <= j <= n.
        // i+j is always equal to median, i.e. there are (m+n)/2 elements combined before them.
        // Second half is bigger than first half if n+m is odd.
        int i = median;
        int j = 0;
        if (i > m) {
            int d = i-m;
            i -= d;
            j += d;
        }
        
        int d = 1;
        while (d < n+m) d <<= 1;
        // Stop when nums1[i-1] <= nums2[j] and nums2[j-1] <= nums1[i].
        // nums1[-1] == nums1[-1] == -INF
        // nums1[m] == nums1[n] == INF
        while (true) {
            // i needs to move left and j needs to move right
            if (j < n && 0 < i && nums1[i-1] > nums2[j]) {
                int reald = d;
                d >>= 1;
                reald = min(reald, i);
                reald = min(reald, n-j);
                i -= reald;
                j += reald;
            }
            // i needs to move right and j needs to move left 
            else if (i < m && 0 < j && nums2[j-1] > nums1[i]) {
                int reald = d;
                d >>= 1;
                reald = min(reald, m-i);
                reald = min(reald, j);
                i += reald;
                j -= reald;
            }
            else break;
        }

        // The minimum value of the second half.
        int minSecond;
        if (i == m) minSecond = nums2[j];
        else if (j == n) minSecond = nums1[i];
        else minSecond = min(nums1[i], nums2[j]);

        // If n+m is odd, answer is minimum of second half.
        if ((n+m)&1) return (double)minSecond;

        // The maximum value of the first half.
        int maxFirst;
        if (i == 0) maxFirst = nums2[j-1];
        else if (j == 0) maxFirst = nums1[i-1];
        else maxFirst = max(nums1[i-1], nums2[j-1]);
    
        // If n+m is even, answer is average of minimum of second half and maximum of first half.
        return (maxFirst + minSecond) / 2.0;
    }
};
