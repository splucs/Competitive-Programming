struct node {
    int key;
    int val;
    node* prev;
    node* next;
    node(int _key, int _val) : key(_key), val(_val), prev(NULL), next(NULL) {}
};

class LRUCache {
private:
    int len;
    int cap;
    node* begin;
    node* end;
    vector<node*> nodeMap;

    void access(node* u) {
        // Remote u from list
        u->next->prev = u->prev;
        u->prev->next = u->next;

        // Add u to end of list
        u->next = end;
        u->prev = end->prev;
        u->next->prev = u;
        u->prev->next = u;
    }
    void evict() {
        node* u = begin->next;
        u->next->prev = u->prev;
        u->prev->next = u->next;
        nodeMap[u->key] = NULL;
        delete u;
    }
public:
    LRUCache(int capacity) {
        cap = capacity;
        len = 0;

        nodeMap.assign(1e4+1, NULL);
        begin = new node(-1, 0);
        end = new node(-1, 0);
        begin->next = end;
        end->prev = begin;
    }
    
    int get(int key) {
        if (nodeMap[key] == NULL) return -1;
        node* u = nodeMap[key];
        access(u);
        return u->val;
    }
    
    void put(int key, int value) {
        if (nodeMap[key] != NULL) {
            node* u = nodeMap[key];
            u->val = value;
            access(u);
        } else {
            node *u = new node(key, value);
            u->next = end;
            u->prev = end->prev;
            u->next->prev = u;
            u->prev->next = u;
            nodeMap[key] = u;
            len++;
        }
        if (len > cap) {
            len--;
            evict();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
