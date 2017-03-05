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
    bool res = true;
    int dfs(TreeNode *p) {
        if (!p) return 0;
        int ldep = dfs(p->left);
        if (!res) return 0;
        int rdep = dfs(p->right);
        if (abs(ldep - rdep) > 1)
            res = false;
        return max(ldep, rdep) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        dfs(root);
        return res;
    }
};
