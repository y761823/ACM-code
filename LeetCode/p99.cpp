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
    void recoverTree(TreeNode* root) {
        err1 = err2 = pre = nullptr;
        dfs(root);
        swap(err1->val, err2->val);
    }
    
    void dfs(TreeNode* p) {
        if (!p) return ;
        dfs(p->left);
        if (!err1 && pre && pre->val > p->val)
            err1 = pre;
        if (err1 && pre->val > p->val)
            err2 = p;
        pre = p;
        dfs(p->right);
    }
    
    TreeNode *err1, *err2, *pre;
};
