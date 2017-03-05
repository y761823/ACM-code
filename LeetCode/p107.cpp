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
    vector<vector<int>> res;
    
    void dfs(TreeNode *p, int dep) {
        if (!p) return ;
        if (res.size() == dep) res.push_back({});
        res[dep].push_back(p->val);
        dfs(p->left, dep + 1);
        dfs(p->right, dep + 1);
    }
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        dfs(root, 0);
        reverse(res.begin(), res.end());
        return res;
    }
};
