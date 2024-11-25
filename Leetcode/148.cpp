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
    inline void swapNodes(ListNode** u, ListNode** v) {
        if (*u == *v) {
            //printf("swapped %d and %d (skipped)\n", (*u)->val, (*v)->val);
            return;
        } else if ((*u)->next == *v) {
            ListNode* prevU = *u;
            ListNode* prevV = *v;
            *v = prevV->next;
            *u = prevV;
            (*u)->next = prevU;
        } else {
            ListNode* nextU = (*u)->next;
            ListNode* nextV = (*v)->next;
            ListNode* tmp = *u;
            *u = *v;
            *v = tmp;
            (*v)->next = nextV;
            (*u)->next = nextU;
        }
    }

    int calculateRandomPivot(ListNode* st, const ListNode* en) {
        int n = 0;
        for (ListNode* u = st; u != en; u = u->next) {
            n++;
        }
        int pivotIdx = rand()%n;
        ListNode* pivotNode = st;
        for (int i = 0; i < pivotIdx; i++) {
            pivotNode = pivotNode->next;
        }
        return pivotNode->val;
    }

    void quickSort(ListNode** st, const ListNode* en) {
        if (*st == en || (*st)->next == en) {
            return;
        }

        int pivot = calculateRandomPivot(*st, en);

        ListNode **eq = st, **ge = st, **u = st;
        while (*u != en) {
            bool moveU = true, moveEq = false, moveGe = false;
            if ((*u)->val == pivot) {
                moveGe = true;
                if ((*ge)->next == *u) {
                    moveU = false;
                }
                swapNodes(ge, u);
            } else if ((*u)->val < pivot) {
                moveGe = moveEq = true;
                if ((*ge)->next == *u) {
                    moveU = false;
                }
                if ((*eq)->next == *ge) {
                    moveU = false;
                    moveGe = false;
                }
                swapNodes(ge, u);
                swapNodes(eq, ge);
            }
            if (moveU) u = &(*u)->next;
            if (moveGe) ge = &(*ge)->next;
            if (moveEq) eq = &(*eq)->next;
        }
        quickSort(st, *eq);
        quickSort(ge, en);
    }
public:
    ListNode* sortList(ListNode* head) {
        quickSort(&head, NULL);
        return head;
    }
};
