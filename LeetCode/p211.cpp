class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new Node;
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        Node* p = root;
        for (auto it = word.begin(); it != word.end(); ++it) {
            int idx = *it - 'a';
            if (!p->go[idx])
                p->go[idx] = new Node;
            p = p->go[idx];
        }
        p->flag = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        std::stack<Node*> nodeStk;
        std::stack<int> posStk; 
        nodeStk.push(root);
        posStk.push(0);
        while (!nodeStk.empty()) {
            Node* p = nodeStk.top(); nodeStk.pop();
            int pos = posStk.top(); posStk.pop();
            
            if (pos == word.size()) {
                if (p->flag)
                    return true;
                continue;
            }
            
            int st = 0, ed = 26;
            if (word[pos] != '.')
                st = word[pos] - 'a', ed = st + 1;
            
            for (int i = st; i < ed; ++i) {
                if (Node* np = p->go[i]) {
                    nodeStk.push(np);
                    posStk.push(pos + 1);
                }
            }
        }
        return false;
    }
    
private:
    struct Node {
        Node* go[26] = {};
        bool flag = false;
    };
    Node* root;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
