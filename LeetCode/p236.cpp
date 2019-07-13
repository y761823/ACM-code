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
        TreeNode* res = nullptr;
        function<int(TreeNode*)> dfs = [=, &res, &dfs](TreeNode* n) {
            int l = n->left ? dfs(n->left) : 0;
            int r = n->right ? dfs(n->right) : 0;
            int t = l | r | (p == n) | ((q == n) << 1);
            if (t == 3 && !res)
                res = n;
            return t;
        };
        dfs(root);
        return res;
    }
};
