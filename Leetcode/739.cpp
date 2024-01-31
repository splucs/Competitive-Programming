class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> decTemp, decIdx;
        int n = temperatures.size();
        vector<int> ans(n, 0);
        for (int i = n-1; i >= 0; i--) {
            int temp = temperatures[i];
            while(!decTemp.empty() && temp >= decTemp.back()) {
                decTemp.pop_back();
                decIdx.pop_back();
            }
            if (!decTemp.empty()) {
                ans[i] = decIdx.back() - i;
            }
            decTemp.push_back(temp);
            decIdx.push_back(i);
        }
        return ans;
    }
};
