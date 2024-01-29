class MyQueue {
private:
    vector<int> in, out;
    void transfer() {
        while (!in.empty()) {
            out.push_back(in.back());
            in.pop_back();
        }
    }
public:
    MyQueue() {}
    
    void push(int x) {
        in.push_back(x);
    }
    
    int pop() {
        if (out.empty()) {
            transfer();
        }
        int ans = out.back();
        out.pop_back();
        return ans;
    }
    
    int peek() {
        if (out.empty()) {
            transfer();
        }
        return out.back();
    }
    
    bool empty() {
        return in.empty() && out.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
