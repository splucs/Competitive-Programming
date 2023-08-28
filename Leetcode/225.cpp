class MyStack {
private:
    queue<int> q;
    int last = -1;
public:
    MyStack() {
        
    }
    
    void push(int x) {
        q.push(x);
        last = x;
    }
    
    int pop() {
        int n = q.size();
        queue<int> nq;
        for (int i = 0; i < n-1; i++) {
            int x = q.front();
            last = x;
            nq.push(x);
            q.pop();
        }
        int popped = q.front();
        q = nq;
        return popped;
    }
    
    int top() {
        return last;
    }
    
    bool empty() {
       return q.size() == 0;
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
