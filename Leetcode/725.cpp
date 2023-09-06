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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int n = 0;
        for (ListNode* u = head; u != NULL; u = u->next) {
            n++;
        }
        int quo = n/k;
        int rem = n%k;

        vector<ListNode*> ans;
        ListNode *u = head, *prev = NULL;
        for (int i = 0; i < k; i++) {
            ans.push_back(u);

            for (int j = i < rem ? -1 : 0; j < quo; j++) {
                prev = u;
                u = u->next;
            }

            if (prev != NULL) prev->next = NULL;
        }
        return ans;
    }
};
