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
    int pairSum(ListNode* head) {
        vector<int> list;
        for (ListNode* u = head; u; u = u->next) {
            list.push_back(u->val);
        }
        int ans = 0;
        for (int i = 0, j = list.size()-1; j > i; i++, j--) {
            if (ans < list[i] + list[j]) {
                ans = list[i] + list[j];
            }
        }
        return ans;
    }
};
