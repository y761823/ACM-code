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
    int kthSmallest(TreeNode* root, int k) {
        traverse(root, k);
        return k;
    }
    
    bool traverse(TreeNode* p, int& k) {
        if (!p)
            return false;
        if (traverse(p->left, k))
            return true;
        if (--k == 0)
            return k = p->val, true;
        return traverse(p->right, k);
    }
};
