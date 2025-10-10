class Solution {
private:
    vector<Node*> last;
    void dfs(Node* u, int h) {
        if (u == NULL) {
            return;
        }
        if (last.size() <= h) {
            last.push_back(NULL);
        }
        if (last[h] != NULL) {
            last[h]->next = u;
        }
        last[h] = u;
        dfs(u->left, h+1);
        dfs(u->right, h+1);
    }
public:
    Node* connect(Node* root) {
        dfs(root, 0);
        for (Node* l : last) {
            l->next = NULL;
        }
        return root;
    }
};
