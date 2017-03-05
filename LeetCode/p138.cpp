/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head) return nullptr;
        for (RandomListNode* cur = head; cur; cur = cur->next->next) {
            RandomListNode* p = new RandomListNode(cur->label);
            p->next = cur->next;
            cur->next = p;
        }
        for (RandomListNode* cur = head; cur; cur = cur->next->next) {
            RandomListNode* p = cur->next;
            p->random = cur->random ? cur->random->next : nullptr;
        }
        RandomListNode* res = head->next;
        for (RandomListNode* cur = head; cur; cur = cur->next) {
            RandomListNode* p = cur->next;
            cur->next = p->next;
            p->next = p->next ? p->next->next : nullptr;
        }
        return res;
    }
};
