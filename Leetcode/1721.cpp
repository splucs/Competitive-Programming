/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        ListNode *root = new ListNode(0, head);
        int n = len(head);
        if (n == 2*k-1) {
            return head;
        }
        if (k > n-k+1) {
            k = n-k+1;
        }
        ListNode *first = removeKth(root, k);
        ListNode *second = removeKth(root, n-k);
        insertBeforeKth(root, first, n-k);
        insertBeforeKth(root, second, k);
        return root->next;
    }
    int len(ListNode* root) {
        if (!root) return 0;
        return 1 + len(root->next);
    }
    ListNode* kth(ListNode *root, int k) {
        if (k == 0) return root;
        return kth(root->next, k-1);
    }
    ListNode* removeKth(ListNode *root, int k) {
        ListNode *prev = kth(root, k-1);
        ListNode *toRem = prev->next;
        prev->next = toRem->next;
        toRem->next = NULL;
        return toRem;
    }
    void insertBeforeKth(ListNode *root, ListNode *toInsert, int k) {
        ListNode *prev = kth(root, k-1);
        toInsert->next = prev->next;
        prev->next = toInsert;
    }
};
