class MyQueue {
private:
    stack<int> in, out;
    void transfer() {
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }
public:
    MyQueue() {}
    
    void push(int x) {
        in.push(x);
    }
    
    int pop() {
        if (out.empty()) {
            transfer();
        }
        int ans = out.top();
        out.pop();
        return ans;
    }
    
    int peek() {
        if (out.empty()) {
            transfer();
        }
        return out.top();
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
