/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        int cnt = countList(head);
        return dfs(head, cnt);
    }
    
    TreeNode* dfs(ListNode* &p, int cnt) {
        if (cnt <= 0)
            return nullptr;
        TreeNode* left = dfs(p, cnt / 2);
        TreeNode* res = new TreeNode(p->val);
        res->left = left;
        res->right = dfs(p = p->next, cnt - 1 - cnt / 2);
        return res;
    }
    
    int countList(ListNode* p) {
        int cnt = 0;
        while (p)
            p = p->next, cnt++;
        return cnt;
    }
};
