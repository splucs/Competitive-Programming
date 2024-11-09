struct event {
    int timestamp;
    bool isArriving;
    int id;
    event(int _timestamp, bool _isArriving, int _id) : timestamp(_timestamp), isArriving(_isArriving), id(_id) {}
};

bool operator <(const event& a, const event& b) {
    if (a.timestamp != b.timestamp) {
        return a.timestamp < b.timestamp;
    }
    if (a.isArriving != b.isArriving) {
        return b.isArriving;
    }
    if (a.id != b.id) {
        return a.id < b.id;
    }
    return false;
}

class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        priority_queue<int, vector<int>, greater<int>> availableChairs;
        vector<int> chairUsed(times.size());
        int numChairs = 0;

        vector<event> events;
        events.reserve(2*times.size());
        for (int i = 0; i < (int)times.size(); i++) {
            events.push_back(event(times[i][0], true, i));
            events.push_back(event(times[i][1], false, i));
        }
        sort(events.begin(), events.end());

        for (const event& e : events) {
            if (e.isArriving) {
                if (!availableChairs.empty()) {
                    chairUsed[e.id] = availableChairs.top();
                    availableChairs.pop();
                } else {
                    chairUsed[e.id] = numChairs++;
                }
                if (e.id == targetFriend) {
                    return chairUsed[targetFriend];
                }
            } else {
                availableChairs.push(chairUsed[e.id]);
            }
        }
        return -1;
    }
};
