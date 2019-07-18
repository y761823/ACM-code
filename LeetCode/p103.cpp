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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        function<void(TreeNode*, int)> dfs = [&](TreeNode* p, size_t depth) {
            if (!p)
                return ;
            if (res.size() < depth + 1)
                res.push_back({});
            res[depth].push_back(p->val);
            dfs(p->left, depth + 1);
            dfs(p->right, depth + 1);
        };
        dfs(root, 0);
        
        for (size_t i = 0; i < res.size(); ++i)
            if (i & 1) reverse(res[i].begin(), res[i].end());
        
        return res;
    }
};
