class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> wordmap;
        for (const string& word : wordList)
            wordmap[word] = -1;
        wordmap[beginWord] = -1;
        if (wordmap[endWord] != -1)
            return {};
        
        auto findTransWords = [&](string s, int step) {
            vector<string> trans;
            for (char& c : s) {
                char org = c;
                for (char t = 'a'; t <= 'z'; ++t) {
                    c = t;
                    auto it = wordmap.find(s);
                    if (it != wordmap.end() && it->second == step)
                        trans.push_back(s);
                }
                c = org;
            }
            return trans;
        };
        
        queue<string> pre, cur;
        cur.push(endWord);
        int step = wordmap[endWord] = 0;
        while (!cur.empty()) {
            pre.swap(cur);
            step++;
            while (!pre.empty()) {
                string s = pre.front(); pre.pop();
                for (string trans : findTransWords(s, -1)) {
                    wordmap[trans] = step;
                    cur.push(trans);
                    if (trans == beginWord)
                        goto FINDEND;
                }
            }
        }
    FINDEND:
        vector<vector<string>> res;
        vector<string> val;
        function<void(string, int)> dfs = [&](string trans, int step) {
            val.push_back(trans);
            if (trans == endWord) {
                res.push_back(val);
            } else {
                for (string trans : findTransWords(trans, step - 1))
                    dfs(trans, step - 1);
            }
            val.pop_back();
        };
        dfs(beginWord, wordmap[beginWord]);
        return res;
    }
};
