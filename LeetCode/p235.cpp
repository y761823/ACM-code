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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return lowestCommonAncestor(root, min(p->val, q->val), max(p->val, q->val));
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, int l, int r) {
        if (root->val > r)
            return lowestCommonAncestor(root->left, l, r);
        if (l > root->val)
            return lowestCommonAncestor(root->right, l, r);
        return root;
    }
};
