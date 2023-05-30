class MyHashSet {
private:
    const int p = 256;
    const int mod = 1e9+7;
    const int tableMax = 8;
    vector<vector<int> > table;

    int hash(int key) {
        int hash = 0;
        while(key) {
            hash = (hash*1ll*p + (key%10))%mod;
            key /= 10;
        }
        return hash;
    }
    void expand() {
        vector<vector<int> > oldTable = table;
        table = vector<vector<int> >(2*oldTable.size());
        for (vector<int> &row : oldTable) {
            for(int key : row) {
                add(key);
            }
        }
    }
public:
    MyHashSet() {
        table = vector<vector<int> >(8);
    }
    
    void add(int key) {
        if (contains(key)) {
            return;
        }
        while(true) {
            int i = hash(key)%table.size();
            if (table[i].size() < tableMax) {
                table[i].push_back(key);
                return;
            }
            expand();
        }
    }
    
    void remove(int key) {
        int i = hash(key)%table.size();
        int sz = table[i].size();
        for (int j = 0; j < sz; j++) {
            if (table[i][j] == key) {
                table[i][j] = table[i][sz-1];
                table[i].pop_back();
                return;
            }
        }
    }
    
    bool contains(int key) {
        int i = hash(key)%table.size();
        int sz = table[i].size();
        for (int j = 0; j < sz; j++) {
            if (table[i][j] == key) {
                return true;
            }
        }
        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
