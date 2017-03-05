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
    ListNode* insertionSortList(ListNode* head) {
        ListNode tmpHead(0); tmpHead.next = head;
        ListNode* cur = head, *pre = &tmpHead;
        while (cur) {
            ListNode* p = &tmpHead;
            while (p->next->val < cur->val)
                p = p->next;
            ListNode* next = cur->next;
            if (p->next != cur) {
                cur->next = p->next;
                p->next = cur;
                pre->next = cur = next;
            } else {
                pre = cur;
                cur = next;
            }
        }
        return tmpHead.next;
    }
};
