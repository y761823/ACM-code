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
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0)
            return {};
        return _generateTrees(1, n);
    }
    
    vector<TreeNode*> _generateTrees(int l, int r) {
        if (l > r)
            return {nullptr};
        vector<TreeNode*> res;
        for (int i = l; i <= r; ++i) {
            vector<TreeNode*> lnodes = _generateTrees(l, i - 1);
            vector<TreeNode*> rnodes = _generateTrees(i + 1, r);
            for (auto lnode : lnodes) for (auto rnode : rnodes) {
                TreeNode* rt = new TreeNode(i);
                rt->left = lnode;
                rt->right = rnode;
                res.push_back(rt);
            }
        }
        return res;
    }
};
