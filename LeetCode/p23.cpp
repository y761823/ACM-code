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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<pair<int, ListNode*>> que;
        for (ListNode* p : lists)
            if (p) que.push(make_pair(-p->val, p));
        
        ListNode head(0), *np = &head;
        while (!que.empty()) {
            ListNode* p = que.top().second; que.pop();
            np->next = p; np = np->next; p = p->next;
            if (p) que.push(make_pair(-p->val, p));
        }
        return head.next;
    }
};
