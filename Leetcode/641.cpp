class MyCircularDeque {
private:
    int st, en;
    int curSize, maxSize;
    vector<int> deq;
public:
    MyCircularDeque(int k) {
        maxSize = k;
        deq.resize(k);
        st = en = 0;
        curSize = 0;
    }
    
    bool insertFront(int value) {
        if (curSize == maxSize) {
            return false;
        }
        curSize++;
        st = (st-1+maxSize)%maxSize;
        deq[st] = value;
        return true;
    }
    
    bool insertLast(int value) {
        if (curSize == maxSize) {
            return false;
        }
        curSize++;
        deq[en] = value;
        en = (en+1)%maxSize;
        return true;
    }
    
    bool deleteFront() {
        if (curSize == 0) {
            return false;
        }
        curSize--;
        st = (st+1)%maxSize;
        return true;
    }
    
    bool deleteLast() {
        if (curSize == 0) {
            return false;
        }
        curSize--;
        en = (en-1+maxSize)%maxSize;
        return true;
    }
    
    int getFront() {
        if (curSize == 0) {
            return -1;
        } 
        return deq[st];
    }
    
    int getRear() {
        if (curSize == 0) {
            return -1;
        } 
        return deq[(en-1+maxSize)%maxSize];
    }
    
    bool isEmpty() {
        return curSize == 0;
    }
    
    bool isFull() {
        return curSize == maxSize;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
