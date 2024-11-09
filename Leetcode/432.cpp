class AllOne {
private:
    unordered_map<string, int> str2cnt;
    set<pair<int, string>> cnt2str;
public:
    AllOne() {
        
    }
    
    void inc(string key) {
        int cnt = 0;
        if (str2cnt.count(key)) {
            cnt = str2cnt[key];
            cnt2str.erase(make_pair(cnt, key));
        }
        cnt++;
        str2cnt[key] = cnt;
        cnt2str.insert(make_pair(cnt, key));
    }
    
    void dec(string key) {
        int cnt = str2cnt[key];
        cnt2str.erase(make_pair(cnt, key));
        cnt--;
        if (cnt > 0) {
            str2cnt[key] = cnt;
            cnt2str.insert(make_pair(cnt, key));
        } else {
            str2cnt.erase(key);
        }
    }
    
    string getMaxKey() {
        if (str2cnt.empty()) {
            return "";
        }
        return cnt2str.rbegin()->second;
    }
    
    string getMinKey() {
        if (str2cnt.empty()) {
            return "";
        }
        return cnt2str.begin()->second;
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
