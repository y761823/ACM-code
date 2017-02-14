
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
    ListNode *findNodeInCycle(ListNode* head) {
        if (!head) return nullptr;
        ListNode *p = head, *q = head->next;
        while (q) {
            p = p->next;
            q = q->next;
            if (q) q = q->next;
            if (p == q) return p;
        }
        return nullptr;
    }

    int getCycleLength(ListNode* p) {
        ListNode* q = p->next;
        int res = 1;
        while (q != p) q = q->next, res++;
        return res;
    }

    ListNode *detectCycle(ListNode *head) {
        ListNode *cp = findNodeInCycle(head);
        if (!cp) return nullptr;
        int len = getCycleLength(cp);
        
        ListNode *p = head, *q = head;
        while (len--) q = q->next;
        while (p != q) p = p->next, q = q->next;
        return p;
    }
};
