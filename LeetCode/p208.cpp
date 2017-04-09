class Trie {
    struct Node {
        Node* go[26];
        bool flag;
        Node() {
            memset(this, 0, sizeof(Node));
        }
    };
    
    Node* root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new Node();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* p = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!p->go[idx]) p->go[idx] = new Node();
            p = p->go[idx];
        }
        p->flag = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* p = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!p->go[idx]) return false;
            p = p->go[idx];
        }
        return p->flag;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node* p = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!p->go[idx]) return false;
            p = p->go[idx];
        }
        return p;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */
