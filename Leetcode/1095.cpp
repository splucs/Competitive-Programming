/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */
struct CachedArray {
    vector<int> cache;
    MountainArray *mountainArr;
    CachedArray() : mountainArr(NULL) {}
    CachedArray(MountainArray &_mountainArr) : mountainArr(&_mountainArr) {
        cache.assign(_mountainArr.length(), -1);
    }
    int get(int i) {
        if (cache[i] == -1) cache[i] = mountainArr->get(i);
        return cache[i];
    }
};

class Solution {
private:
    CachedArray arr;

    int findPeak(int lo, int hi) {
        if (hi - lo < 3) {
            int ans = -1, ansV = -1;
            for (int i = lo; i <= hi; i++) {
                int v = arr.get(i);
                if (v > ansV) {
                    ans = i;
                    ansV = v;
                }
            }
            return ans;
        }

        int d = (hi-lo)/3;
        int c1 = lo+d;
        int v1 = arr.get(c1);
        int c2 = hi-d;
        int v2 = arr.get(c2);

        // peak <= c2
        if (v1 > v2) {
            return findPeak(lo, c2);
        }
        // c1 <= peak
        else if (v1 < v2) {
            return findPeak(c2, hi);
        }
        // c1 <= peak <= c2
        else {
            return findPeak(c1, c2);
        }
    }

    int findInc(int lo, int hi, int target) {
        if (lo > hi) return -1;

        int mid = (lo+hi)/2;
        int v = arr.get(mid);

        if (target < v) return findInc(lo, mid-1, target);
        else if (target > v) return findInc(mid+1, hi, target);
        else return mid;
    }

    int findDec(int lo, int hi, int target) {
        if (lo > hi) return -1;

        int mid = (lo+hi)/2;
        int v = arr.get(mid);

        if (target > v) return findDec(lo, mid-1, target);
        else if (target < v) return findDec(mid+1, hi, target);
        else return mid;
    }
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        arr = CachedArray(mountainArr);
        int peak = findPeak(0, mountainArr.length()-1);
        int ans = findInc(0, peak, target);
        if (ans != -1) return ans;
        return findDec(peak, mountainArr.length()-1, target);
    }
};
