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
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        ListNode *p = head, *q = head->next;
        while (q) {
            p = p->next;
            q = q->next;
            if (q) q = q->next;
            if (p == q) return true;
        }
        return false;
    }
};
