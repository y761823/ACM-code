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
    int dfs(TreeNode *p) {
        if (!p->left && !p->right)
            return 1;
        int res = numeric_limits<int>::max();
        if (p->left) res = min(res, dfs(p->left));
        if (p->right) res = min(res, dfs(p->right));
        return res + 1;
    }
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        return dfs(root);
    }
};
