class Solution {
private:
    vector<int> nums, aux;
    int ans;
    void mergeSort(int l, int r) {
        // recursion base case
        if (l == r) {
            return;
        }

        // recurse
        int mid = (l+r) >> 1;
        mergeSort(l, mid);
        mergeSort(mid+1, r);

        // count reverse pairs
        for (int i = l, j = mid+1; i <= mid; i++) {
            while (j <= r && nums[i] > 2LL*nums[j]) {
                j++;
            }
            ans += j-mid-1;
        }

        // merge sort
        int i = l, j = mid+1, k = l;
        while (i <= mid && j <= r) {
            if (nums[i] < nums[j]) {
                aux[k++] = nums[i++];
            } else {
                aux[k++] = nums[j++];
            }
        }
        while (i <= mid) {
            aux[k++] = nums[i++];
        }
        while (j <= r) {
            aux[k++] = nums[j++];
        }
        for (k = l; k <= r; k++) {
            nums[k] = aux[k];
        }
    }
public:
    int reversePairs(vector<int>& _nums) {
        nums.swap(_nums);
        int n = nums.size();
        aux.resize(n);
        ans = 0;
        mergeSort(0, n-1);
        return ans;
    }
};
