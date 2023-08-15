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
    ListNode* partition(ListNode* head, int x) {
        ListNode *prev = NULL, *lastSmaller = NULL;
        for(ListNode* u = head; u != NULL;) {
            ListNode* nxt = u->next;

            if (u->val < x) {
                if (lastSmaller == prev) {
                    lastSmaller = u;
                    prev = u;
                    u = nxt;
                    continue;
                }

                // Remove u from list
                if (prev != NULL) prev->next = u->next;
                else head = u->next;

                // Add u to after lastSmaller and update lastSmaller
                if (lastSmaller != NULL) {
                    u->next = lastSmaller->next;
                    lastSmaller->next = u;
                } else {
                    u->next = head;
                    head = u;
                }

                lastSmaller = u;
            } else {
                prev = u;
            }

            u = nxt;
        }
        return head;
    }
};
