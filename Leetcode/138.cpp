/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL) return NULL;
        
        Node *headCopy = NULL;
        for (Node* u = head; u != NULL; u = u->next) {
            Node* v = new Node(u->val);
            v->next = u->random;
            v->random = u;
            u->random = v;
        }
        // At this point:
        // u->next == next of u
        // u->random == v
        // v->next == random of u
        // v->random == u
        headCopy = head->random;

        for (Node* u = head; u != NULL; u = u->next) {
            Node* v = u->random;
            if (v->next != NULL) {
                v->random = v->next->random;
            } else {
                v->random = NULL;
            }
        }
        // At this point:
        // u->next == next of u
        // u->random == v
        // v->next == random of u
        // v->random == random of v

        for (Node* u = head; u != NULL; u = u->next) {
            Node* nu = u->next, *nv = NULL;
            if (nu != NULL) nv = nu->random;

            Node* v = u->random;
            Node* ru = v->next;
            v->next = nv;
            u->random = ru;
        }
        // At this point:
        // u->next == next of u
        // u->random == random of u
        // v->next == next of v
        // v->random == random of v

        return headCopy;
    }
};
