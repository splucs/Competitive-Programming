/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
private:
    vector<int> ans;
    void go(Node* u) {
        for (Node* v : u->children) {
            go(v);
        }
        ans.push_back(u->val);
    }
public:
    vector<int> postorder(Node* root) {
        if (root != NULL) {
            go(root);
        }
        return ans;
    }
};
