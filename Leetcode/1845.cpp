#define parent(x) ((x)>>1)
#define left(x) ((x)<<1)
#define right(x) (((x)<<1)+1)

class SeatManager {
private:
    vector<int> heap;
    void init(int n) {
        heap.resize(n+1);
        for (int i = 0; i <= n; i++) {
            heap[i] = i;
        }
    }
    void seafup(int i) {
        while (i > 1) {
            int p = parent(i);
            if (heap[i] < heap[p]) {
                swap(heap[i], heap[p]);
                i = p;
            } else {
                break;
            }
        }
    }
    void seafdown(int i) {
        int n = heap.size();
        while (left(i) < n) {
            int l = left(i);
            int r = right(i);

            // nxt is the smallest of l and r
            int nxt = l;
            if (r < n && heap[r] < heap[l]) {
                nxt = r;
            }

            if (heap[nxt] < heap[i]) {
                swap(heap[nxt], heap[i]);
                i = nxt;
            } else {
                break;
            }
        }
    }
public:
    SeatManager(int n) {
        init(n);
    }
    
    int reserve() {
        int ans = heap[1];
        swap(heap[1], heap[heap.size()-1]);
        heap.pop_back();
        seafdown(1);
        return ans;
    }
    
    void unreserve(int seatNumber) {
        heap.push_back(seatNumber);
        seafup(heap.size()-1);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
