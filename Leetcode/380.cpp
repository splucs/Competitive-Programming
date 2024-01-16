class RandomizedSet {
private:
    unordered_map<int, int> val2Pos;
    vector<int> vals;
public:
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        if (val2Pos.count(val)) {
            return false;
        }

        val2Pos[val] = vals.size();
        vals.push_back(val);

        return true;
    }
    
    bool remove(int val) {
        if (!val2Pos.count(val)) {
            return false;
        }

        int i = val2Pos[val];
        swap(vals[i], vals[vals.size()-1]);

        val2Pos[vals[i]] = i;
        val2Pos.erase(val);

        vals.pop_back();
        return true;
    }
    
    int getRandom() {
        return vals[rand()%vals.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
