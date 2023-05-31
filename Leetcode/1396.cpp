struct customerInfo {
    string stationEntered;
    int timeEntered;
    customerInfo() : stationEntered(""), timeEntered(0) {}
    customerInfo(string _stationEntered, int _timeEntered) : stationEntered(_stationEntered), timeEntered(_timeEntered) {}
};

struct routeInfo {
    int time;
    int count;
    routeInfo() : time(0), count(0) {}
    routeInfo(int _time, int _count) : time(_time), count(_count) {}
};

class UndergroundSystem {
private:
    unordered_map<string, unordered_map<string, routeInfo> > routes;
    unordered_map<int, customerInfo> customers;
public:
    UndergroundSystem() {}
    
    void checkIn(int id, string stationName, int t) {
        customers[id] = customerInfo(stationName, t);
    }
    
    void checkOut(int id, string stationName, int t) {
        customerInfo customer = customers[id];
        customers.erase(id);

        routeInfo &route = routes[customer.stationEntered][stationName];
        route.time += t - customer.timeEntered;
        route.count++;
    }
    
    double getAverageTime(string startStation, string endStation) {
        routeInfo &route = routes[startStation][endStation];
        return double(route.time)/double(route.count);
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
