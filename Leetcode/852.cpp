class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int lo = 0;
        int hi = arr.size()-1;
        while (hi > lo + 1) {
            int mid = (hi+lo)>>1;
            if (arr[mid] > arr[mid+1]) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        return arr[lo] > arr[hi] ? lo : hi;
    }
};
