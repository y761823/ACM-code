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
    ListNode* sortList(ListNode* head) {
        ListNode tmpHead{0};
        tmpHead.next = head;
        for (int step = 1; ; step <<= 1) {
            ListNode* pre = &tmpHead;
            while (pre) {
                ListNode* h1 = pre->next;
                ListNode* h2 = getNextSplit(h1, step);
                if (!h2)
                    break;
                ListNode* last = getNextSplit(h2, step);
                
                pre->next = merge(h1, h2);
                if (pre = getNext(pre, step * 2))
                    pre->next = last;
                else
                    break;
            }
            if (pre == &tmpHead)
                break;
        }
        return tmpHead.next;
    }
    
    ListNode* merge(ListNode* h1, ListNode* h2) {
        ListNode head(0), *last = &head;
        while (h1 && h2) {
            ListNode* &h = h1->val < h2->val ? h1 : h2;
            last->next = h;
            last = h;
            h = h->next;
        }
        last->next = h1 ? h1 : h2;
        return head.next;
    }
    
    ListNode* getNext(ListNode* p, int cnt) {
        while (p && cnt--)
            p = p->next;
        return p;
    }
    
    ListNode* getNextSplit(ListNode* p, int cnt) {
        ListNode* pre = nullptr;
        while (p && cnt--) {
            pre = p;
            p = p->next;
        }
        if (pre)
            pre->next = nullptr;
        return p;
    }
};
