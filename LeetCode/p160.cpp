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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p = headA, *q = headB;
        int np = 0, nq = 0;
        while (p) p = p->next, np++;
        while (q) q = q->next, nq++;
        p = headA, q = headB;
        while (np > nq) p = p->next, np--;
        while (np < nq) q = q->next, nq--;
        while (p != q) p = p->next, q = q->next;
        return p;
    }
};
