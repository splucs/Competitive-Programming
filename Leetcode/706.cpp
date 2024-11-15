#define MAX_CONTAINER 8

class MyHashMap {
private:
    vector<vector<pair<int, int>>> table;
    int hash(int v) {
        int ans = 0;
        for (int mod = table.size(); v > 0; v >>= 2) {
            ans = (ans*7 + (v&3))%mod;
        }
        return ans;
    }
    void expand() {
        vector<vector<pair<int, int>>> expTable(2*table.size());
        expTable.swap(table);
        for (vector<pair<int, int>> &pairs : expTable) {
            for (pair<int, int> &p : pairs) {
                put(p.first, p.second);
            }
        }
    }
public:
    MyHashMap() {
        table.resize(8);
    }
    
    void put(int key, int value) {
        int i = hash(key);
        int n = table[i].size();
        for (int j = 0; j < n; j++) {
            if (table[i][j].first == key) {
                table[i][j].second = value;
                return;
            }
        }
        if (n == MAX_CONTAINER) {
            expand();
            put(key, value);
            return;
        }

        table[i].push_back(make_pair(key, value));
    }
    
    int get(int key) {
        int i = hash(key);
        int n = table[i].size();
        for (int j = 0; j < n; j++) {
            if (table[i][j].first == key) {
                return table[i][j].second;
            }
        }
        return -1;
    }
    
    void remove(int key) {
        int i = hash(key);
        int n = table[i].size();
        for (int j = 0; j < n; j++) {
            if (table[i][j].first == key) {
                swap(table[i][j], table[i][n-1]);
                table[i].pop_back();
                break;
            }
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
