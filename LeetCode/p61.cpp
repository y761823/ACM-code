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
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return head;
        
        ListNode* p = head, *q = head;
        int n = 0;
        while (p) q = p, p = p->next, n++;
        if (!(k %= n)) return head;
        
        q->next = head;
        p = q = head;
        for (int i = k; i < n; ++i) q = p, p = p->next;
        q->next = nullptr;
        
        return p;
    }
};
