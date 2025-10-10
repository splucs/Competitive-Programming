#define MOD 1000000007

class Solution {
private:
    int n;
    vector<long long> arr; //1-indexed
    vector<int> minLeft, minRight;
    vector<long long> partialSum;
    vector<long long> specialSum, revSpecialSum;
    void buildSums() {
        partialSum.assign(n+2, 0);
        specialSum.assign(n+2, 0);
        for (int i = 1; i <= n; i++) {
            partialSum[i] = (arr[i] + partialSum[i-1]) % MOD;
            specialSum[i] = (((i*arr[i]) % MOD) + specialSum[i-1]) % MOD;
        }
        revSpecialSum.assign(n+2, 0);
        for (int i = n; i > 0; i--) {
            revSpecialSum[i] = ((((n-i+1)*arr[i]) % MOD) + revSpecialSum[i+1]) % MOD;
        }

        minLeft.assign(n+2, 0);
        minRight.assign(n+2, 0);

        vector<pair<int, long long>> st;
        st.push_back(make_pair(0, 0));
        for (int i = 1; i <= n; i++) {
            while(st.back().second >= arr[i]) {
                st.pop_back();
            }
            minLeft[i] = st.back().first;
            st.push_back(make_pair(i, arr[i]));
        }
        st.clear();
        st.push_back(make_pair(n+1, 0));
        for (int i = n; i > 0; i--) {
            while(st.back().second > arr[i]) {
                st.pop_back();
            }
            minRight[i] = st.back().first;
            st.push_back(make_pair(i, arr[i]));
        }
    }
public:
    int totalStrength(vector<int>& strength) {
        n = strength.size();
        arr.assign(n+2, 0);
        for (int i = 0; i < n; i++) {
            arr[i+1] = strength[i];
        }
        buildSums();

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int l = minLeft[i], r = minRight[i];
            int arraysLeft = i - l;
            int arraysRight = r - i;

            // left = [l+1, i-1]
            long long sumsLeft = (specialSum[i-1] - specialSum[l] + MOD) % MOD;
            long long sumsLeftAdj = (l * ((partialSum[i-1] - partialSum[l] + MOD) % MOD)) % MOD;
            sumsLeft = (sumsLeft - sumsLeftAdj + MOD) % MOD;

            // right = [i+1, r-1]
            long long sumsRight = (revSpecialSum[i+1] - revSpecialSum[r] + MOD) % MOD;
            long long sumsRightAdj = ((n-r+1) * ((partialSum[r-1] - partialSum[i] + MOD) % MOD)) % MOD;
            sumsRight = (sumsRight - sumsRightAdj + MOD) % MOD;

            long long diff = 0;
            diff = (diff + ((sumsRight*arraysLeft) % MOD)) % MOD;
            diff = (diff + ((sumsLeft*arraysRight) % MOD)) % MOD;
            diff = (diff + ((((arr[i]*arraysRight) % MOD)*arraysLeft) % MOD)) % MOD;
            ans = (ans + ((diff*arr[i]) % MOD) % MOD) % MOD;
        }
        return ans;
    }
};
