class MyCalendar {
private:
    map<int, bool> calendar;
    void doBook(int start, int end) {
        if (calendar.count(start)) {
            calendar.erase(start);
        } else {
            calendar[start] = true;
        }

        if (calendar.count(end)) {
            calendar.erase(end);
        } else {
            calendar[end] = false;
        }
    }
public:
    MyCalendar() {}
    
    bool book(int start, int end) {
        auto it = calendar.lower_bound(start);
        auto nxt = it;
        if (nxt != calendar.end() && nxt->first == start && !nxt->second) {
            nxt++;
        }
        if (nxt == calendar.end()) {
            doBook(start, end);
            return true;
        }
        if (nxt->first < end || !nxt->second) {
            return false;
        }
        doBook(start, end);
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */
