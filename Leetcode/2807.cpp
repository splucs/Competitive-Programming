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
private:
    int gcd(int x, int y) {
        return y == 0 ? x : gcd(y, x%y);
    }
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if (head->next == NULL) {
            return head;
        }
        head->next = new ListNode(gcd(head->val, head->next->val), insertGreatestCommonDivisors(head->next));
        return head;
    }
};
