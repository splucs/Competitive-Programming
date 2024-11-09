class CustomStack {
    vector<int> st, lazy;
    int maxSize;
public:
    CustomStack(int _maxSize) {
        maxSize = _maxSize;
    }
    
    void push(int x) {
        if (st.size() == maxSize) {
            return;
        }
        st.push_back(x);
        lazy.push_back(0);
    }
    
    int pop() {
        if (st.empty()) {
            return -1;
        }
        if (lazy.size() > 1) {
            lazy[st.size()-2] += lazy.back();
        }
        int ans = st.back() + lazy.back();
        st.pop_back();
        lazy.pop_back();
        return ans;
    }
    
    void increment(int k, int val) {
        if (lazy.empty()) {
            return;
        }
        if (k > lazy.size()) {
            k = lazy.size();
        }
        lazy[k-1] += val;
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
