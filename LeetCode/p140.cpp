
class Solution {
public:
    struct Node {
        bool flag = false;
        Node* go[26] = {};
    };
    Node* root = nullptr;

    void init(const vector<string>& wordDict) {
        root = new Node;
        for (const string& str : wordDict) {
            Node* p = root;
            for (char c : str) {
                int idx = c - 'a';
                if (!p->go[idx])
                    p->go[idx] = new Node;
                p = p->go[idx];
            }
            p->flag = true;
        }
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<vector<string>> res(s.size());
        vector<bool> vis(s.size());
        function<void(size_t)> dfs = [&](size_t pos) {
            if (vis[pos])
                return ;
            vis[pos] = true;
            
            Node* p = root;
            for (size_t i = pos; p && i < s.size(); ++i) {
                int idx = s[i] - 'a';
                p = p->go[idx];
                if (p && p->flag) {
                    string cur = s.substr(pos, i - pos + 1);
                    if (i + 1 == s.size()) {
                        res[pos].push_back(cur);
                    } else {
                        dfs(i + 1);
                        for (const string& str : res[i + 1])
                            res[pos].push_back(cur + ' ' + str);
                    }
                }
            }
        };

        init(wordDict);
        dfs(0);
        return res.front();
    }
};
