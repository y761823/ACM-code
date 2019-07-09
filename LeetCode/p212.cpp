static const int fr[] = {-1, 0, 1, 0};
static const int fc[] = {0, 1, 0, -1};

class Solution {
private:
    struct Node {
        Node* go[26] = {};
        string str;
    };
    Node* root;
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.empty())
            return {};
        
        n = board.size(), m = board.front().size();
        root = new Node;
        for (auto word : words) {
            insert(word);
        }
        
        this->board = board;
        vis = vector<vector<bool>>(n, vector<bool>(m));
        res.clear();
        
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c) {
                int idx = board[r][c] - 'a';
                if (Node* p = root->go[idx])
                    dfs(r, c, p);
            }
        
        return res;
    }
    
private:
    bool valid(int r, int c) {
        return 0 <= r && r < n && 0 <= c && c < m;
    };
    
    void dfs(int r, int c, Node* p) {
        vis[r][c] = true;
        
        if (!p->str.empty()) {
            res.push_back(p->str);
            p->str.clear();
        }
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + fr[i], nc = c + fc[i];
            if (valid(nr, nc) && !vis[nr][nc])
            {
                int idx = board[nr][nc] - 'a';
                if (Node* np = p->go[idx]) {
                    dfs(nr, nc, np);
                }
            }
        }
        vis[r][c] = false;
    }
    
    void insert(const string str) {
        Node* p = root;
        for (size_t i = 0; i < str.size(); ++i) {
            int idx = str[i] - 'a';
            if (!p->go[idx])
                p->go[idx] = new Node;
            p = p->go[idx];
        }
        p->str = str;
    }
    
private:
    vector<string> res;
    vector<vector<char>> board;
    vector<vector<bool>> vis;
    int n, m;    
};
