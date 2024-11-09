class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        for (int& x : arr) {
            x = ((x%k)+k)%k;
        }
        sort(arr.begin(), arr.end());
        int i = 0, j = arr.size()-1;
        for (; i < j && arr[i] == 0; i += 2) {
            if (arr[i+1] != 0) {
                return false;
            }
        }
        for (; i < j; i++, j--) {
            if ((arr[i]+arr[j])%k != 0) {
                return false;
            }
        }
        return true;
    }
};
