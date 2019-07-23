/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode left(0), right(0);
        ListNode *pl(&left), *pr(&right);
        for (ListNode* p = head; p; p = p->next) {
            if (p->val < x)
                pl->next = p, pl = p;
            else
                pr->next = p, pr = p;
        }
        pl->next = right.next;
        pr->next = nullptr;
        return left.next;
    }
};
